//kernel.c
//author: Joanna Wang
//Date: 2/9/2016
//signatures
void putChar(char letter, int row, int col, int color);
void putString(char* letter, int row, int col, int color);
int printString(char *str);
int readChar();
int readSector(char *buf, int absSector);
int mod(int num);
int handleInterrupt21(int ax, int bx, int cx, int dx);
//main method
int main(){
    
    //printString("Hello Joanna \0");
    
//    char *buf = “*****\0”;
//    char ch;
//    int fullCh;
//    byte scanCode;

//    printString("Type a char: \0");
//    ch = readChar();
//    buf[2] = ch;
//    printString("Read: \0");
//    printString(buf);
//    printString("\n\r\0");
    
//    char buffer[512];
//    readSector(buffer, 30);
//    printString(buffer);
    
    makeInterrupt21();
    interrupt(0x21, 0x00, 0, 0, 0);

    
    
}

int printString(char *str){
    int i = 0;
    while(str[i] != '\0'){
        char al = str[i];
        char ah = 0x0E;
        int ax = ah * 256 + al;
        interrupt(0x10, ax, 0, 0, 0);
        i++;
    }
    //return i;
}

//int readChar(){
//    
//    interrupt(0x16, 0x00, 0, 0, 0);
//    
//}

int readSector(char *buf, int absSector){
    relSector = mod(absSector, 18)+ 1;
    head = mod((absSector/18), 2);
    track = absSector / 36;
    
}

int mod(int divider, dividend){
    int result = divider - (divider / dividend);
    return result;
}

int handleInterrupt21(int ax, int bx, int cx, int dx){
    printString("Quit Interrupting!\0");
    return 0;
}


//the putChat function
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



