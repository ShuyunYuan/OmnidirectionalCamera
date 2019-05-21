#include <chrono>
#include <iostream>

#include <opencv2/opencv.hpp>

#include "processor.h"

using namespace std;
using namespace std::chrono;
using namespace cv;

void usage(const char *name) {
    cerr << "Usage: " << name << " <FILE_NAME> [-b <TIMES>]" << endl;
}

int main(int argc, char *argv[]) {

    char *fileName = nullptr;
    bool benchmark = false;
    size_t times = 1;
    for (size_t i = 1; i < argc;) {
        if (strcmp(argv[i], "-b") == 0) {
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
    high_resolution_clock::duration totalDuration;
    for (size_t i = 0; i < times; ++i) {
        high_resolution_clock::duration duration;
        outputImage = undistortPanorama(inputImage, duration);
        totalDuration += duration;
    }
    long totalDurationMillis = duration_cast<milliseconds>(totalDuration).count();
    if (benchmark) {
        cout << "Times: " << times << ", Total: " << totalDurationMillis << "ms, Mean: "
                << (double) totalDurationMillis / times << "ms" << endl;
    }

    string outputFileName = fileName;
    string::size_type lastSeparatorIndex = outputFileName.find_last_of("/\\");
    string::size_type prefixIndex = lastSeparatorIndex != string::npos ? lastSeparatorIndex + 1 : 0;
    outputFileName.insert(prefixIndex, "undistorted_");
    imwrite(outputFileName, outputImage);
}
