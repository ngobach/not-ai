#include <bits/stdc++.h>
#include "CImg.h"
#include "utils/TestReader.h"
#include "solvers/base.h"
#include "solvers/exact.h"

using namespace cimg_library;
using namespace std;
using namespace solver;

const char* TC01 = "/home/bachnx/Downloads/testcase_01";

int main(){
    BaseSolver *solver = new ExactSolver;
    TestCase *tc = readTestCases(TC01);
    tc->dump();
    if (tc->isValid()) {
        Result result = solver->solve(tc);
        result.visualize();
    } else {
        cerr << "Invalid test case!\nExiting";
    }
    delete tc;
    delete solver;
    return 0;
}