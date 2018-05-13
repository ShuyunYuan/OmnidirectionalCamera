#ifndef OC_PROCESSOR_H
#define OC_PROCESSOR_H

#include <cv.hpp>

cv::Mat undistortPanorama(const char *fileName, double threshold);

#endif //OC_PROCESSOR_H
