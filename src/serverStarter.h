#include <stdio.h>
#include <unistd.h>

void executeFunction(const char* exec) {
    system(exec);
}

struct ServerStarter {
    ServerStarter(const bool usePython) {
        this->usePython = usePython;
        const char* exec = "python ../python/Server.py";
        if(usePython) {
            tr = std::thread(&executeFunction, exec);
        }
        printf("execute");
    }
    ~ServerStarter() {
        if(usePython) {
            tr.join();
        }
    }
private:
    std::thread tr;
    bool usePython = false;
};

