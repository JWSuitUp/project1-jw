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
int readfile(char *filename, char *buf);
int locateFile(char * filename);
int compareName(char * filename)

//main method
int main(){
    

    
    while(1>0){}

    
}

struct dirEntry {
    char name[6];
    byte sectors[26];
};

struct directory {
    struct dirEntry entries[16];
};

//readfile method
int readfile(char *filename, char *buf){
    char dir[512]
    readSector(dir,2);
    
    int entry = compareName(filename,dir)
    
    readSector（buf, dir.entries[entry].sectors[0])
    readSector（&buf[512], dir.entries[entry].sectors[1])
    if(compareName(filename) == 1){
        readSector(buf,2);
    }
    else{
        return -1;
    }
    
}

//compare name
int compareName(char * filename1){
    int i = 0;
    int j = 0;
    for(i; i <= 16; i++){
        int found = 1;
        for(j; j<= 5 && found; j++){
            if(filename1[j] != dir.entries[i].name[j]){
                found = 0;
            }
        }
        if found return i;
    }
    return -1;
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
