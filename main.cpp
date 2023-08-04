#include "./include/Server.hpp"
#include <iostream>
#include <csignal>

using std::cerr;
using std::endl;

bool g_serverStop = false;

static void stop(int sigHandler){
	(void)sigHandler;
	g_serverStop = true;
}

int main(int argc, char **argv) {
	if (argc < 3){
		cerr << "./irc <port> <password>" << endl;
		return 1;
	}
	signal(SIGINT, stop);
	signal(SIGQUIT, SIG_IGN);
	try{
		Server server;
		server.initServer(argv);
		server.serverRun();
	} catch (std::exception &e){
		cerr << e.what() << endl;
	}
	return 0;
}