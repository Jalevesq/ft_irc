#include "./include/Server.hpp"
#include <iostream>

using std::cerr;
using std::endl;

int main(int argc, char **argv) {
	// SET LE PASSWORD OBLIGATOIRE AVANT DE PUSH
	if (argc < 2){
		cerr << "Wrong number of argument" << endl;
		return 1;
	}
	try{
		Server server;
		server.initServer(argv);
		server.serverRun();
	} catch (std::exception &e){
		cerr << e.what() << endl;
	}
	return 0;
}