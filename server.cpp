// Server side C/C++ program to demonstrate Socket programming 
#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h>
#include <dirent.h> 
#include <string>
#include <iostream>
#include<fcntl.h>
#define PORT 8080 
using namespace std;

int main(int argc, char const *argv[]) 
{ 
	int server_fd, new_socket, valread; 
	struct sockaddr_in address; 
	int opt = 1; 
    int size=1;
    int readcycle=0;
	int addrlen = sizeof(address); 
	char buffer[1024] = {0};
    string fnames;
    DIR *d;
    struct dirent *dir;
    char *token;
    int fd;   
	d=opendir("/");  
	
	// Creating socket file descriptor 
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
	{ 
		perror("socket failed"); 
		exit(EXIT_FAILURE); 
	} 
	
	// Forcefully attaching socket to the port 8080 
	if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) 
	{ 
		perror("setsockopt"); 
		exit(EXIT_FAILURE); 
	} 
	address.sin_family = AF_INET; 
	address.sin_addr.s_addr = INADDR_ANY; 
	address.sin_port = htons( PORT ); 
	
	// Forcefully attaching socket to the port 8080 
	if (bind(server_fd, (struct sockaddr *)&address, 
								sizeof(address))<0) 
	{ 
		perror("bind failed"); 
		exit(EXIT_FAILURE); 
	}while(1){ 
	if (listen(server_fd, 3) < 0) 
	{ 
		perror("listen"); 
		exit(EXIT_FAILURE); 
	} 

	if ((new_socket = accept(server_fd, (struct sockaddr *)&address,(socklen_t*)&addrlen))<0) 
	{ 
		perror("accept"); 
		exit(EXIT_FAILURE); 
	} 
            listen(server_fd,3);	
           valread = read( new_socket , buffer, 1024); 
         if(strcmp(buffer,"LIST_FILES") == 0)
          {
			  
             if(d)
              {
               while((dir=readdir(d)) != NULL)
               { 
                  if(readcycle > 1)
                   {fnames += to_string(size) + string(" ") + string(dir->d_name) + string("\n");size++;}
                   else
                    {readcycle++;}
               }
              }
               send(new_socket , fnames.c_str() , fnames.size() , 0 );
               buffer[1024]={0}; 
            } 

			else if(strstr(buffer,"ADD_FILE") != NULL)
			{
                strtok_r(buffer, "~",&token);
				fd = creat(token, 0764);
			}

			else if(strstr(buffer,"DELETE_FILE") != NULL)
            {	           
			   strtok_r(buffer, "~",&token);
			   remove(token);
			}
                        //close(fd);
}
	return 0; 
} 
