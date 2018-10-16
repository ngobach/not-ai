#include "exact.h"
#include "map"
#include <iostream>
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
    const int match_method = CV_TM_SQDIFF_NORMED;
    for (const auto &part : tc->parts) {
        double minVal = 0, maxVal = 0;
        Point minLoc, maxLoc, matchLoc;
        Mat mPart = imread(tc->basePath + "/" + part);
        match.create(origin.rows - mPart.rows + 1, origin.cols - mPart.cols + 1, CV_32FC1);
        matchTemplate(origin, mPart, match, match_method);
        minMaxLoc(match, &minVal, &maxVal, &minLoc, &maxLoc);
        if(match_method == CV_TM_SQDIFF || match_method == CV_TM_SQDIFF_NORMED) {
            matchLoc = minLoc;
        } else {
            matchLoc = maxLoc;
        }
        printf("** Match result for part \"%s\": at %d %d\n", (tc->basePath + "/" + part).data(), matchLoc.x, matchLoc.y);
        result->items.push_back(ResultItem {
            part,
            matchLoc.x,
            matchLoc.y,
            Rotate::DEG_0,
        });
    }
    return result;
}