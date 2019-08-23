#include "vector"
#include "numeric"
#include "node_api.h"
#include "opencv2/core.hpp"
#include "opencv2/objdetect.hpp"
#include "opencv2/imgproc.hpp"
class FaceFinder{
    public:
        FaceFinder(uint8_t *vctr, uint32_t width, u_int32_t heigh);
        bool init();
        void startScanning(uint8_t *vctr, int * width, int * height, bool &rslt, size_t &size);
    private:
        uint8_t *pixels;
        uint32_t _height, _width;
        cv::Mat img;
        cv::CascadeClassifier face_classifier;
};