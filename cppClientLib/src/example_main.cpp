#include "../cppzmq/zmq.hpp"
#include "Client.h"
#include "Server.h"
#include <iostream>
int main(int argc, char** argv) {
	if (argc == 1) {
		printf("no argvs passed\n");
		Client client;
		client.connect("tcp://127.0.0.1:5555");
		const MotionSpeed speed(1.0f, 1.0f);
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
	std::string arg = argv[1];
	Dprintf("arg = %s", arg.c_str());
	if (arg == "--client") {
		Client client;
		client.connect("tcp://127.0.0.1:5555");
		client.sendBuffer("something.txt");
	} else if (arg == "--server") {
		Server server;
		server.bind("tcp://127.0.0.1:5555");
		while(server.listenForCommand()) {}
	} else if (arg == "--help") {
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
			<<"used for transfering images and buffers, as mentioned before\n";
	} else {
		printf("could not recognize command line argv!\nsupported args are -> \n--client\n--server\n");
		return -1;
	}
	return 0;
}
