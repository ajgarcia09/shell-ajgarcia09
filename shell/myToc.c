#include <stdio.h>
#include <sys/types.h>//for read
#include <unistd.h>//for read
#include <sys/stat.h>//for read
#include <fcntl.h> //for read
#include <stdlib.h>
#include <assert.h>
#include "myToc.h"

#define BUFLEN 1024

int countWords(char * str, char delim){
  int wordCount = 0;
  while(*str){
    while(*str == delim){
      str++;
    }
    if(*str != 0){
      wordCount++;
    }
    while(*str && (*str != delim)){
      str++;
    }
  }
  return wordCount;
 }

char * copyToken(char *str, int tokLength){
  /*copy each character from the current
    token in str into strCopy*/
  char * strCopy = (char *)malloc(tokLength +1);
  for(int i = 0; i< tokLength; i++){
    strCopy[i] = str[i];
  }
  strCopy[tokLength] = 0; //terminate copy
  return strCopy;
  
}
 
char ** allocateTokens(char ** tokenVec, char *str, char delim){

  int tokLength =0;
  int tokNum=0;
  char * temp;
 while(*str){
    if(*str != delim){
      tokLength++;
    }
    //found a delimiter
    else{
    temp = str-tokLength;    
    //storage for current token    
    tokenVec[tokNum] = (char *)malloc(tokLength+1);
    //and its 0 char terminator
    tokenVec[tokNum][tokLength] = '\0';
    tokenVec[tokNum] = copyToken(temp,tokLength);
    tokNum++; //go to the next token
    tokLength = 0; //reset token length
    }
    str++; //go to the next index
  }

 //allocate the token before the null terminating index
    temp = str-tokLength;    
    //storage for current token    
    tokenVec[tokNum] = (char *)malloc(tokLength+1);
    //and its 0 char terminator
    tokenVec[tokNum][tokLength] ='\0';
    tokenVec[tokNum] = copyToken(temp,tokLength);
    return tokenVec;
}

/*Used for calculating the length of the 
current token array from tokenVec 
that we want to print using printTokenVec*/
 
int lengthOfTokenArray(char * str){
  int length = 0;
  while(*str){
    length++; //increment counter while the string isn't empty
    str++;
  }
  return length;
 }

/*print each token in a new line */

void printTokenVec(char ** tokenVec, int wordCount){
  int numBytes = 0;
  for(int i = 0; i < wordCount; i++){
    numBytes = lengthOfTokenArray(tokenVec[i]);
     write(1,tokenVec[i],numBytes);
     write(1, "\n", 1);
    }
  }

 int compStrings(char *str1,char  *str2){

   while(*str1 && *str2){
     if(*str1 != *str2){
       return 0;
     }
     *str1++;
     *str2++;
   }
   return 1;
 }

 char ** mytoc(char *str, char delim){

 int wordCount = countWords(str, delim);
 
 char** tokenVec = (char **)calloc(wordCount+1,sizeof(char *));
 tokenVec[wordCount] = (char *)0;//zero pointer terminator
 tokenVec = allocateTokens(tokenVec, str, delim);
 printTokenVec(tokenVec,wordCount);
  
 return tokenVec; 
}
