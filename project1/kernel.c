//kernel.c
//author: Joanna Wang
//Date: 2/9/2016
//signatures
void putChar(char letter, int row, int col, int color);
void putString(char* letter, int row, int col, int color);
//main method
int main(){
//Print "Hello World" on the top left conor with white lines on a black background
putInMemory(0xB000, 0x8140, 'H');
putInMemory(0xB000, 0x8142, 'e');
putInMemory(0xB000, 0x8144, 'l');
putInMemory(0xB000, 0x8146, 'l');
putInMemory(0xB000, 0x8148, 'o');
putInMemory(0xB000, 0x814A, ' ');
putInMemory(0xB000, 0x814C, 'W');
putInMemory(0xB000, 0x814E, 'o');
putInMemory(0xB000, 0x8150, 'r');
putInMemory(0xB000, 0x8152, 'l');
putInMemory(0xB000, 0x8154, 'd');
    
//Print "Hello World" using the putChar function with white letters on a red background
putChar('H',13,20,0x4F);
putChar('e',13,21,0x4F);
putChar('l',13,22,0x4F);
putChar('l',13,23,0x4F);
putChar('o',13,24,0x4F);
putChar('W',13,26,0x4F);
putChar('o',13,27,0x4F);
putChar('r',13,28,0x4F);
putChar('l',13,29,0x4F);
putChar('d',13,30,0x4F);
    
//Print "Hello World" using the putString function with red letters on a white background
putString("Hello World",20,20,0xF4);
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
    int add = (80*(row -1) + col)
    while(letter[i] != '\0' ){
    putInMemory(0xB000, (add + i)*2 + 0x8000, letter[i]); //calculate the address to store the character
    putInMemory(0xB000, (add + i)*2 + 0x8000 + 1, color); //calculate the address to store the color
    i++;
    }
}

