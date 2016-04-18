main() {
    char buf[300];
    interrupt(0x21,0,"Please enter a file name",0,0);
    interrupt(0x21,0x01,buf,0,0);
//    while (the user doesn't enter Control D) {
//
//    }
    while(1);

 
}
