#ifndef NOT_AI_TESTCASE_H
#define NOT_AI_TESTCASE_H

#include <string>
#include <vector>

namespace solver {
    struct TestCase {
        std::string basePath;
        std::string origin;
        std::vector<std::string> parts;
        bool isValid();
        void dump();
    };
}

#endif //NOT_AI_TESTCASE_H
