#include "vector"
#include "node_api.h"

class DataHolder{
    public:
        DataHolder(napi_deferred defered, uint8_t *vctr, uint32_t width, uint32_t height);
        napi_deferred _defered;
        napi_status _status;
        uint8_t *_vctr;
        uint32_t _width;
        uint32_t _height;
        uint8_t * _vctrFace;
        bool FaceResult = false;
        size_t arraySize = 0;
        ~DataHolder();
};