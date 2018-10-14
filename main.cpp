#include <bits/stdc++.h>
#include "CImg.h"
#include "utils/TestReader.h"
#include "solvers/base.h"
#include "solvers/exact.h"

using namespace cimg_library;
using namespace std;
using namespace solver;

const char* TC01 = "/home/bachnx/Downloads/pikalong-ai-testcases/testcase_01";

int main(){
    BaseSolver *solver = new ExactSolver;
    TestCase *tc = readTestCases(TC01);
    tc->dump();
    solver->solve(tc);
    delete tc;
    delete solver;
    return 0;
}