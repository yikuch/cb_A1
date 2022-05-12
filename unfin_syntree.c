/*
 * syntree.c
 *
 *  Created on: 11.05.2022
 */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "syntree.h"


long int num_nodes = 0;
Node *root = NULL;


int syntreeInit(Syntree *self){

	if(root == NULL){
		if((self = malloc(sizeof(Syntree))) != NULL){
			self->root = NULL;
			root = self;
			return 0;
		}else{
			fprintf(stderr,"syntreeInit(Syntree *self): Fehler malloc(sizeof(Syntree)); errno: %d\n",errno);
			exit(-1);
		}
	}else{
		fprintf(stderr,"syntreeInit(Syntree *self): Syntree kann nur einmal initialisiert werden\n");
		exit(-1);
	}
}

void syntreeRelease(Syntree *self){
    nodeRelease(self -> root);
	free(self);
	printf("syntreeRelease(Syntree *self): Syntree freigegeben\n");
}

void nodeRelease(Node *node) //rekursiv von unten nach oben alles free()
{
	while(node -> unrelated !=NULL) // beginnt mit dem letzen baum
	{
		node=node->unrelated;
	}
while(node -> next != NULL) //setzt node auf den letzen Knoten der Geschwister
{
	node=node -> next;
}
if(node -> child != NULL){ //hat also kinder
nodeRelease(node ->child); //rekursiv für Kind 
}
//hat also kein weiteren rechten geschwister und keine Kinder
free(node);
num_nodes--;
}

syntreeNodeNumber(Syntree *self, int number) //fügt zu der "unrelated" list einen zu dem punkt im baum uinverbundenen Knoten hinzu
{
 	Node *new;
	 if((new = malloc(sizeof(Node))) != NULL){
		new->data = number;
		new->next = NULL;
		new->child=NULL; 
		new->unrelated=NULL;
        num_nodes++;
		new->id=num_nodes;
		Node *temp=self-> root;
		while(temp-> unrelated != NULL)
		{
          temp=temp->unrelated;
		}
		temp->unrelated=new;
	}else{
		fprintf(stderr,"syntreeNodeNumber(Syntree *self, int number): Fehler malloc(sizeof(Node)); errno: %d\n",errno);
		exit(-1);
	}
	return new->id;
}
