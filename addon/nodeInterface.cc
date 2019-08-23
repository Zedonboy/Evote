#include "stdio.h"
#include "string"
#include "array"
#include "memory"
#include "tuple"
#include "nodeInterface.h"
#include "dataholder.h"
// remember you must initialize an empty buffer at arraybuffer before writing on it
#define SIZE_OF_PIXEL_ARRAY 100*100*4
// make sure to call property checker before calling this
void checkProperties(napi_env env,const napi_value obj, std::vector<std::string> properties){
    for (auto &&i : properties)
    {
        const char * foo = i.c_str();
        bool result;
        napi_has_named_property(env, obj, foo, &result);
        if(result) continue;
        else {
            auto errorMssg = std::string("The Propery ") += i += std::string("be found");
            napi_throw_error(env, NULL, errorMssg.c_str());
            break;
        }
    }
    
}

void getProperties(napi_env env, napi_value obj,std::vector<std::string> props ,std::vector<napi_value*> values){
    for (size_t i = 0; i < props.size(); i++)
    {
        napi_get_named_property(env, obj, props[i].c_str(), values[i]);
    }    
}

void getValuesfromTypedArray(napi_env env,napi_value uint8array,size_t length_Of_Js_Array, uint8_t *pixelArray8){
    for (size_t i = 0; i < length_Of_Js_Array; i++)
    {
        napi_value element;
        uint32_t tmpValue;
        napi_get_element(env, uint8array, i, &element);
        napi_coerce_to_number(env, element, &element);
        napi_get_value_uint32(env, element, &tmpValue);
        pixelArray8[i] = (uint8_t)tmpValue;
    }
}

void executor(napi_env env, void* data){
    auto dataHolder = static_cast<DataHolder *>(data);
    std::unique_ptr<FaceFinder> ptr = std::make_unique<FaceFinder>(dataHolder->_vctr, dataHolder->_width, dataHolder->_height);
    if(ptr->init()){
        int32_t width, height;
        napi_value arraybuffer;
        dataHolder->_vctrFace = new uint8_t[SIZE_OF_PIXEL_ARRAY]; // width * height * 4 bytes color
        ptr->startScanning(dataHolder->_vctrFace, &width, &height, dataHolder->FaceResult, dataHolder->arraySize);
        dataHolder->_height = height;
        dataHolder->_width = width;
        dataHolder->_status = napi_ok;
    } else {
        napi_throw_error(env, NULL, "Could not load haarcaascade .xml(model) file, place the file at the directory where you app started to run");
        dataHolder->_status = napi_cancelled;
    }
}

void createResultJS_Object_Props(napi_env env, napi_value js_obj, int32_t width, int32_t height, uint8_t *pixelData, DataHolder *dataholder){
    napi_value js_width, js_height, uint8clamped, arraybuffer;
    napi_create_int32(env, width, &js_width);
    uint8_t *buffer = new uint8_t[SIZE_OF_PIXEL_ARRAY];
    napi_create_int32(env, height, &js_height);
    napi_create_arraybuffer(env, SIZE_OF_PIXEL_ARRAY, (void**)&buffer, &arraybuffer);
    // copying to buffer
    memcpy(buffer, pixelData, dataholder->arraySize);
    napi_create_typedarray(env, napi_uint8_clamped_array, dataholder->arraySize, arraybuffer, 0, &uint8clamped);
    napi_set_named_property(env, js_obj, "width", js_width);
    napi_set_named_property(env, js_obj, "height", js_height);
    napi_set_named_property(env, js_obj, "pixelArray", uint8clamped);  
}

void executor_complete(napi_env env, napi_status status,void* data){
    auto dataholder = static_cast<DataHolder *>(data);
    if(status == napi_ok && dataholder->_status != napi_cancelled && dataholder->FaceResult){
        napi_value js_Obj;
        napi_create_object(env, &js_Obj);
        createResultJS_Object_Props(env, js_Obj, dataholder->_width, dataholder->_height, dataholder->_vctrFace, dataholder);
        napi_resolve_deferred(env, dataholder->_defered, js_Obj);
    } else if(!dataholder->FaceResult) {
        napi_value error, mssg;
        napi_create_string_utf8(env, 
        "Could not get face, from photo try taking another photo with emphasis on his/her face", NAPI_AUTO_LENGTH, &mssg);
        napi_create_error(env, NULL, 
        mssg, &error);
        napi_reject_deferred(env, dataholder->_defered, error);
    } else {
        napi_value error, mssg;
        napi_create_string_utf8(env, 
        "Error Face detection was canceled because maybe could not load haarcascade model file", NAPI_AUTO_LENGTH, &mssg);
        napi_create_error(env, NULL, 
        mssg, &error);
        napi_reject_deferred(env, dataholder->_defered, error);
    }
    delete dataholder;
}

void createAsyncOp(napi_env env, napi_deferred defered, uint8_t *vtr, int32_t width, int32_t height){
    napi_async_work work;
    napi_value asyncID;
    DataHolder* dataHldrPtr = new DataHolder(defered, vtr, width, height);
    //static_cast<void *>(dataHldrPtr);
    napi_create_int32(env, 45078, &asyncID);
    napi_create_async_work(env, NULL, asyncID, executor, executor_complete, dataHldrPtr, &work);
    napi_queue_async_work(env, work);
}

napi_value GetFacePhoto_JSFunction(napi_env env, napi_callback_info info){
    napi_status status;
    napi_value js_argument[1];
    napi_deferred deferred;
    napi_value promise;

    size_t argc = 1;
    status = napi_get_cb_info(env, info, &argc, js_argument, NULL, NULL);

    napi_value uint8array, height, width;
    checkProperties(env, js_argument[0], {"height", "width", "pixelArray"});
    getProperties(env, js_argument[0],{"height", "width", "pixelArray"}, {&height, &width, &uint8array} );
    napi_coerce_to_number(env, height, &height);
    napi_coerce_to_number(env, width, &width);
    bool result;
    napi_is_typedarray(env, uint8array, &result);
        if(!result){
            napi_throw_error(env, NULL, "pixelArray is not a typed Array");
            return NULL;
        }

    int32_t c_int_width, c_int_height;
    napi_typedarray_type arrayType = napi_uint8_clamped_array;
    size_t length_Of_Js_Array;
    napi_get_typedarray_info(env, uint8array, &arrayType, &length_Of_Js_Array, NULL,NULL,NULL);
    //int32_t *pixelArray8 = new int32_t[length_Of_Js_Array];
    uint8_t * pixelArray8 = new uint8_t[length_Of_Js_Array];
    getValuesfromTypedArray(env, uint8array, length_Of_Js_Array, pixelArray8);
    napi_get_value_int32(env, height, &c_int_height);
    napi_get_value_int32(env, width, &c_int_width);
    napi_create_promise(env, &deferred, &promise);
    createAsyncOp(env, deferred, pixelArray8, c_int_width, c_int_height);
    return promise;
}


napi_value testing(napi_env env, napi_callback_info info){
    napi_value arraybuffer, uint8clamped, num;
    uint8_t * buffer = NULL;
    uint8_t * b = new uint8_t[2];
    napi_create_arraybuffer(env, 2, (void **)&b, &arraybuffer);
    b[0] = 6;
    b[1] = 7;
    napi_create_typedarray(env, napi_uint8_clamped_array, 2, arraybuffer, 0, &uint8clamped);
    return uint8clamped;
}

napi_status createAddonObject(napi_env env,napi_value  &AddonObj){
    napi_status status;
    status = napi_create_object(env, &AddonObj);
    napi_value function, functionOne; // testing
    status = napi_create_function(env, "getFace", NAPI_AUTO_LENGTH, GetFacePhoto_JSFunction,NULL, &function);
    // For Testing Purposes
    napi_create_function(env, "test", NAPI_AUTO_LENGTH, testing, NULL, &functionOne);
    status = napi_set_named_property(env, AddonObj, "getFace", function);
    // testing
    napi_set_named_property(env, AddonObj, "test", functionOne);
    return status;
}

napi_value init(napi_env env, napi_value exports){
    napi_status status;
    napi_value newAddon;
    status = createAddonObject(env, newAddon);
    if(status != napi_ok) return NULL;
    return newAddon;
}

inline int checkStatus(napi_status &status){
    if(status != napi_ok) return NULL;
}

inline int checkStatusWithMssg(const napi_status & st, napi_env env, const char *messg){
    if(st != napi_ok){
        napi_throw_error(env, NULL, messg);
        return NULL;
    }
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, init);