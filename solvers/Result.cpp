#include "Result.h"
#include "../CImg.h"

solver::Result::Result() {}
solver::Result::Result(TestCase* testcase) : origin(testcase->origin), basePath(testcase->basePath) {}

void solver::Result::visualize() {

}