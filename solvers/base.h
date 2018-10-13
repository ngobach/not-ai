#ifndef NOT_AI_BASE_H
#define NOT_AI_BASE_H

#include <string>
namespace solver {
    class BaseSolver {
    public:
        BaseSolver(std::string s);
        void solve();
    protected:
        std::string name;
    };
}
#endif //NOT_AI_BASE_H
