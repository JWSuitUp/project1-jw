
#include "userlib.h"

char ch[300];
char buf[300];
char filename[6];
char filename2[6];
int numSectors = 0;
main(){
    while (1) {
//      interrupt(0x21,0x00,"\n",0,0);
//      interrupt(0x21,0x00,"Shell> ",0,0);
//      interrupt(0x21,0x01,ch,0,0 );
        //printString("\n");
        printString("Shell> ");
        readString(ch);
        
        if(ch[0]== 't' && ch[1] == 'y'&& ch[2] == 'p' && ch[3] == 'e'){
            int i = 0;
            filename[0]= ch[5];
            filename[1]= ch[6];
            filename[2]= ch[7];
            filename[3]= ch[8];
            filename[4]= ch[9];
            filename[5]= ch[10];
            interrupt(0x21,0x00,filename,0,0);

//            interrupt(0x21,0x03,filename,buf,0);
//            interrupt(0x21,0x00,buf,0,0 );
            readfile(filename,buf);
            printString(buf);
            
        }
        else if(ch[0]== 'e' && ch[1] == 'x'&& ch[2] == 'e' && ch[3] == 'c' && ch[4] == 'u'&& ch[5] == 't' && ch[6] == 'e'){
            filename[0]= ch[8];
            filename[1]= ch[9];
            filename[2]= ch[10];
            filename[3]= ch[11];
            filename[4]= ch[12];
            filename[5]= ch[13];
            //interrupt(0x21,0x00,filename,0,0);
            //interrupt(0x21,0x04,filename,0x2000,0);
            //interrupt(0x21, 0x04, "uprog1\0", 0x2000, 0);
            executeProgram(filename,0x2000);
        }
        else if(ch[0] == 'd' && ch[1] == 'e'&& ch[2] == 'l' && ch[3] == 'e' && ch[4] == 't'&& ch[5] == 'e'){
            filename[0]= ch[7];
            filename[1]= ch[8];
            filename[2]= ch[9];
            filename[3]= ch[10];
            filename[4]= ch[11];
            filename[5]= ch[12];
            if(deleteFile(filename) == -1){
                printString("File not found");
            }
        }
        
        else if(ch[0] == 'c' && ch[1] == 'o'&& ch[2] == 'p' && ch[3] == 'y'){
            filename[0]= ch[5];
            filename[1]= ch[6];
            filename[2]= ch[7];
            filename[3]= ch[8];
            filename[4]= ch[9];
            filename[5]= ch[10];
            
            filename2[0]= ch[12];
            filename2[1]= ch[13];
            filename2[2]= ch[14];
            filename2[3]= ch[15];
            filename2[4]= ch[16];
            filename2[5]= ch[17];
            
            numSectors = readfile(filename, buf);
            //numSectors = 1;
            if(numSectors == 1){
                printString("File not found");
            }
            else if(writeFile(filename2,buf, numSectors-1) == -1){
                printString("Disk directory is full");
            }
            else if(writeFile(filename2,buf, numSectors-1) == -2){
                printString("Disk is full");
            }
            
        }
        else if(ch[0] == 'd' && ch[1] == 'i'&& ch[2] == 'r'){
            
            
        }
        else{
            interrupt(0x21,0,"Unrecognized command \n ",0,0);
        }
    }
}
