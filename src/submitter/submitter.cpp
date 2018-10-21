#include <sys/socket.h>
#include <arpa/inet.h>
#include <cstring>
#include <iostream>
#include <chrono>
#include <thread>

#include "submitter.h"
#include "answer.h"

using namespace std::chrono;

const int MAX_BUFF = 1995;
const int SUBMIT_DELAY_MS = 200;

int sock_fd = 0;
char sock_buff[MAX_BUFF];
long long lastSubmit = 0;

inline long long millis() {
    return duration_cast< milliseconds >(system_clock::now().time_since_epoch()).count();
}


#if DEBUG == true
bool submitter::connect(const char *host, int port) {
    return true;
}
#else
bool submitter::connect(const char *host, int port) {
    sockaddr_in server_addr;
    if((sock_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("ERROR! Could not create socket\n");
        return false;
    }
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_addr.s_addr = inet_addr(host);
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    if (connect(sock_fd, (sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        printf("ERROR! Could not connect()!\n");
        return false;
    }
    return true;
}
#endif

#if DEBUG == true
bool submitter::disconnect() {
    return true;
}
#else
bool submitter::disconnect() {
    shutdown(sock_fd, SHUT_RDWR);
    return true;
}
#endif

#if DEBUG == true
submitter::SubmitResult submitter::submit(const char *name, int x, int y, int rotate) {
    SubmitResult result = {};
    if (ans.empty()) {
        return { "OK", x, y, rotate, OK };
    }

    result.verb = WRONG;
    for (const auto &a : ans) {
        if (a.name == name && a.rotate == rotate && abs(a.x - x) <= 5 && abs(a.y - y) <= 5) {
            result.x = a.x;
            result.y = a.y;
            result.name = name;
            result.rotate = a.rotate;
            result.verb = OK;
        }
    }
    return result;
}
#else
submitter::SubmitResult submitter::submit(const char *name, int x, int y, int rotate) {
    submitter::SubmitResult result {};
    long long delay = lastSubmit + SUBMIT_DELAY_MS - millis();
    char verb[10];
    if (delay > 0) {
        printf("Have to wait %lld millis before submit\n", delay);
        std::this_thread::sleep_for(std::chrono::milliseconds(delay));
    }
    sprintf(sock_buff, "%s %d %d %d\n", name, x, y, rotate);
    printf(">> %s", sock_buff);
    send(sock_fd, sock_buff, strlen(sock_buff), 0);
    ssize_t len = recv(sock_fd, sock_buff, MAX_BUFF, 0);
    sock_buff[len] = 0;
    printf("<< %s", sock_buff);
    sscanf(sock_buff, "%s %d %d", verb, &x, &y);
    if (verb[0] == 'O') {
        result.name = name;
        result.x = x;
        result.y = y;
        result.rotate = rotate;
        result.verb = OK;
    } else if (strstr(sock_buff, "run rate")) {
        result.verb = RETRY;
    } else {
        result.verb = WRONG;
    }
    lastSubmit = millis();
    return result;
}
#endif
