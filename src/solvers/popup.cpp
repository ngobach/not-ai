//
// Created by bachnx on 20/10/2018.
//

#include "popup.h"
#if DEBUG == true

#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

void popup(const cv::Mat & mat) {
    using namespace cv;
    const char *WD_PREVIEW = "preview";
    const char *WD_HISTOGRAM = "histogram";
    const float fRange[] = { 0.0f, 1.0f };
    const int nHistSize = 256;
    const float* fHistRange = { fRange };
    Mat tmp, hist;
    normalize(mat, tmp, 1, 0, NORM_MINMAX, -1, Mat());
    calcHist(&tmp, 1, 0, Mat(), hist, 1, &nHistSize, &fHistRange);
    namedWindow(WD_PREVIEW);
//    namedWindow(WD_HISTOGRAM);
    imshow(WD_PREVIEW, tmp);
    std::cout << hist << std::endl;
    waitKey(0);
}
#else

void popup(const cv::Mat &) {
}
#endif
