/*
 * stack.c
 *
 *  Created on: 09.05.2022
 */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "stack.h"

long count = 0;
IntStack *start = NULL;

// Stack Initialisieren
int stackInit(IntStack *self){

	if(start == NULL){
		if((self = malloc(sizeof(IntStack))) != NULL){
			self->top = NULL;
			start = self;
			return 0;
		}else{
			fprintf(stderr,"stackInit(IntStack *self): Fehler malloc(sizeof(IntStack)); errno: %d\n",errno);
			exit(-1);
		}
	}else{
		fprintf(stderr,"stackInit(IntStack *self): Stack kann nur einmal initialisiert werden\n");
		exit(-1);
	}
}

// Stack freigeben
void stackRelease(IntStack *self){

	while(count > 0){
		stackPop(self);
	}
	free(start);
	printf("stackRelease(IntStack *self): Stack freigegeben\n");
}

// push
void stackPush(IntStack *self, int i){

	StackStruct *new;
	if((new = malloc(sizeof(StackStruct))) != NULL){
		new->data = i;
		new->next = self->top;
		self->top = new;
		count++;
	}else{
		fprintf(stderr,"stackPush(IntStack *self, int i): Fehler malloc(sizeof(StackElem)); errno: %d\n",errno);
		fprintf(stderr,"letzte Wert auf dem Stack ist: %d\n",stackTop(self));
		exit(-1);
	}
}

// top
int stackTop(const IntStack *self){

	if(count < 1){
		fprintf(stderr,"stackTop(IntStack *self): Stack ist leer\n");
		exit(-1);
	}else{
		return self->top->data;
		}
}

// pop
int stackPop(IntStack *self){

	if(count > 0){
		StackStruct *temp = self->top;
		int data = self->top->data;
		self->top = self->top->next;
		free(temp);
		count--;
		return data;

	}else{
		fprintf(stderr,"stackPop(IntStack *self): Stack ist leer\n");
		exit(-1);
	}
}

// is empty
int stackIsEmpty(const IntStack *self){

	if(count < 1){
		return 1;
	}else{
		return 0;
	}
}

// Ausgeben
void stackPrint(const IntStack *self){

	if(count < 1){
		fprintf(stderr,"stackPrint() nicht möglich, Stack ist leer\n");
		exit(-1);
	}
	long i = count;
	StackStruct *temp = self->top;
	while(i > 0){
		printf("wert: %d	stnr: %d\n",temp->data,i--);
		temp = temp->next;
	}
}
