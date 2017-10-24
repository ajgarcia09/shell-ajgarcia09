#ifndef MyTocIncluded
#define MyTocIncluded

//counts how many words in the input
int countWords(char * str, char delim);

/*allocates each token in an array and
  returns a pointer to this array*/ 
char ** mytoc(char *str, char delim);

//counts the length of each token and allocates it in the array
char ** allocateTokens(char ** tokenVec, char *str,char delim);

//prints all tokens allocated in the array
void printTokenVec(char ** tokenVec, int wordCount);

//calculates the length of the each token in order to print it
int lengthOfTokenArray(char * str);

//compares two strings and returns 1 if both strings are equal.
//used to exit program.
int compStrings(char *str1, char *str2);

#endif
