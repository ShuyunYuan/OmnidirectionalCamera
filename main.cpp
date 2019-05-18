#include <chrono>
#include <iostream>

#include <opencv2/opencv.hpp>

#include "processor.h"

using namespace std;
using namespace std::chrono;
using namespace cv;

void usage(const char *name) {
    cerr << "Usage: " << name << " <FILE_NAME> [-t <THRESHOLD>] [-b <TIMES>]" << endl;
}

int main(int argc, char *argv[]) {

    char *fileName = nullptr;
    double threshold = 70;
    bool benchmark = false;
    size_t times = 1;
    for (size_t i = 1; i < argc;) {
        if (strcmp(argv[i], "-t") == 0) {
            if (i + 1 >= argc) {
                usage(argv[0]);
                return 1;
            }
            threshold = stod(argv[i + 1]);
            i += 2;
        } else if (strcmp(argv[i], "-b") == 0) {
            if (i + 1 >= argc) {
                usage(argv[0]);
                return 1;
            }
            benchmark = true;
            times = stol(argv[i + 1]);
            i += 2;
        } else {
            if (fileName) {
                usage(argv[0]);
                return 1;
            }
            fileName = argv[i];
            ++i;
        }
    }

    Mat inputImage = imread(fileName);
    Mat outputImage;
    auto start = high_resolution_clock::now();
    for (size_t i = 0; i < times; ++i) {
        outputImage = undistortPanorama(inputImage, threshold);
    }
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start) / times;
    if (benchmark) {
        cout << "Times: " << times << endl;
        cout << "Mean: " << duration.count() << "ms" << endl;
    }

    string outputFileName = fileName;
    string::size_type lastSeparatorIndex = outputFileName.find_last_of("/\\");
    string::size_type prefixIndex = lastSeparatorIndex != string::npos ? lastSeparatorIndex + 1 : 0;
    outputFileName.insert(prefixIndex, "undistorted_");
    imwrite(outputFileName, outputImage);
}
