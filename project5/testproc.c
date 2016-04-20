/*
 *  testproc.c
 *  
 *
 *  Created by Grant Braught on 4/1/10.
 *  Copyright 2010 Dickinson College. All rights reserved.
 *
 */

#define MAIN

#include "stdio.h"
#include "assert.h"
#include <string.h>
#include "proc.h"

void testInit() {	
	initializeProcStructures();
	
	assert(running == &idleProc);
	assert(readyHead == NULL);
	assert(readyTail == NULL);
	int i=0;
	for (i=0; i<8; i++) {
		assert(memoryMap[i] == FREE);
		assert(pcbPool[i].name[0] == 0x00);
		assert(pcbPool[i].state == DEFUNCT);
		assert(pcbPool[i].segment == 0x00);
		assert(pcbPool[i].stackPointer == 0x00);
	}
   
	assert(strcmp(idleProc.name, "IDLE\0") == 0);
	assert(idleProc.segment == 0x0000);
	assert(idleProc.stackPointer == 0x0000); 
}

void testgetFreeMemorySegment(){
    int test = getFreeMemorySegment();
    assert(test == -1 || (test >= 0 && test <8));
    //assert(test == 560);
}

void testreleaseMemorySegment(){
    memoryMap[3] = 2;
    releaseMemorySegment(3);
    assert(memoryMap[3] == 0);
}

void testgetFreePCB(){
    struct PCB *test = getFreePCB();
    assert(test->state == STARTING || test == 0x00);
}

void testreleasePCB(){
    struct PCB *test = getFreePCB();
    releasePCB(test);
    assert(test->state == DEFUNCT);
    assert(test->next == 0x00);
    assert(test->prev == 0x00);
    assert(test->name[0] == 0x00);
}

void testaddToReady() {
    struct PCB *test = getFreePCB();
    addToReady(test);
    assert(readyTail == test);
    assert(readyTail->next == NULL);

}

void testremoveFromReady() {
    struct PCB *head = readyHead;
    struct PCB *test = removeFromReady();
    assert(test == head );
}

int main() {
	printf("Testing initializeProcStructures\n");
	testInit();
	printf("done testing init\n");
    
    printf("Testing testgetFreeMemorySegment\n");
    testgetFreeMemorySegment();
    //printf("%i", testgetFreeMemorySegment());
    printf("done testing getFreeMemorySegment\n");
    
    printf("Testing testreleaseMemorySegment\n");
    testreleaseMemorySegment();
    printf("done test release\n");

    printf("Testing getFreePCB\n");
    testgetFreePCB();
    printf("done testing getFreePCB\n");
    
    printf("Testing releasePCB\n");
    testreleasePCB();
    printf("done testing releasePCB\n");

    printf("Testing addToReady\n");
    testaddToReady();
    printf("done testing add\n");

    printf("Testing removeFromReady\n");
    testremoveFromReady();
    printf("done testing remove\n");

}