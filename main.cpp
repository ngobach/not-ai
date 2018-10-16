#include <bits/stdc++.h>
#include "utils/TestReader.h"
#include "solvers/base.h"
#include "solvers/exact.h"

using namespace std;
using namespace solver;

const char* TC01 = "../testcase";

int main(){
    BaseSolver *solver = new ExactSolver;
    TestCase *tc = readTestCases(TC01);
    tc->dump();
    if (tc->isValid()) {
        Result *result = solver->solve(tc);
        result->visualize();
    } else {
        cerr << "Invalid test case!\nExiting";
    }
    return 0;
}