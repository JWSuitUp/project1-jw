//kernel.c
//author: Joanna Wang
//Date: 2/25/2016
//prototype 
void putChar(char letter, int row, int col, int color);
void putString(char* letter, int row, int col, int color);
int printString(char *str);
int readChar();
int readString(char *buf);
int readSector(char *buf, int absSector);
int handleInterrupt21(int ax, int bx, int cx, int dx);

//main method
int main(){
    
    char * buf = "***********************";
    char ch;
    int fullCh;
    char scanCode;
    
    char line[80];
    char ah[1];
    
      //Test printString
    printString("Hello Joanna\0");

      //Test readChar
//    printString("Type a char: \0");
//    ch = readChar();
//    buf[2] = ch;
//    printString("Read: \0");
//    printString(buf);
//    printString("\n\r\0");
//
      //Test readString
//    printString("Enter a line: \0");
//    readString(buf);
//    printString("\n\0");
//    printString(buf);
    
    //Test readSector
//    char buffer[512];
//    readSector(buffer, 30);
//    printString(buffer);
    
    //Test makeInterrupt
//    makeInterrupt21();
//    interrupt(0x21,0x00,0,0,0);
    
    
    //Test makeInterrupt21
//    makeInterrupt21();	// setup ISR for interrupt 0x21
//    
//    interrupt(0x21, 0x00, "Type>\0", 0, 0);	// display prompt
//    interrupt(0x21, 0x11, buf, 0, 0);			  // read char
//    line[0] = buf[0];
//    line[1] = 0x00;
//    interrupt(0x21, 0x00, line, 0, 0);			// print string
    
    while(1>0){}

    
}

//printString method
int printString(char *str){
    int i = 0;
    int result;
    while(str[i] != '\0'){
        char al = str[i];
        char ah = 0x0E;
        int ax = ah * 256 + al;
        interrupt(0x10, ax, 0, 0, 0);
        i++;
    }
     result = i - 1;
    
    //Test for the return result
//    for(;result >= 0;result--){
//        char al = '*';
//        char ah = 0x0E;
//        int ax = ah * 256 + al;
//        interrupt(0x10, ax, 0, 0, 0);
//        
//    }
    return result;
    
}

//readChar method
int readChar(){

    return interrupt(0x16, 0x00, 0, 0, 0);
}

//readString method
//(The kernel improvement part is not working. But the orinignal code should be working)
int readString(char *buf){
    int i = 0;
    int result;
    while(i == 0 ||buf[i-1] != 0x0D){
        //if (buf[i-1] == 0x08) {
            //interrupt(0x10,0x08, 0, 0, 0);
            //printString(" ");

            //interrupt(0x10,'x', 0, 0, 0);
            //interrupt(0x10,0x08, 0, 0, 0);
            //buf[i] = ' ';
            //interrupt(0x10,'x', 0, 0, 0);
            //i--;
        //}
        //else {
        result =readChar()%256;
        buf[i] =result;
        interrupt(0x10,0x0E*256+result, 0, 0, 0);
        i++;
        //}
    }


    buf[i++] = 0;
    return i - 1;
}

//readSector
int readSector(char *buf, int absSector){
    int relSector = mod(absSector, 18)+ 1;
    int head = mod((absSector/18), 2);
    int track = absSector / 36;
    
    //Calculate for the values of ax,bx,cx,dx
    int ax = 0x02 * 256 + 0x01;
    int bx = buf;
    int cx = track * 256 + relSector;
    int dx = head * 256 + 0x00;
    interrupt(0x13, ax, bx, cx, dx);
    return 1;
}

//The mod function.Return the mod.
int mod(int divider, int dividend){
    int result = divider - (divider / dividend)* dividend;
    return result;
}



//The handelInterrupt21 function
int handleInterrupt21(int ax, int bx, int cx, int dx){
    if (ax == 0x00) {
         printString(bx);
        return 1;
    }
    else if(ax == 0x11){
        ((char*)bx)[0] = readChar();
        return 1;
    }
    else if(ax == 0x01){
        readString(bx);
        return 1;

    }
    else{
    return -1;
    }
}

//the putChar function
//Parameters: letter to be printed, row and col of the desired location, color of the letters
void putChar(char letter, int row, int col, int color){
    int letterAddress = (80*(row -1) + col)*2 + 0x8000; // calculate the address to store the character
    putInMemory(0xB000, letterAddress, letter); //calculate the address to store the color
    putInMemory(0xB000, letterAddress + 1, color);
}

//the putString function
//Parameters: string to be printed, row and col of the desired location(begining of the string), color of the string
void putString(char* letter, int row, int col, int color){
    int i = 0;
    int add = (80*(row -1) + col);
    while(letter[i] != '\0' ){
        putInMemory(0xB000, (add + i)*2 + 0x8000, letter[i]); //calculate the address to store the character
        putInMemory(0xB000, (add + i)*2 + 0x8000 + 1, color); //calculate the address to store the color
        i++;
    }
}
