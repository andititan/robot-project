#include "Client.h"
#include <cstdlib>
#include <thread>

void executeFunction(const char* exec) {
    system(exec);
}

int main(int argc, char** argv) {
    const char* exec = "python ../../python/Server.py";
    std::thread tr(&executeFunction, exec);
    Client client;
    const Result (Client::*functPonter[])(const MotionSpeed&) = {
        &Client::setMotorCommand,
        &Client::stopCommand,
        &Client::deactivate
    };
    client.connect("tcp://127.0.0.1:5555");
    for (int i = 0; i < 7; i++) {
        const Result res = (client.*functPonter[i])(MotionSpeed{0.5, 1.0f});
        if (res == Result::FailedToSend) {
            printf("failed to send\n");
        }
    }
    tr.join();
    return 0;
}