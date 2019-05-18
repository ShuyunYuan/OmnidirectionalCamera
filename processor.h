#ifndef OC_PROCESSOR_H
#define OC_PROCESSOR_H

#include <opencv2/opencv.hpp>

cv::Mat undistortPanorama(const cv::Mat &fileName, double threshold);

#endif //OC_PROCESSOR_H
