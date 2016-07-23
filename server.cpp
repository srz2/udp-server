#include <iostream>		//Main IO Functions
#include <string.h>		//Enables usage of bzero
#include <stdio.h>		//Enables printf()

#include <sys/socket.h>		//Socket Functions
#include <sys/types.h>
#include <netinet/in.h>		//Enables usage of struct sockaddr_in
#include <arpa/inet.h>		//Enables inet_addr
#include <unistd.h>		//Makes closing socket possible
#include <cstdlib>		//Makes exit possible
#include <errno.h>		//Enables errno

using namespace std;

#define BUF_SIZE	100

int main()
{
	int sock = -1;
	if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
	{
		cout << "Cannot create socket" << endl;
		exit(1);
	}

	struct sockaddr_in local;
	bzero(&local, sizeof(local));
	local.sin_family = AF_INET;
	local.sin_addr.s_addr = htonl(INADDR_ANY);
	local.sin_port = htons(1234);

	if (bind(sock, (struct sockaddr *)&local, sizeof(local)) < 0)
	{
		cout << "Cannot bind socket" << endl;
		exit(1);
	}

	struct sockaddr_in dest_remote;
	bzero(&dest_remote, sizeof(dest_remote));
	dest_remote.sin_family = AF_INET;
	dest_remote.sin_port = htons(12345);
	inet_pton(AF_INET, "238.0.0.1", &dest_remote.sin_addr);
	//cout << dest_remote.sin_addr.s_addr << endl;

	char str[BUF_SIZE];
	memset(str, '\0', BUF_SIZE);
	inet_ntop(AF_INET, &dest_remote.sin_addr, str, INET_ADDRSTRLEN);
	cout << "Remote IP: " << str << endl;

	char * msg = new char[BUF_SIZE];
	memset(msg, '\0', BUF_SIZE);
	strcpy(msg, "Hello! I am a message");

	while(1)
	{
		//printf("%d - %s\n", strlen(msg), msg);
		int returnValue = sendto(sock, msg, strlen(msg) + 1, 0, (struct sockaddr *)&dest_remote, sizeof(dest_remote));
		if (returnValue < 0)
		{
			cout << "Return value: " << returnValue << endl;
			int error = errno;
			string error_str = strerror(error);
			cout << error_str << endl;
			break;
		}
		sleep(1);
	}

	close(sock);
}
