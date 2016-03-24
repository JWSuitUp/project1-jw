//
//  userlib.h
//  
//
//  Created by Joanna Wang on 3/23/16.
//
//

#ifndef userlib_h
#define userlib_h
void printString(char *string);
void readChar();
void readString(char *buf);
void readfile(char *filename, char *buf);
void executeProgram(char* name, int segment);
void terminate();


#endif /* userlib_h */
