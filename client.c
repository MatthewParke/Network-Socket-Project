#include "csapp.h"

int fib(int n){
	if(n == 1 || n == 2){
		return 1;
	}
	else{
	   return fib(n-1) + fib(n-2);
	}
}

int main(int argc, char **argv){
	int clientfd, port;
	char *host;
	
	host = "elnux1.cs.umass.edu";
	port = 48579;


	clientfd = open_clientfd(host, port);
	if(clientfd < 0){
		printf("failed to connect to sever\n");
		close(clientfd);
		exit(0);
	}
	printf("Connected to server\n");
	
	FILE *file = fdopen(clientfd, "a+");

	fprintf(file,"27740990");
	printf("Sending Spire ID 27740990\n");

	char *line = NULL;
	size_t count;
	int result;
	result = getline(&line, &count, file);
	if(result < 0){
		printf("failed to recieve problem\n");
		free(line);
		fclose(file);
		close(clientfd);
		exit(0);
	}
	int fib_arg;
	count = sscanf(line, "FIB%d", &fib_arg);
	printf("Recieved Problem: FIB%d\n", fib_arg);
	
	free(line); line = NULL;
	fib_arg = fib(fib_arg);

	printf("Sending Solution: %d\n", fib_arg);
	fprintf(file, "%d", fib_arg);
	result = getline(&line, &count, file);
	if(result < 0){
		printf("FAILED: wrong solution\n");
		free(line);
		fclose(file);
		close(clientfd);
		exit(0); 
	}
	printf("SUCCESS: solution correct\n");

	printf("Sending Bonus Solution: HW9\n");
	fprintf(file, "HW9");

	result = getline(&line, &count, file);
	if(result < 0){
		printf("FAILED: wrong bonus solution\n");
		free(line);
		fclose(file);
		close(clientfd);
		exit(0);
	}
	printf("SUCCESS: bonus solution correct\n");

	free(line);
	fclose(file);
	close(clientfd);
	exit(0);

	return 0;
}