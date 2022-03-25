// Client side C/C++ program to demonstrate Socket programming 
#include <stdio.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
#include <string.h> 
#include <string>
#include <iostream>
using namespace std;

#define PORT 8080 



int main(int argc, char const *argv[]) 
{ 
	
	int sock = 0, valread; 
	struct sockaddr_in serv_addr; 
	char buffer[1024] = {0}; 
    string res;
	int choice=0;
	
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
	{ 
		printf("\n Socket creation error \n"); 
		return -1; 
	} 

	serv_addr.sin_family = AF_INET; 
	serv_addr.sin_port = htons(PORT); 
	
	// Convert IPv4 and IPv6 addresses from text to binary form 
	if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0) 
	{ 
		printf("\nInvalid address/ Address not supported \n"); 
		return -1; 
	} 


	if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
	{ 
		printf("\nConnection Failed \n"); 
		return -1; 
	} 


		printf("\n1.List Files\n2.Create File\n3.Edit File\n4.Delete File\n5.Exit\n");
	cin>>choice;

	switch(choice)
	{
		case 1:
		//system("./s.out");
                send(sock , "LIST_FILES", strlen("LIST_FILES") , 0 ); 
	        valread = read( sock , buffer, 1024); 
	        printf("%s\n",buffer);
	        break;

		case 2:
		//system("./s.out");
		printf("Enter file name : ");
		cin>>res;
		res=string("ADD_FILE~")+res;
		send(sock , res.c_str(), strlen(res.c_str()) , 0 );
                break;  

		case 4:
		//system("./s.out");
		printf("Enter file name : ");
		cin>>res;
		res=string("DELETE_FILE~")+res;
		send(sock , res.c_str(), strlen(res.c_str()) , 0 );
                break; 

		case 5:
                close(sock);
		exit(0);
	}

	return 0; 
} 
