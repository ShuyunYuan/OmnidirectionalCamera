#include <cmath>

#include "ocam_functions.h"

//生成全景环带的展开图
void create_panoramic_undistortion_LUT(CvMat *mapx, CvMat *mapy, float Rmin, float Rmax, float xc, float yc) {
    int width = mapx->width;
    int height = mapx->height;
    float *mapx_data = mapx->data.fl;
    float *mapy_data = mapy->data.fl;
    for (int row = 0; row < height; ++row) {
        for (int column = 0; column < width; ++column) {
            float theta = ((float) column) / width * 2 * M_PI;
            float rho = Rmax - (Rmax - Rmin) / height * row;
            int index = row * width + column;
            mapx_data[index] = xc + rho * cos(theta);
            mapy_data[index] = yc + rho * sin(theta);
        }
    }
}
