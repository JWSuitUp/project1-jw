void putChar(char letter, int row, int col, int color);
void putString(char* letter, int row, int col, int color);
int main(){
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
putString("Hello World",20,20,0xF4);
}

void putChar(char letter, int row, int col, int color){
    putInMemory(0xB000, (80*(row -1) + col)*2 + 0x8000, letter);
    putInMemory(0xB000, (80*(row -1) + col)*2 + 0x8000 + 1, color);
}

void putString(char* letter, int row, int col, int color){
    int i = 0;
    while(letter[i] != '\0' ){
    putInMemory(0xB000, (80*(row -1) + col + i)*2 + 0x8000, letter[i]);
    putInMemory(0xB000, (80*(row -1) + col + i)*2 + 0x8000 + 1, color);
    i++;
    }
}

