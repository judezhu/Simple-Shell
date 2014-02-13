//Shell.cpp
//source file for this program

#include<iostream>
#include"Shell.h"
#include<string>
#include<boost/algorithm/string.hpp>
#include<vector>

                                                                                                                                                                                     
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

//Parse the command
void parse_command(string a, command_t &b)
{
  vector <string> fields;
  split(fields,a,is_any_of(" "));
  fields.erase(remove_if(fields.begin(),fields.end(),[](string const& s) {return s.size()==0;}), fields.end());
  
  int i = 0;
  for(vector<string>::iterator it = fields.begin(); it!=fields.end(); it++)
  {
   b.argv[i]= (char*)((*it).c_str());
   i++;
  }
  b.argv[i] = NULL;
   
}

//Get the full path
char* lookup_path(char* argv_path[], string* dir)
{
  char* pName;//Pathname
  
  if(argv_path[0]!=NULL)
  //check if is already an absolute path name
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
  //cout << path_env_var;
  vector<string> fields;
  split(fields, path_env_var, is_any_of(":"));
   
  int i=0;
  for(vector<string>::iterator it = fields.begin(); it!=fields.end(); it++)
  {
    //cout <<*it<<endl;
    *it = *it+"/";
    dirs[i] = (char*)((*it).c_str());
    i++;
  }
  
  return 0;

}
