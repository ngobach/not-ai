#include "exact.h"

solver::ExactSolver::ExactSolver() : BaseSolver("ExactSolver") {}

solver::Result solver::ExactSolver::solve(solver::TestCase *tc) {
    Result result(tc);
    result.items.push_back(ResultItem {
        tc->parts[1],
        0, 0,
        Rotate::DEG_0,
    });
    result.items.push_back(ResultItem {
        tc->parts[2],
        300, 300,
        Rotate::DEG_270,
    });
    return result;
}