#include "node_api.h"

// Module Initialization 
napi_value init (napi_env env, napi_value exports){
    napi_value jsObj;
    napi_create_object(env, &jsObj);
    return jsObj;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, init);