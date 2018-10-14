#ifndef NOT_AI_BASE_H
#define NOT_AI_BASE_H

#include <string>
#include "TestCase.h"

namespace solver {
    class BaseSolver {
    public:
        BaseSolver(std::string s);
        virtual bool solve(TestCase*) =0;
    protected:
        std::string name;
    };
}
#endif //NOT_AI_BASE_H
