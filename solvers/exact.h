#ifndef NOT_AI_EXACT_H
#define NOT_AI_EXACT_H

#include "base.h"
namespace solver {
    class ExactSolver : public BaseSolver {
    public:
        ExactSolver();
        bool solve(TestCase);
    };
}
#endif //NOT_AI_EXACT_H
