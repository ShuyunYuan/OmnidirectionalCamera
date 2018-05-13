#include <cstdio>
#include <algorithm>

#include <opencv2/imgcodecs.hpp>
#include <cv.hpp>

#include "ocam_functions.h"

using namespace std;
using namespace cv;

Mat undistortPanorama(const char *fileName) {

    Mat source;
    source = imread(fileName);
    Mat greyscale;
    cvtColor(source, greyscale, CV_BGR2GRAY);
    Mat binary;
    threshold(greyscale, binary, 70, 255, CV_THRESH_BINARY);

    vector<vector<Point>> contours;
    findContours(binary, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
    vector<double> areas(contours.size());
    transform(contours.begin(), contours.end(), areas.begin(),
              [](const vector<Point> &contour) { return contourArea(contour); });
    size_t maxIndex = static_cast<size_t>(max_element(areas.begin(), areas.end()) - areas.begin());
    const vector<Point> &maxContour = contours[maxIndex];
    Point2f center;
    float radius;
    minEnclosingCircle(maxContour, center, radius);

    Mat output(400, 1200, CV_8UC3);
    Mat mapX(output.rows, output.cols, CV_32FC1);
    Mat mapY(output.rows, output.cols, CV_32FC1);
    float rMin = 120;   // the minimum radius of the region you would like to undistort into a panorama
    float rMax = radius;  // the maximum radius of the region you would like to undistort into a panorama
    create_panoramic_undistortion_LUT(mapX, mapY, rMin, rMax, center.x, center.y);//进行展开
    remap(source, output, mapX, mapY, INTER_LINEAR);

    return output;
}
