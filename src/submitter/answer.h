//
// Created by bachnx on 20/10/2018.
//

#ifndef NOT_AI_ANSWER_H
#define NOT_AI_ANSWER_H

#include <string>
#include <vector>

struct Answer {
    std::string name;
    int x;
    int y;
    int rotate;
};

extern std::vector<Answer> ans;

#endif //NOT_AI_ANSWER_H
