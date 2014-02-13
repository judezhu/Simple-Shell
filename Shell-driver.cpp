//Shell-driver.cpp
//driver for Shell program

#include<iostream>
#include<string>
#include"Shell.h"
#include<cstring>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>

using namespace std;

int main()
{

  string command_line; //command_line from user 
                       //and save it in a string  
  
  command_t command; //command structure includes 
                     //full path name and all the parameters
 
  //struct command_t initialization
  command.fullpath = (char*) malloc(MAX_FULLPATH_LENGTH);
  for(int i=0; i<MAX_ARGS; i++)
  {
    command.argv[i] =(char*) malloc(MAX_ARG_LENGTH);
  }
 
  //Get all directories from PATH env var
  //and store them in a string array
  string pathv[MAX_PATHS]; 
  parse_path(pathv);
  
  int status; 
    
  while(true)
  {
    //Read the command line
    print_prompt();
    std::getline(cin,command_line);

    //Quit the shell
    if(command_line.compare("exit")==0 || command_line.compare("quit")==0)
    {
      break;
    }

//   if(command_line.compare("NULL"))

//     {
//       continue;
//     }
  
    //Parse the command line, 
    parse_command(command_line, command);  
   
    //Get the full path name
    command.fullpath = lookup_path(command.argv, pathv);
    if(command.fullpath!=NULL)
    { 
      if(fork()==0)
      {
        
       status = execve(command.fullpath, command.argv, NULL);
       break;
      }
     
      else
      {
        wait(status);
      }

    }
    else
    {
      cout<<"Coudn't find this command!"<<endl;
    }
  }
    //free dynamic memory 
  free(command.fullpath); 
  for(int i=0; i<MAX_ARGS;i++)
  {
    free(command.argv[i]);  
  }

return 0;
}









