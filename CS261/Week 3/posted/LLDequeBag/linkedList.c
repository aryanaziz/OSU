#include "linkedList.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>


/* Double Link*/
struct DLink {
	TYPE value;
	struct DLink * next;
	struct DLink * prev;
};

/* Double Linked List with Head and Tail Sentinels  */

struct linkedList{
	int size;
	struct DLink *firstLink;
	struct DLink *lastLink;
};

/*
	initList
	param lst the linkedList
	pre: lst is not null
	post: lst size is 0
*/

void _initList (struct linkedList *lst) {
	assert(lst != 0); //Make sure it's not null

	//Setup the first and last link
	struct DLink *firstItem = malloc(sizeof(struct DLink));
    struct DLink *lastItem = malloc(sizeof(struct DLink));

	//Make them lead to eachother
	firstItem->next = lastItem;
	lastItem->prev = firstItem;

	//Assign them to lst
	lst->firstLink = firstItem;
	lst->lastLink = lastItem;
	lst->size = 2;
}

/*
 createList
 param: none
 pre: none
 post: firstLink and lastLink reference sentinels
 */

struct linkedList *createLinkedList()
{
	struct linkedList *newList = malloc(sizeof(struct linkedList));
	_initList(newList);
	return(newList);
}

/*
	_addLinkBeforeBefore
	param: lst the linkedList
	param: l the  link to add before
	param: v the value to add
	pre: lst is not null
	pre: l is not null
	post: lst is not empty
*/

/* Adds Before the provided link, l */

void _addLinkBefore(struct linkedList *lst, struct DLink *l, TYPE v)
{
	//Make sure both of the lists aren't null
	assert(lst != 0);
	//assert(!isEmptyList(l));

	//Create the new item
	struct DLink *newItem = malloc(sizeof(struct DLink));

	//Setup the new item
	newItem->value = v;
	newItem->next = l;
	newItem->prev = l->prev;

	//Lastly, place it into list before l
	l->prev->next = newItem; //Go to the item before l and make it's next this new link
	l->prev = newItem; //Go to l and make it's previous this item

	//Almost forgot, you have to increase the size of this fool
	lst->size = lst->size + 1;

}


/*
	addFrontList
	param: lst the linkedList
	param: e the element to be added
	pre: lst is not null
	post: lst is not empty, increased size by 1
*/

void addFrontList(struct linkedList *lst, TYPE e)
{
	//Make sure the list isn't null
	assert(lst != 0);

	//Already did all the work to add a link before, just add it before the first link
	_addLinkBefore(lst, lst->firstLink->next, e);
	
}

/*
	addBackList
	param: lst the linkedList
	param: e the element to be added
	pre: lst is not null
	post: lst is not empty, increased size by 1
*/

void addBackList(struct linkedList *lst, TYPE e) {
	//Make sure the list isn't null
	assert(lst != 0);

	//Already did all the work to add a link before, just add it before the last link
	_addLinkBefore(lst, lst->lastLink, e);
}

/*
	frontList
	param: lst the linkedList
	pre: lst is not null
	pre: lst is not empty
	post: none
*/

TYPE frontList (struct linkedList *lst) {
	//Make sure the list isn't null
	assert(lst != 0);

	//Just return the value for the first item. 
	return(lst->firstLink->next->value);
}

/*
	backList
	param: lst the linkedList
	pre: lst is not null
	pre: lst is not empty
	post: lst is not empty
*/

TYPE backList(struct linkedList *lst)
{
	//Make sure the list isn't null
	assert(lst != 0);

	//Just return the value for the last item. 
	return(lst->lastLink->prev->value);
}

/*
	_removeLink
	param: lst the linkedList
	param: l the linke to be removed
	pre: lst is not null
	pre: l is not null
	post: lst size is reduced by 1
*/

void _removeLink(struct linkedList *lst, struct DLink *l)
{
	//Make sure both of the lists aren't null
	assert(lst != 0);
	//assert(!isEmptyList(l));

	//Pull a Soviet Union and make it so that l never existed
	l->prev->next = l->next; //Go to the item before l and change it's next to be the item after l
	l->next->prev = l->prev; //go to the item after l and change it's next to be the item before l

	//Free the memory, don't want memory leaks.
	free(l);

	//Reduce the size of this fool
	lst->size = lst->size - 1;
	
}

/*
	removeFrontList
	param: lst the linkedList
	pre:lst is not null
	pre: lst is not empty
	post: size is reduced by 1
*/

void removeFrontList(struct linkedList *lst) {
   	//Make sure the list isn't null
	assert(lst != 0);

	//Already did all the work to remove a link, so just remove the first one
	_removeLink(lst, lst->firstLink->next);

}

/*
	removeBackList
	param: lst the linkedList
	pre: lst is not null
	pre:lst is not empty
	post: size reduced by 1
*/

void removeBackList(struct linkedList *lst)
{	
	//Make sure the list isn't null
	assert(lst != 0);

	//Already did all the work to remove a link, so just remove the last one
	_removeLink(lst, lst->lastLink->prev);
	
}

/*
	isEmptyList
	param: lst the linkedList
	pre: lst is not null
	post: none
*/

int isEmptyList(struct linkedList *lst) {
 	//Can't use my usual version to assert the list isn't null
 	assert(lst != NULL);

 	if(lst->size > 0) {
 		return 1;
 	}

 	else {
 		return 0;
 	}
}


/* Function to print list
 Pre: lst is not null
 */
void _printList(struct linkedList* lst)
{
	//Make sure the list isn't null
	assert(lst != 0);

	//Make a temporary link so that you can check against it. Set it equal to the first link and make your while loop stop if it gets to the last link. 
	struct DLink *tempItem = lst->firstLink;

	while(tempItem != lst->lastLink) {
		printf("%d\n", tempItem->value); //Print it out
		tempItem = tempItem->next; //Set it equal to the next thing in the chain
	}

}

/* 
	Add an item to the bag
	param: 	lst		pointer to the bag
	param: 	v		value to be added
	pre:	lst is not null
	post:	a link storing val is added to the bag
 */
void addList(struct linkedList *lst, TYPE v)
{
	//Make sure the list isn't null
	assert(lst != 0);

	_addLinkBefore(lst, lst->firstLink->next, v);

}

/*	Returns boolean (encoded as an int) demonstrating whether or not
	the specified value is in the collection
	true = 1
	false = 0

	param:	lst		pointer to the bag
	param:	e		the value to look for in the bag
	pre:	lst is not null
	pre:	lst is not empty
	post:	no changes to the bag
*/
int containsList (struct linkedList *lst, TYPE e) {
	//Make sure the list isn't null
	assert(lst != 0);

	//Make a temporary link so that you can check against it. Set it equal to the first link and make your while loop stop if it gets to the last link. 
	struct DLink *tempItem = lst->firstLink;

	while(tempItem != lst->lastLink) {
		if(tempItem->value == e) {
			return 1;
		}
		tempItem = tempItem->next; //Set it equal to the next thing in the chain
	}

	return 0;	
}

/*	Removes the first occurrence of the specified value from the collection
	if it occurs

	param:	lst		pointer to the bag
	param:	e		the value to be removed from the bag
	pre:	lst is not null
	pre:	lst is not empty
	post:	e has been removed
	post:	size of the bag is reduced by 1
*/
void removeList (struct linkedList *lst, TYPE e) {
	//Make sure the list isn't null
	assert(lst != 0);

	//Already did the work to find an item and to remove an item, just copy the code from contains and instead of returning something, have it remove it. 
	struct DLink *tempItem = lst->firstLink;

	while(tempItem != lst->lastLink) {
		if(tempItem->value == e) {
			_removeLink(lst, tempItem);
		}
		tempItem = tempItem->next; //Set it equal to the next thing in the chain
	}
}