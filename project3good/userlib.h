#ifndef USER_LIB
#define USER_LIB
void printString(char *string);
//void readChar();
void readString(char *buf);
void readfile(char *filename, char *buf);
void executeProgram(char* name, int segment);
void terminate();


#endif /* userlib_h */
