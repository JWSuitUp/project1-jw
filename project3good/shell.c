char ch[300];
main(){
    while (1) {
        interrupt(0x21,0,"Shell> ",0,0);
        interrupt(0x21,0x01,ch,0,0 );
        interrupt(0x21,0,"Unrecognized command \n ",0,0);
    }
}
