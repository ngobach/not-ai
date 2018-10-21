#include <cstdio>
#include <dirent.h>
#include "TestReader.h"

solver::TestCase *readTestCases(const char* path) {
    DIR *dir = opendir(path);
    dirent *entry = readdir(dir);
    solver::TestCase *testCase = new solver::TestCase;
    testCase->basePath = path;
    while (entry != nullptr) {
        if (entry->d_type == DT_REG) {
            std::string s = entry->d_name;
            if (s.find("original.") == 0) {
                testCase->origin = s;
            } else if (s.rfind(".png") == s.length()-4 || s.rfind(".jpg") == s.length()-4){
                testCase->parts.push_back(s);
            }
        }
        entry = readdir(dir);
    }
    return testCase;
}