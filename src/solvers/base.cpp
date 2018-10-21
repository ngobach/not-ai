#include <utility>
#include "base.h"

solver::BaseSolver::BaseSolver(std::string s) : name(std::move(s)) {}