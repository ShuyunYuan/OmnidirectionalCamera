#include <cmath>

#include "ocam_functions.h"

using namespace cv;

void create_panoramic_undistortion_LUT(Mat mapX, Mat mapY, float rMin, float rMax, float centerX, float centerY) {
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
