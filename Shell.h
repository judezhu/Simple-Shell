//shell.h
#ifndef SHELL_H
#define SHELL_H

#define MAX_ARGS 64
#define MAX_ARG_LENGTH 64
#define MAX_PATHS 64
#define MAX_FULLPATH_LENGTH 528  
#include<string>

using namespace std;

struct command_t
{
  char* fullpath;
  int argc;
  char* argv[MAX_ARGS];
  //string argv[MAX_ARGS];
};
void print_prompt();
//void read_command(string buffer);
void parse_command(string a, command_t &b );

char* lookup_path(char* argv[], string* dir);
int parse_path(string* dir);






#endif
