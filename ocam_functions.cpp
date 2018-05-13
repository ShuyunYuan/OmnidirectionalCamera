
#define _USE_MATH_DEFINES
#include <math.h>

#include "ocam_functions.h"


//生成全景环带的展开图
void create_panoramic_undistortion_LUT(CvMat *mapx, CvMat *mapy, float Rmin, float Rmax, float xc, float yc) {
    int i, j;
    float theta;
    int width = mapx->width;
    int height = mapx->height;
    float *data_mapx = mapx->data.fl;
    float *data_mapy = mapy->data.fl;
    float rho;

    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            // Note, if you would like to flip the image, just inverte the sign of theta
            theta = -((float) j) / width * 2 * M_PI;
            rho = Rmax - (Rmax - Rmin) / height * i;
            *(data_mapx + i * width + j) = xc + rho * sin(theta);
            *(data_mapy + i * width + j) = yc + rho * cos(theta);
        }
    }
}
