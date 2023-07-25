#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>
#include <poll.h>
#include <string>
#include <unistd.h>
#include <fcntl.h>
#include <iostream>
#define MAX_USER 10
// #define PORT 6690

using std::cout;
using std::endl;

int main(int ac, char **av) {
	if (ac != 2) {
		std::cerr << "./a.out <port>" << std::endl;
		return (1);
	}
	std::string name = "user";
	int lol = 0;
	int port = atoi(av[1]);
    struct sockaddr_in address;
    int currUserNbr = 0;
    struct pollfd mypoll[MAX_USER + 1];
    int connectionFd[MAX_USER];
    char buffer[1024];
    int addrlen;
    int fdSocket;
    // Open an empty socket
    fdSocket = socket(AF_INET, SOCK_STREAM, 0);
	fcntl(fdSocket, F_SETFL, O_NONBLOCK);
    // Assign port 6667 to struct
    address.sin_port = htons(port);
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = htonl(INADDR_A NY);
    addrlen = sizeof(address);
    // bind the empty socket to port 6667
    bind(fdSocket, (struct sockaddr*)&address, sizeof(address));
    // make the socket listen to new connection
    int listener = listen(fdSocket, MAX_USER);
    // Add the listener socket to the poll list
    mypoll[0].fd = fdSocket;
    mypoll[0].events = POLLIN;
    while (true) {
        int numReady = poll(mypoll, currUserNbr + 1, 100);
        if (numReady < 0) {
            std::cerr << "poll error" << std::endl;
            break;
        }
        // Check if there's a new incoming connection
        if (mypoll[0].revents & POLLIN) {
            int newFd = accept(fdSocket, (struct sockaddr*)&address, (socklen_t*)&addrlen);
            if (newFd < 0) {
                std::cerr << "accept error" << std::endl;
            }
            else
            {
                std::cout << "New connection accepted, socket fd: " << newFd << std::endl;
                currUserNbr++;
                mypoll[currUserNbr].fd = newFd;
                mypoll[currUserNbr].events = POLLIN;
                connectionFd[currUserNbr] = newFd;
				std::string welcomeMessage = "001 user :Welcome on ft_irc !\r\n";
				// std::string nickNameChange = ":user NICK Balls\r\n";
            	send(newFd, welcomeMessage.c_str(), welcomeMessage.size(), 0);
				// send(newFd, nickNameChange.c_str(), nickNameChange.size(), 0);
				// send(newFd, usernameMessage.c_str(), usernameMessage.size(), 0);
				
                // send(newFd, message, strlen(message), 0);
            }
        }
        // Check for data from existing connections
        for (int i = 1; i <= currUserNbr; i++) {
            if (mypoll[i].revents & POLLIN) {
                int ret = read(connectionFd[i], buffer, sizeof(buffer) - 1);
                if (ret <= 0) {
                    // Connection closed or error occurred
                    std::cout << "Connection closed or error occurred for socket fd: " << connectionFd[i] << std::endl;
                    close(connectionFd[i]);
                    mypoll[i].fd = -1;
                } else {
                    buffer[ret] = '\0';
					std::string sBuffer = buffer;
					if (sBuffer.find("NICK") != std::string::npos && lol < 1) {
						std::string newName = sBuffer.substr(5);
						std::string response = ":" + name + " NICK " + newName + "\r\n";
						send(mypoll[i].fd, response.c_str(), response.size(), 0);
						name = newName;
						continue ;
					}
					lol++;
                    std::cout << "Received from socket fd " << connectionFd[i] << ": " << buffer;
                }
            }
        }
    }
    // Close all active connections
    for (int i = 1; i <= currUserNbr; i++) {
        if (mypoll[i].fd != -1) {
            close(connectionFd[i]);
        }
    }
    close(fdSocket);
    return 0;
}