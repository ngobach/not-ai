//
// Created by bachnx on 19/10/2018.
//

#ifndef NOT_AI_SUBMITER_H
#define NOT_AI_SUBMITER_H

#include <string>

namespace submiter {
    struct SubmitResult {
        std::string name;
        int x, y, rotate;
        bool isOk;
    };

    bool connect(const char* host, int port);
    bool disconnect();
    bool isConnected();
    SubmitResult submit(const char *name, int x, int y, int rotate);
}

#endif //NOT_AI_SUBMITER_H
