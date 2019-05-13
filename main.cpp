#include <iostream>

#include <opencv2/opencv.hpp>

#include "processor.h"

using namespace std;
using namespace cv;

int main(int argc, char *argv[]) {

    if (!(argc == 2 || argc == 3)) {
        cerr << "Usage: " << argv[0] << " <FILE_NAME> [THRESHOLD]" << endl;
        exit(1);
    }
    char *fileName = argv[1];
    double threshold = argc == 3 ? stod(argv[2]) : 70;

    Mat outputImage = undistortPanorama(fileName, threshold);
    string outputFileName = fileName;
    string::size_type lastSeparatorIndex = outputFileName.find_last_of("/\\");
    string::size_type prefixIndex = lastSeparatorIndex != string::npos ? lastSeparatorIndex + 1 : 0;
    outputFileName.insert(prefixIndex, "undistorted_");
    imwrite(outputFileName, outputImage);
}
