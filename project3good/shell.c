#include <stdio.h>
#include <userlib.h>
#include <userlib.c>

char ch[300];
char buf[300];
char filename[6];
char *job;
main(){
    while (1) {
        interrupt(0x21,0,"Shell> ",0,0);
        interrupt(0x21,0x01,ch,0,0 );

        if(ch[0]== 't' && ch[1] == 'y'&& ch[2] == 'p' && ch[3] == 'e'){
            
            interrupt(0x21,0,"print ",0,0);
            //filename[0]= ch[5];
            //interrupt(0x21,0,"again ",0,0);

//            filename[1]= ch[6];
//            filename[2]= ch[7];
//            filename[3]= ch[8];
//            filename[4]= ch[9];
//            filename[5]= ch[10];
//            interrupt(0x21,0,"fill ",0,0);
            
        }

        
        interrupt(0x21,0,"Unrecognized command \n ",0,0);
    }
}
