#include "proc.h"

void initializeProcStructures(){
    int i = 0;
    int j = 0;
    for(i; i < 8; i++){
        memoryMap[i] = 0;
    }
    for(j; j < 8; j++){
        pcbPool[j].name[0] = 0x00;
        state = 0;
        segment = 0;
        stackPointers = 0x0000;
    }
    
    idleProc.name[0] = 'I';
    idleProc.name[1] = 'D';
    idleProc.name[2] = 'L';
    idleProc.name[3] = 'E';
    idleProc.state = 1;
    idleProc.segment = 0;
    stackPointers =0x0000;
    running = idleProc;
    readyHead = 0x00;
    readyTail = 0x00;
}

int getFreeMemorySegment(){
    int i = 0;
    for(i; i < 8; i++){
        if(memoryMap[i] == 0){
            return i;
        }
    }
    return -1;
}

void releaseMemorySegment(int seg){
    memoryMap[seg] = 0;
}

struct PCB *getFreePCB(){
    int i = 0;
    for(i;i < 8; i++){
        if(pcbPool[i].state == 0){
            pcbPool[i].state = 4;
            return *pcbPool[i];
        }
    }
    return 0x00;
    
}

void releasePCB(struct PCB *pcb){
    pcb.state = 0;
    pcb.next = 0x00;
    pcb.prev = 0x00;
    pcb.name[0] = 0x00;
    
}

void addToReady(struct PCB *pcb){
    readyTail.next = pcb;
    pcb = readyTail;
    
}

struct PCB *removeFromReady(){
    PCB temp = readyHead;
    readyHead = readyHead.next;
    return *temp;
}
