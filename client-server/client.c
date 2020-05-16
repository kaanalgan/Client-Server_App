#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <strings.h>

int main(int argc, char* argv[]){

	/*Getting inputs from user*/
	int firstOperand, secondOperand, result;
	printf("\nPlease enter first integer here: ");
	scanf("%d", &firstOperand);
	printf("\nPlease enter second integer here: ");
	scanf("%d", &secondOperand);
	int simpleSocket = 0;
	int simplePort = 0;
	int returnStatus = 0;
	struct sockaddr_in simpleServer;

	if(argc != 3){
		fprintf(stderr, "Usage: %s <server> <port>\n", argv[0]);
		exit(1);	
	}

	simpleSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if(simpleSocket == -1){
		fprintf(stderr, "Could not create a socket!\n");
		exit(1);
	}
	else{
		fprintf(stderr, "Socket created!\n");
	}

	simplePort = atoi(argv[2]);
	bzero(&simpleServer, sizeof(simpleServer));
	simpleServer.sin_family = AF_INET;
	inet_addr((char *)&(simpleServer.sin_addr.s_addr));
	simpleServer.sin_port = htons(simplePort);
	returnStatus = connect(simpleSocket, (struct sockaddr *)&simpleServer, sizeof(simpleServer));

	if(returnStatus == 0){
		fprintf(stderr, "Connection successful!\n");
	}

	else{
		fprintf(stderr, "Connection to the address failed!\n");
		close(simpleSocket);
		exit(1);	
	}
	/*Formatting the inputs for network transmission & sending them */
	firstOperand = htons(firstOperand);
	write(simpleSocket, &firstOperand, sizeof(int));
	secondOperand = htons(secondOperand);
	write(simpleSocket, &secondOperand, sizeof(int));
	returnStatus = read(simpleSocket, &result, sizeof(int));
	result = ntohs(result);

	if(returnStatus > 0){
		printf("Result of %d + %d : %d", ntohs(firstOperand), ntohs(secondOperand), result);
	}

	else{
		fprintf(stderr, "Return Status = %d \n", returnStatus);
	}

	close(simpleSocket);
	return 0;
}
