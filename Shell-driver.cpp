//Shell-driver.cpp
//driver for Shell program

#include<iostream>
#include<string>
#include"Shell.h"
#include<cstring>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<sys/types.h>
#include<sys/wait.h>


using namespace std;

int main()
{

  string command_line = ""; //command_line from user 
                       //and save it in a string  
  
  command_t command; //command structure includes 
                     //full path name and all the parameters
   
  //struct command_t initialization
  command.fullpath1 = (char*) malloc(MAX_FULLPATH_LENGTH);
  command.fullpath2 = (char*) malloc(MAX_FULLPATH_LENGTH);
  command.file1 = (char*) malloc(MAX_FILENAME_LENGTH);
  command.file2 = (char*) malloc(MAX_FILENAME_LENGTH);

  for(int i=0; i<MAX_ARGS; i++)
  {
    command.argv1[i] =(char*) malloc(MAX_ARG_LENGTH);
  }
  
  for(int i=0; i<MAX_ARGS; i++)
  {
    command.argv2[i] =(char*) malloc(MAX_ARG_LENGTH);
  }
 
  //Get all directories from PATH env var
  //and store them in a string array
  string pathv[MAX_PATHS]; 
  parse_path(pathv);
  
  pid_t pid;
  bool flag[5];
  string cmd_1, cmd_2; 

  //int rv; 
  //int x;

  while(true)
  {
    //Read the command line
    flag[0] = false;//background_cmd;
    flag[1] = false;//pipe_cmd;
    flag[2] = false;//redirection_in;
    flag[3] = false;//redireciton_out
    flag[4] = false;//normal_cmd; 
    print_prompt();
    std::getline(cin,command_line);

    //Quit the shell
    if(command_line.compare("exit")==0 || command_line.compare("quit")==0)
    {
      break;
    }
  
    split_command(command_line, cmd_1, cmd_2,flag);    
  
    if(flag[4]==true)
    {
      //cout << "flag4 here"<<endl;
      parse_command_normal(cmd_1,command); 
      command.fullpath1 = lookup_path(command.argv1, pathv);
      if(command.fullpath1!=NULL)
      {
        normal_cmd(command);		
      }
    }
   
    //After checking, this is > 
    else if(flag[3]==true)
    {
      //cout << "here"<<endl; 
      parse_command_out(cmd_1, cmd_2, command); 
      command.fullpath2 = lookup_path(command.argv2,pathv);
      //cout << comm 
      if(command.fullpath2!=NULL)
      {
        //cout<<"good"<<endl;
        redirection_out_cmd(command);		
      }

    }
    //After checking,this is < 
    else if(flag[2]==true)
    {
      //cout << "here"<<endl; 
      parse_command_out(cmd_1, cmd_2, command); 
      command.fullpath1 = lookup_path(command.argv1,pathv);
      //cout << comm 
      if(command.fullpath1!=NULL)
      {
        //cout<<"good"<<endl;
       // redirection_in_cmd(command);		
      }

    }

    //After checking, this is a pipe
    else if(flag[1]==true)
    {
      cout << "here"<<endl; 
      parse_command_pipe(cmd_1, cmd_2, command); 
      //char*  s10  = (char*) malloc(MAX_FULLPATH_LENGTH);
      //char*  s20  = (char*) malloc(MAX_FULLPATH_LENGTH);
 // command.fullpath2 = (char*) malloc(MAX_FULLPATH_LENGTH);
     // command.fullpath1= lookup_path(command.argv1,pathv);
     // command.fullpath2= lookup_path(command.argv2,pathv);
      
      //cout << comm 
     // if((command.fullpath1!=NULL)&&(command.fullpath2!=NULL))
     // {
    // cout << "m1 "<< s10;
    // cout<<  "m2 "<< s20;
      //  cout<<"good"<<endl;
        pipe_cmd(command);		
     // }

    }

    else
    {
      continue;
    }
  }//while
    //free dynamic memory 
  free(command.fullpath1); 
  free(command.fullpath2); 
  //free(command.file1); 
  //free(command.file2); 
  
  for(int i=0; i<MAX_ARGS;i++)
  {
    free(command.argv1[i]);  
  }
  for(int i=0; i<MAX_ARGS;i++)
  {
    free(command.argv2[i]);  
  }

return 0;
}









