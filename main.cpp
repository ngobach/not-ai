#include <bits/stdc++.h>
#include "utils/TestReader.h"
#include "solvers/base.h"
#include "solvers/exact.h"
#include "submitter/submitter.h"

using namespace std;
using namespace solver;

//const char* TC01 = "/home/bachnx/Documents/tc03xs";
const char* TEST_CASE_DIR = "/home/bachnx/Documents/tc03xs";

int main(int argc, char **argv){
    char sock_host[1024];
    int sock_port;
    if (argc < 3) {
        strcpy(sock_host, "127.0.0.1");
        sock_port = atoi(argv[1]);
    } else {
        strcpy(sock_host, argv[1]);
        sock_port = atoi(argv[2]);
    }
    printf("Socket info %s:%d\n", sock_host, sock_port);
    bool isConnect = submitter::connect(sock_host, sock_port);
    if (isConnect) {
        printf("Submitter connected to server!\n");
    } else {
        printf("ERROR! Submitter failed to connect to server!\n");
        exit(1);
    }

    // Solving the real problem
    BaseSolver *solver = new ExactSolver;
    TestCase *tc = readTestCases(TEST_CASE_DIR);
    tc->dump();
    if (tc->isValid()) {
        Result *result = solver->solve(tc);
        result->visualize();
    } else {
        cerr << "Invalid test case!\nExiting";
    }
    return 0;
}