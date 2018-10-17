#include "Result.h"
#include <opencv2/core.hpp>
#if DEBUG == true
#include <opencv2/highgui.hpp>
#endif
#include <opencv2/imgproc.hpp>

solver::Result::Result() {}
solver::Result::Result(TestCase* tc) : origin(tc->origin), basePath(tc->basePath) {}

#if DEBUG == true
void solver::Result::visualize() {
    using namespace cv;
    Mat bg = imread((this->basePath + "/" + this->origin).data());
    bg = Scalar(48, 48, 48);
    namedWindow("Visualizer", WINDOW_AUTOSIZE);
    for (const auto &item : this->items) {
        Mat tmp = imread(this->basePath + "/" + item.name, IMREAD_COLOR);
        rectangle(tmp, { 0, 0 }, { tmp.cols - 1 , tmp.rows - 1 }, Scalar(0, 0, 255));
        tmp.copyTo(bg.rowRange(item.y, min(item.y + tmp.rows, bg.rows)).colRange(item.x, min(item.x + tmp.cols, bg.cols)));
    }
    imshow("Visualizer", bg);
    waitKey(0);
}
#else
void solver::Result::visualize() {
    printf("Release build! Visualize skipped.");
}
#endif

void solver::Result::send() {
    // TODO: Send this via socket
}
