
#include "userlib.h"

char ch[300];
char buf[300];
char filename[6];
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
        else{
            interrupt(0x21,0,"Unrecognized command \n ",0,0);
        }
    }
}
