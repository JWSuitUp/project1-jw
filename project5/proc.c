#include "proc.h"

void initializeProcStructures(){
    int i = 0;
    int j = 0;
    for(; i < 8; i++){
        memoryMap[i] = 0;
    }
    for(; j < 8; j++){
        pcbPool[j].name[0] = 0x00;
        pcbPool[j].state = 0;
        pcbPool[j].segment = 0;
        pcbPool[j].stackPointer = 0x0000;
    }
    
    idleProc.name[0] = 'I';
    idleProc.name[1] = 'D';
    idleProc.name[2] = 'L';
    idleProc.name[3] = 'E';
    idleProc.state = 1;
    idleProc.segment = 0;
    idleProc.stackPointer =0x0000;
    running = &idleProc;
    readyHead = 0x00;
    readyTail = 0x00;
}

int getFreeMemorySegment(){
    int i = 0;
    for(; i < 8; i++){
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
    for(;i < 8; i++){
        if(pcbPool[i].state == DEFUNCT){
            pcbPool[i].state = STARTING;
            return &pcbPool[i];
        }
    }
    return 0x00;
    
}

void releasePCB(struct PCB *pcb){
    pcb->state = DEFUNCT;
    pcb->next = 0x00;
    pcb->prev = 0x00;
    pcb->name[0] = 0x00;
    
}

void addToReady(struct PCB *pcb){
    if(readyHead == NULL){
        readyHead = pcb;
        readyTail = pcb;
    }
    else{
        readyTail->next = pcb;
        pcb = readyTail;
    }
}

struct PCB *removeFromReady(){
    struct PCB * temp = readyHead;
    readyHead = readyHead->next;
    return temp;
}
