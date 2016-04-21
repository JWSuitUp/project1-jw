#ifndef USER_LIB
#define USER_LIB
void printString(char *string);
//void readChar();
void readString(char *buf);
int readfile(char *filename, char *buf);
void executeProgram(char* name, int segment);
void terminate();
void deleteFile(char *fname);
void writeFile(char *fname, char *buffer, int sectors);
void yield();
void showProcesses();
int kill(int segment);
#endif /* userlib_h */
