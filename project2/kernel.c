//kernel.c
//author: Joanna Wang
//Date: 2/9/2016
//signatures
void putChar(char letter, int row, int col, int color);
void putString(char* letter, int row, int col, int color);
int printString(char *str);
int readChar();
int readString(char *buf);
//main method
int main(){
    
    char * buf = "***********************************";
    char ch;
    int fullCh;
    char scanCode;
    char * line = "                        ";
    char a;
    
    //Test printString
    //printString("Hello Joanna\0");
    
    //Test readChar
    //printString("Type a char: \0");
    //ch = readChar();
    //buf[2] = ch;
    //printString("Read: \0");
    //printString(buf);
    //printString("\n\r\0");

    //Test readString
    printString("Enter a line: \0");
    readString(buf);
    printString("\n\0");
    printString(buf);
    

}

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
    
//    for(;result >= 0;result--){
//        char al = '*';
//        char ah = 0x0E;
//        int ax = ah * 256 + al;
//        interrupt(0x10, ax, 0, 0, 0);
//        
//    }
    return result;
    
}

int readChar(){
    return interrupt(0x16, 0x00, 0, 0, 0);
}

int readString(char *buf){
    int i = 0;
    int result;
    while(buf[i] != '\0'&& (i == 0 ||buf[i-1] != 0x0D)){
        result =readChar()%256;
        buf[i] =result;
        i++;
    }
    
    buf[i++] = 0;
    return i - 1;
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
