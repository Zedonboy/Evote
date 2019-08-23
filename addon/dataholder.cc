#include "dataholder.h"
DataHolder::DataHolder(napi_deferred mdefered,uint8_t *mvctr,uint32_t mwidth,uint32_t mheight){
    _defered = mdefered;
    _vctr = mvctr;
    _width = mwidth;
    _height = mheight;
}
DataHolder::~DataHolder(){
    delete[] _vctr;
    delete[] _vctrFace;
}