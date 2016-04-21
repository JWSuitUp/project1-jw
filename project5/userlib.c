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
int readfile(char *filename, char *buf){
    interrupt(0x21,0x03,filename,buf,0);
}
void executeProgram(char* name, int segment){
    interrupt(0x21,0x04,name,segment,0);
}
void terminate(){
    interrupt(0x21,0x05,0,0,0);
}
void deleteFile(char *fname){
    interrupt(0x21,0x07,fname,0,0);
}
void writeFile(char *fname, char *buffer, int sectors){
    interrupt(0x21, 0x08,fname,buffer,sectors);
}
void yield(){
    interrupt(0x21, 0x09,0,0,0);
}
void showProcesses(){
    interrupt(0x21, 0x0A,0,0,0);
}
int kill(int segment){
    interrupt(0x21,0x0B,segment,0,0);
}
