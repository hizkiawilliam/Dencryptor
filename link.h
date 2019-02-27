/* Fig. 12.13: fig12_13.c
Operating and maintaining a queue */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> 
#include "encrypt.h"

/* self-referential structure */
struct Node {
	char data[50]; /* define data as a char */
	char pass[50];
	struct Node *nextPtr; /* Node pointer */
}; /* end structure Node */

typedef struct Node Node;
typedef Node *NodePtr;

/* function prototypes */
bool search(struct Node* topPtr, char data[50], char pass[50]);
bool searchUser(struct Node* topPtr, char data[50]);
void push( NodePtr *topPtr, char info[50], char pass[50] );
void pop( NodePtr *topPtr );
int isEmpty( NodePtr topPtr );
void printStack( NodePtr currentPtr );
void instructions( void );
	
/* display program instructions to user */
void instructions( void )
{
	printf("\t\t\t\t==============================\n");
    printf("\t\t\t\t| 1. Add User                |\n");
    printf("\t\t\t\t| 2. Delete User             |\n");
    printf("\t\t\t\t| 3. Search User             |\n");
    printf("\t\t\t\t| 4. Print Users             |\n");
    printf("\t\t\t\t| 5. Go to Dencryptor Menu   |\n");
    printf("\t\t\t\t| 6. Admin logout            |\n");
    printf("\t\t\t\t| 7. Exit Program            |\n");
    printf("\t\t\t\t==============================\n");
    printf("\t\t\t\tSelect Your Choice : ");
} /* end function instructions */


/* insert a node a queue tail */
void push( NodePtr *topPtr, char info[50], char pass[50] )
{
	NodePtr newPtr; /* pointer to new node */
	newPtr = malloc( sizeof( Node ) );
	/* insert the node at stack top */
	if ( newPtr != NULL ) 
	{ /* is space available */
		strcpy(newPtr->data,info);
		strcpy(newPtr->pass,pass);
		newPtr->nextPtr = *topPtr;
		*topPtr = newPtr;
	} /* end if */
	else 
	{
		printf( "%s not inserted. No memory available.\n", info );
	} /* end else */
} /* end function push */

/* remove node from queue head */
void pop( NodePtr *topPtr )
{
	NodePtr tempPtr; /* temporary node pointer */
	char popValue[50]; /*node value*/
	
	tempPtr = *topPtr;
	strcpy(popValue,( *topPtr )->data);
	*topPtr = ( *topPtr )->nextPtr;
	free( tempPtr );
	
	printf( "\n\t\t\t\tThe user poped is %s.\n", popValue );
} /* end function pop */

/* Return 1 if the list is empty, 0 otherwise */
int isEmpty( NodePtr topPtr )
{
	return topPtr == NULL;
} /* end function isEmpty */

/* Checks whether the value x is present in linked list */
bool search(struct Node* topPtr, char data[50], char pass[50])
{ 
    struct Node* current = topPtr;  // Initialize current 
    while (current != NULL) 
    { 
        if ((strcmp(current->data,data)==0)&&(strcmp(current->pass,pass)==0))
            return true; 
        current = current->nextPtr; 
    } 
    return false; 
} 

bool searchUser(struct Node* topPtr, char data[50])
{ 
    struct Node* current = topPtr;  // Initialize current 
    while (current != NULL) 
    { 
        if ((strcmp(current->data,data)==0))
            return true; 
        current = current->nextPtr; 
    } 
    return false; 
}

/* Print the queue */
void printStack( NodePtr currentPtr )
{
	/* if queue is empty */
	if ( currentPtr == NULL ) 
	{
		printf( "\n\t\t\t\tUser is empty.\n" );
	} /* end if */
	else 
	{
		printf( "\n\t\t\t\tUser, Pass\n" );
		/* while not end of queue */
		while ( currentPtr != NULL ) 
		{
			printf( "\t\t\t\t- %s, %s\n",currentPtr->data,currentPtr->pass);
			currentPtr = currentPtr->nextPtr;
		} /* end while */
		//printf( "NULL\n\n" );
	} /* end else */
} /* end function printStack */

void printStackFile( NodePtr currentPtr )
{
	FILE *fp;												//deklarasi sebuah pointer dari tipe file	
	fp=fopen("account.txt","w");
	fclose(fp);
	fp=fopen("account.txt","w");
	while ( currentPtr != NULL ) 
	{
		fprintf( fp,"%s %s\n",encrypt(currentPtr->data,2),currentPtr->pass); //cetak ke file setelah diencrypt
		currentPtr = currentPtr->nextPtr;
	} /* end while */
	fclose(fp);
} /* end function printStack */

static void reverse(struct Node** head_ref) 
{ 
    struct Node* prev   = NULL; 
    struct Node* current = *head_ref; 
    struct Node* next = NULL; 
    while (current != NULL) 
    { 
        // Store next 
        next  = current->nextPtr;   
        // Reverse current node's pointer 
        current->nextPtr = prev;    
        // Move pointers one position ahead. 
        prev = current; 
        current = next; 
    } 
    *head_ref = prev; 
} 
