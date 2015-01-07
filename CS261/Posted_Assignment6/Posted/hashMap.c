#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "hashMap.h"



/*the first hashing function you can use*/
int stringHash1(char * str)
{
    int i;
    int r = 0;
    for (i = 0; str[i] != '\0'; i++)
        r += str[i];
    return r;
}

/*the second hashing function you can use*/
int stringHash2(char * str)
{
    int i;
    int r = 0;
    for (i = 0; str[i] != '\0'; i++)
        r += (i+1) * str[i]; /*the difference between stringHash1 and stringHash2 is on this line*/
    return r;
}

/* initialize the supplied hashMap struct*/
void _initMap (struct hashMap * ht, int tableSize)
{
    int index;
    if(ht == NULL)
        return;
    ht->table = (hashLink**)malloc(sizeof(hashLink*) * tableSize);
    ht->tableSize = tableSize;
    ht->count = 0;
    for(index = 0; index < tableSize; index++)
        ht->table[index] = NULL;
}

/* allocate memory and initialize a hash map*/
hashMap *createMap(int tableSize) {
    assert(tableSize > 0);
    hashMap *ht;
    ht = malloc(sizeof(hashMap));
    assert(ht != 0);
    _initMap(ht, tableSize);
    return ht;
}

/*
 Free all memory used by the buckets.
 Note: Before freeing up a hashLink, free the memory occupied by key and value
 */
void _freeMap (struct hashMap * ht)
{  
    /*write this*/  
    struct hashLink* currentLink = malloc(sizeof(struct hashLink)); //Save a spot for the current link
    struct hashLink* nextLink = malloc(sizeof(struct hashLink)); //Save a spot for the next link

    for(int i = 0; i < ht->tableSize; i++) {
        currentLink = ht->table[i]; //Set the current link
        while(currentLink != NULL) { //If your current link is valid
            nextLink = currentLink->next; //Assign the nextLink since we are going to free the current one
            free(currentLink); //Free that sucka
            currentLink = nextLink; //As TI says, "On to the next one"
        }
    }

    //Now that we are done freeing the individual links, we need to clear the whole thing
    free(ht->table); //Free the table
    ht->tableSize = 0; //Reset the tableSize (forgot to do this the first time around, Whoops)
    ht->count = 0; //Reset the number of links (also forgot this one, caused many problems) 
}

/* Deallocate buckets and the hash map.*/
void deleteMap(hashMap *ht) {
    assert(ht!= 0);
    /* Free all memory used by the buckets */
    _freeMap(ht);
    /* free the hashMap struct */
    free(ht);
}

/* 
Resizes the hash table to be the size newTableSize 
*/
void _setTableSize(struct hashMap * ht, int newTableSize)
{
    /*write this*/
    hashLink** currentMap = ht->table; //Grab the current table
    int curTableSize = ht->tableSize; //Grab the current table size
    ht->table = (hashLink**)malloc(newTableSize * sizeof(hashLink*)); //
    ht->tableSize = newTableSize; //Set the tableSize to the new one THIS MOTHERFUCKER CAUSED ME 3 HOURS OF DEBUGGING... (I had it after the for loop below)

    for(int i = 0; i < curTableSize; i++) {//For loop to add all the values into the new table
        while(currentMap[i] != NULL) { //While there is a value at the old map's position
            hashLink* nextLink; //Set a placeholder for the next item so that we can move onto it after 
            nextLink = currentMap[i]->next; //Set the next value
            insertMap(ht, currentMap[i]->key, currentMap[i]->value); //The work is already being done for this, re-use that function. 
            currentMap[i] = nextLink;
        }
    }
}

/*
 insert the following values into a hashLink, you must create this hashLink but
 only after you confirm that this key does not already exist in the table. For example, you
 cannot have two hashLinks for the word "taco".
 
 if a hashLink already exists in the table for the key provided you should
 replace that hashLink--this requires freeing up the old memory pointed by hashLink->value
 and then pointing hashLink->value to value v.
 
 also, you must monitor the load factor and resize when the load factor is greater than
 or equal LOAD_FACTOR_THRESHOLD (defined in hashMap.h).
 */
void insertMap (struct hashMap * ht, KeyType k, ValueType v)
{  
    /*write this*/
    int index;

    //Find the index to insert the values at
    if(HASHING_FUNCTION == 1) {
        index = stringHash1(k);
    }
    else if(HASHING_FUNCTION == 2) {
        index = stringHash2(k);
    }
    index = index % ht->tableSize; //Reduce the index to a valid spot
    if(index < 0) { //Make sure it's positive
        index = index + ht->tableSize;
    }

    //Let's see if it exists and change the value if it does
    if(containsKey(ht, k)) {
        ht->table[index]->value = v; //Replace the value of it. It says we should delete it, but ehh
    }
    else { //If it doesn't already exist, let's add it in
        struct hashLink* newLink = malloc(sizeof(struct hashLink)); //Create a new link and save space
        newLink->key = k; //Assign the Key
        newLink->value = v; //Assign the value
        newLink->next = ht->table[index]; //Assign the next
        ht->table[index] = newLink; //You gotta add the actual link to the table...
        ht->count = ht->count + 1;
    }

    if(tableLoad(ht) >= LOAD_FACTOR_THRESHOLD) { //Check to see if the load factor is over
        _setTableSize(ht, ht->tableSize * 2); //Double the size
    }
}

/*
 this returns the value (which is void*) stored in a hashLink specified by the key k.
 
 if the user supplies the key "taco" you should find taco in the hashTable, then
 return the value member of the hashLink that represents taco.
 
 if the supplied key is not in the hashtable return NULL.
 */
ValueType* atMap (struct hashMap * ht, KeyType k)
{ 
    /*write this*/
    int index;

    //Find the index to insert the values at (copied from above)
    if(HASHING_FUNCTION == 1) {
        index = stringHash1(k);
    }
    else if(HASHING_FUNCTION == 2) {
        index = stringHash2(k);
    }
    index = index % ht->tableSize; //Reduce the index to a valid spot
    if(index < 0) { //Make sure it's positive
        index = index + ht->tableSize;
    }

    struct hashLink* currentLink = ht->table[index]; //Create a temporary item to search through
    while(currentLink != NULL) { //Gonna look through each one 
        if(strcmp(currentLink->key, k) == 0) { //If we have a value there
            return &(currentLink->value); //Parenthesis around it because we want the value of the whole thing, not just currentLink
        }
        currentLink = currentLink->next;
    }

    return NULL; //If there is no value, return nothing.
}

/*
 a simple yes/no if the key is in the hashtable. 
 0 is no, all other values are yes.
 */
int containsKey (struct hashMap * ht, KeyType k)
{  
    /*write this*/
    int index;

    //Find the index to insert the values at (copied from above)
    if(HASHING_FUNCTION == 1) {
        index = stringHash1(k);
    }
    else if(HASHING_FUNCTION == 2) {
        index = stringHash2(k);
    }
    index = index % ht->tableSize; //Reduce the index to a valid spot
    if(index < 0) { //Make sure it's positive
        index = index + ht->tableSize;
    }

    //same code as above just return 1 instead of the value
    struct hashLink* currentLink = ht->table[index];
    while(currentLink != NULL) { //Gonna look through each one 
        if(strcmp(currentLink->key, k) == 0) {
            return 1;
        }
        currentLink = currentLink->next;
    }

    return 0; //If there is no value, return nothing.
}

/*
 find the hashlink for the supplied key and remove it, also freeing the memory
 for that hashlink. it is not an error to be unable to find the hashlink, if it
 cannot be found do nothing (or print a message) but do not use an assert which
 will end your program.
 */
void removeKey (struct hashMap * ht, KeyType k)
{  
    /*write this*/
    int index;

    //Find the index to insert the values at (copied from above)
    if(HASHING_FUNCTION == 1) {
        index = stringHash1(k);
    }
    else if(HASHING_FUNCTION == 2) {
        index = stringHash2(k);
    }
    index %= ht->tableSize; //Reduce the index to a valid spot
    if(index < 0) { //Make sure it's positive
        index += ht->tableSize;
    }

    struct hashLink* currentLink = ht->table[index];
    struct hashLink* previousLink = malloc(sizeof(struct hashLink));

    if(currentLink == NULL) { //Didn't find him
        return;
    }

    while(strcmp(currentLink->key, k) != 0) { //Found it
        previousLink = currentLink; 
        currentLink = currentLink->next;
    }
    if(previousLink != NULL) {
        previousLink->next = currentLink->next;
    }   

    else {
        ht->table[index] = 0;
    }
}

/*
 returns the number of hashLinks in the table
 */
int size (struct hashMap *ht)
{  
    /*write this*/
    return ht->count; //Finally a simple one!
    
}

/*
 returns the number of buckets in the table
 */
int capacity(struct hashMap *ht)
{  
    /*write this*/
    return ht->tableSize; //Another one!
}

/*
 returns the number of empty buckets in the table, these are buckets which have
 no hashlinks hanging off of them.
 */
int emptyBuckets(struct hashMap *ht)
{  
    /*write this*/
    int numBuckets = 0; //Start with a count of 0

    for(int i = 0; i < ht->tableSize; i++) { //Go through the table
        if(ht->table[i] == NULL) { //Find the ones that are null
            numBuckets = numBuckets + 1; //Add to the list
        }
    }
    return numBuckets;
}

/*
 returns the ratio of: (number of hashlinks) / (number of buckets)
 
 this value can range anywhere from zero (an empty table) to more then 1, which
 would mean that there are more hashlinks then buckets (but remember hashlinks
 are like linked list nodes so they can hang from each other)
 */
float tableLoad(struct hashMap *ht)
{  
    /*write this*/
    return (float) ht->count / ht->tableSize; //Gotta make at least 1 of these a float

}
void printMap (struct hashMap * ht)
{
    int i;
    struct hashLink *temp;  
    for(i = 0;i < capacity(ht); i++){
        temp = ht->table[i];
        if(temp != 0) {     
            printf("\nBucket Index %d -> ", i);     
        }
        while(temp != 0){           
            printf("Key:%s|", temp->key);
            printValue(temp->value);
            printf(" -> ");
            temp=temp->next;            
        }       
    }
}


