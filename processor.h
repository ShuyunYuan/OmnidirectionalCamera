#ifndef OC_PROCESSOR_H
#define OC_PROCESSOR_H

#include <chrono>

#include <opencv2/opencv.hpp>

cv::Mat undistortPanorama(const cv::Mat &input, std::chrono::high_resolution_clock::duration &duration);

#endif //OC_PROCESSOR_H
