#include <sys/socket.h>
#include <arpa/inet.h>
#include <cstring>
#include <iostream>
#include <chrono>
#include <thread>

#include "submitter.h"

using namespace std::chrono;

const int MAX_BUFF = 1995;
const int SUBMIT_DELAY_MS = 200;

int sock_fd = 0;
char sock_buff[MAX_BUFF];
long long lastSubmit = 0;

inline long long millis() {
    return duration_cast< milliseconds >(system_clock::now().time_since_epoch()).count();
}

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

bool submitter::disconnect() {
    shutdown(sock_fd, SHUT_RDWR);
    return true;
}

submitter::SubmitResult submitter::submit(const char *name, int x, int y, int rotate) {
    long long delay = lastSubmit + SUBMIT_DELAY_MS - millis();
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
    lastSubmit = millis();
    return submitter::SubmitResult();
}

