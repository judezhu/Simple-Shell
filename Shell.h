//shell.h
#ifndef SHELL_H
#define SHELL_H

#define MAX_ARGS 64
#define MAX_ARG_LENGTH 64
#define MAX_PATHS 64
#define MAX_FULLPATH_LENGTH 528  
#define MAX_FILENAME_LENGTH 64
#include<string>

using namespace std;

struct command_t
{
  char* fullpath1;
  char* fullpath2;
  int argc;
  char* argv1[MAX_ARGS];
  char* argv2[MAX_ARGS];
  char* file1;
  char* file2;
 //string argv[MAX_ARGS];
};
void print_prompt();
//void read_command(string buffer);
void split_command(string cmd,string &cmd1, string &cmd2, bool *f);
//void parse_command_out(string a, command_t &b,bool *f );
void parse_command_out(string cm1, string cm2, command_t &b);
void parse_command_in(string cm1, string cm2, command_t &b);
void parse_command_normal(string cm1,command_t &b);
void parse_command_pipe(string cm1, string cm2, command_t &b);

//void parse_command_out(string a, command_t &b,bool *f );

char* lookup_path(char* argv[], string* dir);
int parse_path(string* dir);

//redirection out
void redirection_out_cmd(command_t cmd);
void normal_cmd(command_t cmd);
void pipe_cmd(command_t cmd);

#endif
