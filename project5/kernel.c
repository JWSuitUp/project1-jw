//kernel.c  project5
//author: Joanna Wang, Abby
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
int compare(char *name, char *name2);
int executeProgram(char* name);
int checkSegment(int segment);
void launchProgram(int segment);
void terminate();
void resetSegments();
int writeSector(char *buffer, int sector);
int deleteFile(char *fname);
int writeFile(char *fname, char *buffer, int sectors);
void handleTimerInterrupt(int segment, int stackPointer);
void returnFromTimer(int segment, int stackPointer);
void kStrCopy(char *src, char *dest, int len);
void yield();
void showProcesses();
int kill(int segment);

struct dirEntry {
    char name[6];
    char sectors[26];
};

struct directory {
    struct dirEntry entries[16];
};

//main method
int main(){
    enableInterrupts();

        //char buf[512];
    //    //writeSector("Abby", 2879);
    //    printString("go2");
    //    //deleteFile("messag");
    //    readfile("messag",buf);
    //    printString("read");
        //writeFile("exampl", buf, 1);
    //    printString("end");
    
    //printString("main");
    //Test executeProgram
    makeInterrupt21();
    interrupt(0x21, 0x04, "shell\0", 0x2000, 0);
    interrupt(0x21, 0x00, "Done!\n\r\0", 0, 0);
    makeTimerInterrupt();
    while(1);			/* infinite loop */
//    char buffer[10000];		/* the maximum size of a file*/
//    int i = 0;
//    makeInterrupt21();
//    for(; i < 1000; ++i)
//    {
//        buffer[i] = buffer[i]+'a';
//    }
//    printString("bleh");
//    printString(&buffer);
//    printString("TRYING");
//    
//    /*read the file into buffer*/
//    interrupt(0x21, 0x03, "messag\0", buffer, 0);
//    printString("Reading done");
//
//    
//    /*print out the file*/
//    interrupt(0x21, 0x00, buffer, 0, 0);
//    printString("done");
//
//    
//    while(1);			/* infinite loop */

}



//writeSector
int writeSector(char *buffer, int sector){
    int relSector = mod(sector, 18)+ 1;
    int head = mod((sector/18), 2);
    int track = sector / 36;
    
    //Calculate for the values of ax,bx,cx,dx
    int ax = 0x03 * 256 + 0x01;
    int bx = buffer;
    int cx = track * 256 + relSector;
    int dx = head * 256 + 0x00;
    
    interrupt(0x13, ax, bx, cx, dx);
    return 1;
}

//deleteFile method
int deleteFile(char *fname){
    char dirBuffer[512];
    char diskmap[512];
    struct directory *dir;
    int i = 0;
    int j = 0;
    dir = dirBuffer;
    readSector(dirBuffer,2);
    readSector(diskmap,1);
    for (i; i < 16; i++) {
        if(compare(fname,dir->entries[i].name) == 1){
            for( j = 0; j < 26 ; j++){
                if(dir->entries[i].sectors[j]!=0){
                    diskmap[ dir->entries[i].sectors[j] ] = 0;
                }
            }
            
            dir->entries[i].sectors[0] = 0x00;
            dir->entries[i].name[0] = 0x00;
            
            writeSector(diskmap,1);
            writeSector(dirBuffer,2);
            return 1;
        }
        
    }
    return -1;
}

//writeFile method
int writeFile(char *fname, char *buffer, int sectors){
    struct directory *dir;
    char diskmap[512];
    int i = 0;
    int j = 0;
    int k = 0;
    dir = buffer;
    readSector(buffer,2);
    readSector(diskmap,1);
    //printString("start to write");
    for(i; i < 16; i++){
        if(compare(fname,dir->entries[i].name) == 1){
            while(j != 26 ){
                if(j != sectors){
                    writeSector(&buffer[j*512], dir->entries[i].sectors[j]);
                }
                j++;
            }
            //printString("find it. writing");
            for( j = 0; j < 26 ; j++){
                if(dir->entries[i].sectors[j]!=0){
                    diskmap[ dir->entries[i].sectors[j] ] = 0xFF;
                }
            }
            if(j == 26){
                writeSector(diskmap,1);
                writeSector(buffer,2);
                return -2;
            }
            else{
                writeSector(diskmap,1);
                writeSector(buffer,2);
                return j+1;
            }
        }
    }
    
    for(i = 0; i < 16; i++){
        if(dir->entries[i].name[0] == 0){
            while(k != 26 ){
                if(k != sectors){
                    writeSector(&buffer[j*512], dir->entries[i].sectors[k]);
                }
                k++;
            }
            //printString("didn't find it. writing");
            for( j = 0; j < 26 ; j++){
                if(dir->entries[i].sectors[j]!=0){
                    diskmap[ dir->entries[i].sectors[j] ] = 0xFF;
                }
            }
            if(k ==  26){
                writeSector(diskmap,1);
                writeSector(buffer,2);
                return -2;
            }
            else{
                writeSector(diskmap,1);
                writeSector(buffer,2);
                return k+1;
            }
        }
        else{
            return -1;
        }
    }
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
//readfile method
int readfile(char *filename, char *buf){
    char dirBuffer[512];
    struct directory *dir;
    int i = 0;
    int j = 0;
    dir = dirBuffer;
    readSector(dirBuffer,2);
    
    for (i; i < 16; i++) {
        if(compare(filename,dir->entries[i].name) == 1){
            for(j; j < 26; j++){
                if(dir->entries[i].sectors[j] != 0){
                    readSector( buf + 512*j, dir->entries[i].sectors[j]);
                }
                else{
                    return j+1;
                }
            }
        }
    }
    return -1;
    
}

int compare(char *name, char *name2){
    int i = 0;
    for(i; i<= 5; i++){
        if(name[i] != name2[i]){
            //interrupt(0x21, 0x00, "not same", 0, 0);
            return -1;
            
        }
        
    }
    return 1;
    
}

int executeProgram(char* name){
    int i = 0;
    int offset = 0x0000;
    char buffer[512];
    int sectors;
    int segment;
    struct PCB *pcb;
    
    setKernelDataSegment();
    pcb = getFreePCB();
    restoreDataSegment();

    setKernelDataSegment();
    segment = getFreeMemorySegment()
    restoreDataSegment();

    if(segment == -1){
        return -2;
    }
    
    sectors = readfile(name, buffer);
    if(sectors == -1){
        return -1;
    }
    
    for (i; i < sectors*512 ; i++) {
        putInMemory(segment,offset,buffer[i]);
        offset++;
    }
//    pcb->name[0] = name[0];
//    pcb->name[1] = name[1];
//    pcb->name[2] = name[2];
//    pcb->name[3] = name[3];
//    pcb->name[4] = name[4];
//    pcb->name[5] = name[5];
    kStrCopy(name, pcb->name, 6);
    
    setKernelDataSegment();
    pcb->state = STARTING;
    pcb->segment = segment;
    pcb->stackPointer = 0xFF00;
    restoreDataSegment();

    initializeProgram(segment);
    return 1;
    
}

int checkSegment(int segment){
    if (segment == 0x2000 ||
        segment == 0x3000 ||
        segment == 0x4000 ||
        segment == 0x5000 ||
        segment == 0x6000 ||
        segment == 0x7000 ||
        segment == 0x8000 ||
        segment == 0x9000) {
        return 1;
    }
    else{
        return -1;
    }
}

void terminate(){
    struct PCB *pcb;
    
    setKernelDataSegment();
    pcb = running;
    restoreDataSegment();
    
    setKernelDataSegment();
    releaseMemorySegment(pcb->segment);
    releasePCB(pcb);
    restoreDataSegment();

//    resetSegments();
//    printString("I'm back!");
    interrupt(0x21, 0x04, "shell\0", 0x2000, 0);
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
        
        result =readChar()%256;
        buf[i] =result;
        interrupt(0x10,0x0E*256+result, 0, 0, 0);
        i++;
        
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
    else if(ax == 0x02){
        readSector(bx,cx);
    }
    else if(ax == 0x03){
        readfile(bx,cx);
    }
    else if(ax == 0x04){
        executeProgram(bx);
    }
    else if(ax == 0x05){
        terminate();
    }
    else if(ax == 0x07){
        deleteFile(bx);
    }
    else if(ax == 0x08){
        writeFile(bx,cx,dx);
    }
    else if(ax == 0x09){
        yield();
        return 1;
    }
    else if(ax == 0x0A){
        showProcesses();
        return 1;
    }
    else if(ax == 0x0B){
        kill(bx);
    }
    else{
        return -1;
    }
    
}

void handleTimerInterrupt(int segment, int stackPointer){
    struct PCB *pcb ;
    struct PCB *head;
    
    setKernelDataSegment();
    pcb = getFreePCB();
    
    if(pcb->state != DEFUNCT){
        
    }
    pcb->stackPointer = stackPointer;
    pcb->state = READY;
    addToReady(pcb);
    
    head = removeFromReady();
    restoreDataSegment();
    
    setKernelDataSegment();
    if(head == NULL){
        head = idleProc;
    }
    
    head->state = RUNNING;
    restoreDataSegment();

    setKernelDataSegment();
    running = head;
    restoreDataSegment();
    //printString("tic");
    returnFromTimer(head->segment, head->stackPointer);
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

void kStrCopy(char *src, char *dest, int len) {
    int i = 0;
    for (i = 0; i < len; i++) {
        putInMemory(0x1000, dest+i, src[i]);
        if (src[i] == 0x00) {
            return;
        }
    }
}

void yield(){
    setKernelDataSegment();
    running->state = READY;
    restoreDataSegment();
}

void showProcesses(){
    int i = 0;
    setKernelDataSegment();
    struct PCB *pcb;
    for(i; i < 8; i++){
        if(pcb->state == RUNNING){
            pcb->name = memoryMap[i]->name;
            pcb->segment = memoryMap[i]->segment;
            segment = (pcb->segment - 0x2000)/0x1000;
            printString(pcb->name);
            printString(", ");
            printString(segment);
            printString("\n");
        }
        
    }
    restoreDataSegment();
}

int kill(int segment){
    int i = 0;
    int index;
    setKernelDataSegment();
    struct PCB *pcb;
    index = (pcb->segment - 0x2000)/0x1000
    if(memoryMap[index]->state == RUNNING){
        terminate();
        return 1;
    }
    return -1;
        
}
