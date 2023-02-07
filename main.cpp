#include "Client.h"
#include <cstdlib>
#include <thread>
#include <iostream>
#include <unistd.h>

void executeFunction(const char* exec) {
    system(exec);
}
struct PythonScript {
    PythonScript(const bool usePython) {
        this->usePython = usePython;
        const char* exec = "python ../../python/Server.py";
        if(usePython) {
            tr = std::thread(&executeFunction, exec);
        }
    }
    ~PythonScript() {
        if(usePython) {
            tr.join();
        }
    }
private:
    std::thread tr;
    bool usePython = false;
};

int main(int argc, char** argv) {
    bool startPython = false;
    int opt = 0;
#ifdef _WIN32
    startPython = true;
#else
    while ((opt = getopt(argc, argv, "h:s")) != -1) {
        switch (opt) {
            case 'h':
                std::cout
                    << "\nDESCRIPTION:\n"
                    <<"------------\n"
                    <<"Example application demonstrating how to use RobotMovementClientServer\n"
                    <<"\n\n"
                    <<"--client starts the client and connects to 127.0.0.1 on port :5555\n"
                    <<"can be used for transfering images, buffers, robot movement speed\n"
                    <<"image and buffers transfer supported for cpp Server, for now.\n"
                    <<"Movement speed supported for python server\n\n"
                    <<"--server starts the server part and connects to 127.0.0.1 on port :5555\n"
                    <<"used for transfering images and buffers, as mentioned before\n"
                    <<"client and server can be used in example main\n, to run it enable STAND_ALONE in cppClientLib/CMakeLists.txt\n"
                    <<"here only --startPython can be used, to start the server on new thread, with no need to run the script from new terminal\n";
                exit(0);
            case 's':
                startPython = true;
                break;
            default:
                printf("could not recognize command line argv!\nsupported args are -> \n--client\n--server\n");
                exit(-1);
        }
    }
#endif
    PythonScript ps(startPython);
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
    return 0;
}