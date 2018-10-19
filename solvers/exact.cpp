#include "exact.h"
#include "map"
#include <iostream>
#include <limits>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>

solver::ExactSolver::ExactSolver() : BaseSolver("ExactSolver") {}

solver::Result *solver::ExactSolver::solve(solver::TestCase *tc) {
    using namespace cv;
    Result *result = new Result(tc);
    std::map<int, ResultItem> m;
    Mat origin = imread(tc->basePath + "/" + tc->origin);
    Mat match;

    for (const auto &part : tc->parts) {
        double best = std::numeric_limits<double>::min();
        ResultItem ri = ResultItem {};
        double minVal, maxVal;
        Point loc;
        Mat mPart = imread(tc->basePath + "/" + part);
        for (int rot = 0; rot < 4; rot++) {
            Mat tmp;
            mPart.copyTo(tmp);
            if (rot) {
                cv::rotate(tmp, tmp, rot-1);
            }
            match.create(origin.rows - tmp.rows + 1, origin.cols - tmp.cols + 1, CV_32FC1);
            matchTemplate(origin, tmp, match, CV_TM_CCOEFF);
            minMaxLoc(match, &minVal, &maxVal, nullptr, &loc);
            printf("** Match result for part \"%30s\"/%d at (%5d:%5d) ::: %lf/%lf\n", (tc->basePath + "/" + part).data(), rot * 90, loc.x, loc.y, minVal, maxVal);
            if (maxVal > best) {
                ri = ResultItem {
                    part,
                    loc.x,
                    loc.y,
                    (Rotate)rot,
                };
                best = maxVal;
            }
        }
        result->items.push_back(ri);
        std::cout << result->items.back() << '\n';
    }
    return result;
}