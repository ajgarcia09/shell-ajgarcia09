#include <stdio.h>
#include "myToc.h"
#include "shell.h"
#include <sys/types.h>//for read
#include <unistd.h>//for read
#include <sys/stat.h>//for stat
#include <fcntl.h> //for read
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>

#define BUFLEN 1024

void freeTokens(char ** tokenVec){
  while(*tokenVec){
    free(*tokenVec);
    tokenVec++;
  }
 }

char * concatStrings(char * str1, char * str2){
  printf("entered concatStrings\n");
  printf("str1: %s\n",str1);
  printf("str2: %s\n", str2);
  int newStringSize =lengthOfTokenArray(str1)+lengthOfTokenArray(str2)+2;
  printf("newStringSize %d\n", newStringSize);
  char * newStr = malloc(newStringSize);
  int i =0;  
  while(str1[i]){
    newStr[i] = str1[i];
    printf("current newStr: %c\n", newStr[i]);
    i++;
  }
  newStr[i] = '/'; 
  i++;
  int j =0;
  while(str2[j]){
    newStr[i] = str2[j];
    printf("current newStr: %c\n", newStr[j]);
    j++;
    i++;
  }
  newStr[i] = '\0';
  printf("newStr: %s\n", newStr);
  return newStr;
}
  
    
char ** getPathList(char ** envp){
  printf("in getPath\n");
  char ** tokens; 
  for(int i = 0; envp[i]; i++){
    tokens = mytoc(envp[i], '=');
    if(compStrings(tokens[0],"PATH")){
      break;
    }
    freeTokens(tokens);
    free(tokens);
   }
  char ** path = mytoc(tokens[1], ':');
  return path;
  }

char ** updateInputList(char ** inputList, char * command){
  int commandSize = lengthOfTokenArray(command); //+ null char
  inputList[0] = '\0';
  inputList[0] = malloc(commandSize+1);
  int i =0;
  for(; i < commandSize; i++){
    inputList[0][i] = command[i];
  }
  inputList[0][i] = '\0';
  return inputList;

}
    


  /*argc, argv and envp are used to get environment
  variables used to find the PATH variable.*/

int main(int argc, char **argv, char **envp){
  for(;;){
    char input[BUFLEN];
    char * command;
    write(1,"[ajgarcia09 shell]$ ",19);
    int numBytesRead = read(0,input,BUFLEN);
    input[numBytesRead-1] = '\0'; //remove new line char
    if(compStrings(input,"exit")==1){
      break;  //exit program
    }
   //tokenize input string
   char ** inputList = mytoc(input, ' ');
   //absolute path was entered
   if(access(inputList[0], X_OK) == 0){
     char * command = inputList[0];
     printf("found command: %s\n",command);
     execve(command,inputList,envp);
     free(command);
   }
   else{//search for command in path list
     printf("didn't find command %s\n", inputList[0]);
     char ** path = getPathList(envp);
     int sizeOfInputListIndex = lengthOfTokenArray(inputList[0]);
     char * temp = (char*)malloc(sizeOfInputListIndex+1);
     for(int i = 0; i < sizeOfInputListIndex; i++){
       if(i == (sizeOfInputListIndex -1)){
	   temp[i] = '\0';
	 }
	 temp[i] = inputList[0][i];
      }
     
     for(int i =0; path[i]; i++){
       command = concatStrings( path[i],temp);
       printf("command: %s\n", command);
       inputList = updateInputList(inputList,command);
       execve(command,inputList,envp);
       free(command);
       //printf("new inputList[0]: %s\n",inputList[0]);
       // command2 = concatStrings(command,inputList[0]);
       //printf("command2 %s\n",command2);
    }

  pid_t  pid = fork();
   if(pid == 0){ //child is running
     execve(command, inputList,envp);
   }
   else{
     wait(NULL);
     freeTokens(inputList);
     free(inputList);
   }
  }
  }
}
     

       
