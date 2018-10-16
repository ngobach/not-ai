
#ifndef NOT_AI_RESULT_H
#define NOT_AI_RESULT_H

#include "TestCase.h"
#include <string>
#include <vector>

namespace solver {
    enum Rotate {
        DEG_0 = 0,
        DEG_90 = 90,
        DEG_180 = 180,
        DEG_270 = 270,
    };

    struct ResultItem {
        std::string name;
        int x, y;
        Rotate r;
    };

    struct Result {
    public:
        Result();
        Result(TestCase*);
        std::string basePath;
        std::string origin;
        std::vector<ResultItem> items;
        void visualize();
        void send();
    };
}

#endif //NOT_AI_RESULT_H
