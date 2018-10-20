#include "exact.h"
#include "map"
#include <iostream>
#include <limits>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include "../submitter/submitter.h"

namespace {
    using namespace cv;
    double search(const Mat &src, const Mat &tpl, solver::ResultItem &resultItem) {
        double best = std::numeric_limits<double>::max();
        double minVal, maxVal;
        Point loc;
        Mat src_, tpl_, match, tmp;
        int scaleFactor = max(src.cols, src.rows) / 1000;
        if (scaleFactor < 1) { scaleFactor = 1; }

        resize(tpl, tpl_, Size(tpl.cols/scaleFactor, tpl.rows/scaleFactor));
        resize(src, src_, Size(src.cols/scaleFactor, src.rows/scaleFactor));
        for (int rot = 0; rot < 4; rot++) {
            tpl_.copyTo(tmp);
            if (rot) {
                cv::rotate(tmp, tmp, rot - 1);
            }
            match.create(src_.rows - tmp.rows + 1, src_.cols - tmp.cols + 1, CV_32FC1);
            matchTemplate(src_, tmp, match, CV_TM_SQDIFF);
            minMaxLoc(match, &minVal, &maxVal, &loc, nullptr);
            // TODO: Normalize & find if its best match
            printf("** Match result %dx ^%d at [%d:%d] ::: %.0lf/%.0lf\n", scaleFactor, rot * 90, loc.x*scaleFactor, loc.y*scaleFactor, minVal, maxVal);
            if (best > minVal) {
                resultItem.x = loc.x*scaleFactor;
                resultItem.y = loc.y*scaleFactor;
                resultItem.r = (solver::Rotate) rot;
                best = minVal;
            }
        }
        // Correction phase
        if (scaleFactor > 1) {
            if (resultItem.r) {
                rotate(tpl, tmp, resultItem.r - 1);
            } else {
                tmp = tpl;
            }
            int boundX = max(0, resultItem.x - scaleFactor*2);
            int boundY = max(0, resultItem.y - scaleFactor*2);
            int boundXX = min(boundX + tmp.cols + scaleFactor*4, src.cols);
            int boundYY = min(boundY + tmp.rows + scaleFactor*4, src.rows);
            Mat sub = src.rowRange(boundY, boundYY).colRange(boundX, boundXX);
            match.create(sub.rows - tmp.rows + 1, sub.cols - tmp.cols + 1, CV_32FC1);
            matchTemplate(sub, tmp, match, CV_TM_SQDIFF);
            minMaxLoc(match, &minVal, nullptr, &loc, nullptr);
            loc.x += boundX; loc.y += boundY;
            printf("** Corrected location %d:%d\n", loc.x, loc.y);
            resultItem.x = loc.x;
            resultItem.y = loc.y;
        }
        return minVal;
    }
    const double THRESHOLD = 1e6;
}

solver::ExactSolver::ExactSolver() : BaseSolver("ExactSolver") {}

solver::Result *solver::ExactSolver::solve(solver::TestCase *tc) {
    using namespace cv;
    using namespace submitter;

    Result *result = new Result(tc);
    Mat origin = imread(tc->basePath + "/" + tc->origin);

    for (const auto &part : tc->parts) {
        ResultItem ri = {};
        ri.name = part;
        Mat mPart = imread(tc->basePath + "/" + part);
        double score = search(origin, mPart, ri);
        printf("Matched part %s with score %.0lf at %d:%d^%d\n", ri.name.data(), score, ri.x, ri.y, ri.r*90);
        submitter::submit(ri.name.data(), ri.x, ri.y, ri.r);
        result->items.push_back(ri);
    }
    printf("Solver ended!\n");
    return result;
}