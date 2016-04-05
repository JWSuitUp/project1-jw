#include "userlib.h"

void printString(char *string){
    interrupt(0x21,0x00,string,0,0);
}
//void readChar(){
//    interrupt(0x21,0x11,ch,0,0);
//}
void readString(char *buf){
    interrupt(0x21,0x01,buf,0,0);
}
void readfile(char *filename, char *buf){
    interrupt(0x21,0x03,filename,buf,0);
}
void executeProgram(char* name, int segment){
    interrupt(0x21,0x04,name,segment,0);
}
void terminate(){
    interrupt(0x21,0x05,0,0,0);
}
void deleteFile(){
    interrupt(0x21, 0x07, char *fname, 0, 0);
}
void writeFile(){
    interrupt(0x21, 0x08, char *fname, char *buffer, int sectors);
}