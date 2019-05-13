#include <cstdio>
#include <algorithm>

#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

static void makeUndistortPanoramicMaps(Mat mapX, Mat mapY, float rMin, float rMax, float centerX, float centerY) {
    int columns = mapX.cols;
    int rows = mapX.rows;
    for (int row = 0; row < rows; ++row) {
        for (int column = 0; column < columns; ++column) {
            float rho = rMin + (rMax - rMin) / rows * row;
            float theta = -static_cast<float>(column) / columns * 2 * static_cast<float>(M_PI);
            mapX.at<float>(row, column) = centerX + rho * cos(theta);
            mapY.at<float>(row, column) = centerY + rho * sin(theta);
        }
    }
}

Mat undistortPanorama(const char *fileName, double threshold) {

    Mat source;
    source = imread(fileName);
    Mat greyscale;
    cvtColor(source, greyscale, COLOR_BGR2GRAY);
    Mat binary;
    cv::threshold(greyscale, binary, threshold, 255, THRESH_BINARY);

    vector<vector<Point>> contours;
    findContours(binary, contours, RETR_EXTERNAL, CHAIN_APPROX_NONE);
    vector<double> areas(contours.size());
    transform(contours.begin(), contours.end(), areas.begin(),
              [](const vector<Point> &contour) { return contourArea(contour); });
    size_t maxIndex = static_cast<size_t>(max_element(areas.begin(), areas.end()) - areas.begin());
    const vector<Point> &maxContour = contours[maxIndex];
    Point2f center;
    float radius;
    minEnclosingCircle(maxContour, center, radius);

    Mat output(400, 1200, source.type());
    Mat mapX(output.rows, output.cols, CV_32FC1);
    Mat mapY(output.rows, output.cols, CV_32FC1);
    float rMin = 380;   // the minimum radius of the region you would like to undistort into a panorama
    float rMax = radius;  // the maximum radius of the region you would like to undistort into a panorama
    makeUndistortPanoramicMaps(mapX, mapY, rMin, rMax, center.x, center.y);//进行展开
    remap(source, output, mapX, mapY, INTER_LINEAR);

    return output;
}
