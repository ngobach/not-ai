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
        Mat tmp = imread(this->basePath + "/" + item.name);
        if (item.r) {
            rotate(tmp, tmp, item.r - 1);
        }
        rectangle(tmp, { 0, 0 }, { tmp.cols - 1 , tmp.rows - 1 }, Scalar(0, 0, 255));
        int x, y, xx, yy;
        x = min(item.x, bg.cols - tmp.cols);
        y = min(item.y, bg.rows - tmp.rows);
        xx = x + tmp.cols;
        yy = y + tmp.rows;
        printf("Part [%s] => (%d->%d):(%d->%d)\n", item.name.data(), x, xx, y, yy);
        tmp.copyTo(bg.colRange(x, xx).rowRange(y, yy));
    }
    const int visibleWidth = 1600;
    const int visibleHeight = 900;
    double ratio = min(double(visibleWidth) / bg.cols, double(visibleHeight) / bg.rows);
    if (ratio < 1) {
        resize(bg, bg, Size(bg.cols * ratio, bg.rows * ratio), CV_INTER_LINEAR);
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

std::ostream &solver::operator<<(std::ostream &out, const solver::ResultItem &r) {
    out << "Part: " << r.name << " at " << r.x << ";" << r.y;
    return out;
}
