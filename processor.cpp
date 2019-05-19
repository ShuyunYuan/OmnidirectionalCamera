#include <cstdio>
#include <algorithm>

#include <opencv2/opencv.hpp>

#ifdef USE_CUDA
#include <opencv2/cudawarping.hpp>
#endif

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

Mat undistortPanorama(const Mat &input) {

    int outputRows = 400;
    int outputCols = 1200;
    Mat mapX(outputRows, outputCols, CV_32FC1);
    Mat mapY(outputRows, outputCols, CV_32FC1);
    // The minimum radius of the region to undistort into a panorama
    float rMin = 120;
    // The maximum radius of the region to undistort into a panorama
    float rMax = 400;
    makeUndistortPanoramicMaps(mapX, mapY, rMin, rMax, input.cols / 2.0f, input.rows / 2.0f);

#ifdef USE_CUDA
    cuda::GpuMat gpuInput(input);
    cuda::GpuMat gpuOutput(outputRows, outputCols, input.type());
    cuda::GpuMat gpuMapX(mapX);
    cuda::GpuMat gpuMapY(mapY);
    cuda::remap(gpuInput, gpuOutput, gpuMapX, gpuMapY, INTER_LINEAR);
    Mat output;
    gpuOutput.download(output);
#else
    Mat output(outputRows, outputCols, input.type());
    remap(input, output, mapX, mapY, INTER_LINEAR);
#endif

    return output;
}
