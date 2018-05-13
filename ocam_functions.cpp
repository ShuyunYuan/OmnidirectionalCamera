#include <cmath>

#include "ocam_functions.h"

using namespace cv;

//生成全景环带的展开图
void create_panoramic_undistortion_LUT(Mat mapx, Mat mapy, float rMin, float rMax, float centerX, float centerY) {
    int columns = mapx.cols;
    int rows = mapx.rows;
    for (int row = 0; row < rows; ++row) {
        for (int column = 0; column < columns; ++column) {
            float theta = ((float) column) / columns * 2 * M_PI;
            float rho = rMin + (rMax - rMin) / rows * row;
            mapx.at<float>(row, column) = centerX + rho * cos(theta);
            mapy.at<float>(row, column) = centerY + rho * sin(theta);
        }
    }
}
