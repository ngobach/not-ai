#include "exact.h"
#include "map"
#include "../CImg.h"

solver::ExactSolver::ExactSolver() : BaseSolver("ExactSolver") {}

solver::Result solver::ExactSolver::solve(solver::TestCase *tc) {
    using cimg_library::CImg;
    Result result(tc);
    std::map<int, ResultItem> m;
    CImg<unsigned char> origin((tc->basePath + "/" + tc->origin).data());
    for (const auto &partName: tc->parts) {

    }
    return result;
}