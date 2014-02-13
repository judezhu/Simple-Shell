//Shell.cpp
//source file for this program

#include<iostream>
#include"Shell.h"
#include<string>
#include<boost/algorithm/string.hpp>
#include<vector>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>    
#include<sys/wait.h>

using namespace std;
using namespace boost;

//Print out the prompt
void print_prompt()
{
  string prompt = "mini shell >";
  cout <<prompt;
}

//Read the command
void read_command(string buffer)
{
  std::getline(cin,buffer);
}

void split_command(string cmd, string &cmd1, string &cmd2, bool* f)
{
 // size_t index;
  int index;
  
  if((index = cmd.find("&"))!=string::npos)
  {
    f[0] = true;
    cmd1 = cmd.substr(0,index);
  }

  //check whether there is a pipe symbol
  else if((index = cmd.find("|"))!=string::npos)
  {
    f[1] = true;
    cmd1 = cmd.substr(0,index);
    cmd2 = cmd.substr(index+1);
  }
  
  else if((index = cmd.find("<"))!=string::npos)
  {
    f[2] = true;
    cmd1 = cmd.substr(0,index);
    cmd2 = cmd.substr(index+1);
    
  }
  //check whether there is a "out" redirection
  else if((index = cmd.find(">"))!=string::npos)
  {
    f[3] = true;
    cmd1 = cmd.substr(0,index);
    cmd2 = cmd.substr(index+1);
  }
  else
  {
    f[4] = true;
    cmd1 = cmd;
  }

}

// parse the command to do the redirection out
// precondition: 
// postcondition: 
void parse_command_out( string cm1, string cm2, command_t &b )
{
    //Split the command line by spaces, and store all the words in a string vector
  vector <string> fields1;
  split(fields1,cm1,is_any_of(" "));
  fields1.erase(remove_if(fields1.begin(),fields1.end(),[](string const& s) {return s.size()==0;}), fields1.end());
  int i = 0; 
  for(vector<string>::iterator it = fields1.begin(); it!=fields1.end(); it++)
  {
     b.argv2[i] = (char*)((*it).c_str());
     cout << (*it);
     cout << b.argv2[i];
     i++;
     
  }
  b.argv2[i] = NULL;

  vector <string> fields2;
  split(fields2,cm2,is_any_of(" "));
  fields2.erase(remove_if(fields2.begin(),fields2.end(),[](string const& s) {return s.size()==0;}), fields2.end());
  
  vector<string>::iterator it = fields2.begin(); 
  b.file2= (char*)((*it).c_str());
  cout << b.file2 <<endl;
}

// parse the command to do the redirection out
// precondition: 
// postcondition: 
void parse_command_in( string cm1, string cm2, command_t &b )
{
    //Split the command line by spaces, and store all the words in a string vector
  vector <string> fields1;
  split(fields1,cm1,is_any_of(" "));
  fields1.erase(remove_if(fields1.begin(),fields1.end(),[](string const& s) {return s.size()==0;}), fields1.end());
  int i = 0; 
  for(vector<string>::iterator it = fields1.begin(); it!=fields1.end(); it++)
  {
     b.argv1[i] = (char*)((*it).c_str());
     cout << (*it);
     cout << b.argv1[i];
     i++;
     
  }
  b.argv1[i] = NULL;

  vector <string> fields2;
  split(fields2,cm2,is_any_of(" "));
  fields2.erase(remove_if(fields2.begin(),fields2.end(),[](string const& s) {return s.size()==0;}), fields2.end());
  
  vector<string>::iterator it = fields2.begin(); 
  b.file1= (char*)((*it).c_str());
  cout << b.file1 <<endl;
}

// parse the command to do the pipe 
// precondition: 
// postcondition: 
void parse_command_pipe( string cm1, string cm2, command_t &b )
{
    //Split the command line by spaces, and store all the words in a string vector
  vector <string> fields1;
  split(fields1,cm1,is_any_of(" "));
  fields1.erase(remove_if(fields1.begin(),fields1.end(),[](string const& s) {return s.size()==0;}), fields1.end());
  int i = 0; 
  for(vector<string>::iterator it = fields1.begin(); it!=fields1.end(); it++)
  {
     b.argv1[i] = (char*)((*it).c_str());
     i++;
     
  }
  b.argv1[i] = NULL;

  vector <string> fields2;
  split(fields2,cm2,is_any_of(" "));
  fields2.erase(remove_if(fields2.begin(),fields2.end(),[](string const& s) {return s.size()==0;}), fields2.end());
  int j = 0; 
  for(vector<string>::iterator it = fields2.begin(); it!=fields2.end(); it++)
  {
     b.argv2[j] = (char*)((*it).c_str());
     j++;
     
  }
  b.argv2[j] = NULL;

}


// parse the command to do the normal command
// precondition: 
// postcondition: 
void parse_command_normal( string cm1, command_t &b )
{
    //Split the command line by spaces, and store all the words in a string vector
  vector <string> fields1;
  split(fields1,cm1,is_any_of(" "));
  fields1.erase(remove_if(fields1.begin(),fields1.end(),[](string const& s) {return s.size()==0;}), fields1.end());
  int i = 0; 
  for(vector<string>::iterator it = fields1.begin(); it!=fields1.end(); it++)
  {
     b.argv1[i] = (char*)((*it).c_str());
     i++;
  }
  b.argv1[i] = NULL;

}



//Get the full path
char* lookup_path(char* argv_path[], string* dir)
{
  char* pName;//Pathname
  
  if(argv_path[0]!=NULL)
  //check if is already an absolute path name, the ASCII code for "/"
  // is 47 
  {
    if(argv_path[0][0]==47) 
    {
      pName = argv_path[0];
      if(access(pName,0)!=(-1))
      {
        return pName;
      }
      else
      {
        return NULL;
      }
    }
  
    //search directories in PATH
    else
    {
      for(int i=0; i<MAX_PATHS;i++)
      {
        pName = (char*)((dir[i]+argv_path[0]).c_str());
        if (access(pName,0)!=(-1))
        {
          return pName;
        }
        
      }
      
      return NULL;
    }
  }
  
  else
  {
    return NULL;
  }
}

//Get all the path variables in PATH env
int parse_path(string* dirs)
{
  string path_env_var;
  string the_path;

  for(int i=0; i < MAX_ARGS; i++)
  {
   // dirs[i] = NULL;
  }

  path_env_var = getenv("PATH");
  vector<string> fields;
  split(fields, path_env_var, is_any_of(":"));
   
  int i=0;
  for(vector<string>::iterator it = fields.begin(); it!=fields.end(); it++)
  {
    *it = *it+"/";
    dirs[i] = (char*)((*it).c_str());
    i++;
  }
  
  return 0;

}


// the function for execute the redirection out 
void redirection_out_cmd(command_t cmd)
{
  int fd;
  int fds[2];//2 file discriptors

  pipe(fds);
  char c;
  int count; // count the number of char read from the stdin of the pipe;
  pid_t pid;

  //child process #1
  if(fork()==0)
  {
    cout << "hey"<<endl;
    fd = open(cmd.file2,O_WRONLY | O_CREAT,0775);
    if (fd < 0)
    {
      cout<< "There is an error to open/create a file!"<<endl;
      return;
    }

    dup2(fds[0],0);

    //Don't need the stdout end of the pipe;
    close(fds[1]);
    while((count=read(0, &c, 1))>0)
    {
       write(fd, &c, 1);
    }
    execlp("echo", "echo", NULL); 
  }
  
  else
  {
    pid=fork();
    switch(pid) 
    {
      case -1:
          perror("fork");

       case 0:
          cout << "hey" <<endl;
          dup2(fds[1], 1);
          //Don't need the stdin end of the pipe;
          close(fds[0]);
	  execve(cmd.fullpath2, cmd.argv2, NULL);
      default:
	  waitpid(pid,NULL,0);
     }
  }
}

// the function for execute the redirection in
void redirection_in_cmd(command_t cmd)
{
  int fd;
  int fds[2];//2 file discriptors

  pipe(fds);
  char c;
  int count; // count the number of char read from the stdin of the pipe;
  pid_t pid;

  //child process #1
  if(fork()==0)
  {
    cout << "hey"<<endl;
    fd = open(cmd.file2,O_RDWR | O_CREAT,0666);
    if (fd < 0)
    {
      cout<< "There is an error to open/create a file!"<<endl;
      return;
    }
    
    
    dup2(fds[1],1);

    //Don't need the stdin end of the pipe;
    close(fds[0]);
    while((read(fd, &c, 1))>0)
    {
    }
    execlp("echo", "echo", NULL); 
  }
  
  else
  {
    pid=fork();
    switch(pid) 
    {
      case -1:
          perror("fork");

       case 0:
          cout << "hey" <<endl;
          dup2(fds[1], 1);
          close(fds[0]);
	  execve(cmd.fullpath2, cmd.argv2, NULL);
      default:
	  waitpid(pid,NULL,0);
     }
  }
}
//the function to execute a normal command without a special feature
void normal_cmd(command_t cmd)
{
      int x;
      pid_t pid;
      pid = fork();
      switch(pid)
      {
        case -1:
            perror("fork");
        case 0:
            execve(cmd.fullpath1, cmd.argv1, NULL);
        default:
            waitpid(pid,NULL,0);

       }
} 

// the function for execute the redirection out 
void pipe_cmd(command_t cmd)
{
  int fds[2];//2 file discriptors

  pipe(fds);
  pid_t pid;

  //child process #1
  if(fork()==0)
  {
    cout << "pipe back"<<endl;
    close(fds[1]);
    dup2(fds[0],0);
    close(fds[0]);
    //Don't need the stdout end of the pipe;
    execve(cmd.fullpath2, cmd.argv2, NULL);
    
  } 


  
  else
  {
    pid=fork();
    switch(pid) 
    {
      case -1:
          perror("fork");

       case 0:
          close(fds[0]);
          dup2(fds[1], 1);
          //Don't need the stdin end of the pipe;
          close(fds[1]);
	  execve("/bin/ls", cmd.argv1, NULL);
      default:
	  waitpid(pid,NULL,0);
     }
  }
}
