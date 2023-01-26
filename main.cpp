#include "Client.h"
#include <cstdlib>
#include <thread>

void executeFunction(const char* exec) {
    system(exec);
}

int main(int argc, char** argv) {
    const char* exec = "python ../../python/Server.py";
    std::thread tr(&executeFunction, exec);
    const MotionSpeed speed(1.0f, 1.0f);
    Client client;
    client.connect("tcp://127.0.0.1:5555");
    for (int i = 0; i < 7; i++) {
        const Result res = client.setMotorCommand(speed);
        if (res == Result::FailedToSend) {
            printf("failed to send\n");
            break;
        }
    }
    client.stopCommand();
    client.disconnect();
    tr.join();
    return 0;
}