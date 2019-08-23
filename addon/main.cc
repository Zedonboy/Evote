#include "nodeInterface.h"
#include "opencv2/highgui.hpp"
#include "stdint.h"
FaceFinder::FaceFinder(uint8_t *vctr, uint32_t width, u_int32_t height){
    pixels = vctr;
    _width = width;
    _height = height;
}

bool FaceFinder::init(){
    img = cv::Mat(_height,_width, CV_8UC4, pixels);
    auto result = face_classifier.load("haarcascade_frontalface_alt2.xml");
    return result;
}

void FaceFinder::startScanning(uint8_t *vctr, int * width, int * height, bool &result, size_t &size){
    cv::Mat gray;
    #ifdef DEBUG
    cv::imshow("Test", img);
    cv::waitKey();
    #endif
    cv::cvtColor(img, gray, cv::COLOR_RGBA2GRAY);
    cv::equalizeHist(gray, gray);
    std::vector<cv::Rect> faces;
    face_classifier.detectMultiScale(gray, faces, 1.5, 2, 0|cv::CASCADE_SCALE_IMAGE, cv::Size(20, 20));
    if(faces.size() > 0){
        result = true;
        cv::Mat grayfaceRoi = gray(faces[0]);
        cv::resize(grayfaceRoi,grayfaceRoi, cv::Size(100, 100), 0,0);
        *width = grayfaceRoi.cols;
        *height = grayfaceRoi.rows;
        cv::cvtColor(grayfaceRoi, grayfaceRoi, cv::COLOR_GRAY2RGBA);
        size = grayfaceRoi.total() * 4;
        memcpy(vctr, grayfaceRoi.data, grayfaceRoi.total() * 4);
    }
}