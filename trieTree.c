#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "trieTree.h"

bool goBackwards = false;
int firstLetter = 0;
int addToCounter = 1;
int longestWord = 0;
node* head;


node* getNewNode(){
    node* newNode = (node*) malloc(sizeof(node));
    newNode->counter=0;
    newNode->isLeaf=true;
    for (size_t i = 0; i < CHAR_SIZE; i++) {newNode->characterArray[i] = NULL;}
    return newNode;
}

node* insertNewLetter(node* startNode, char character){ //NOTE - unlike insertNewWord method, this method returns the node pointer of the node it got to.
        if(character<65 || character>122 || (character>90 && character<97)){ //non Alphabet character. Should be skipped.
            
            return NULL;
        }

        if(character>=65 && character<=90){character = character + 32;} //change upper case letter to lower case

        if(startNode->characterArray[character-'a']==NULL){startNode->characterArray[character - 'a'] = getNewNode();} //if the next node doesn't exist, create it
        startNode->isLeaf=false;
        return startNode->characterArray[character - 'a'];
        
}

void killTree(node* killMe){

    if(!(killMe->isLeaf)){
        for (size_t i = 0; i < CHAR_SIZE; i++){
            if(killMe->characterArray[i]) {killTree(killMe->characterArray[i]);}
        }
    }
    free(killMe);
    
}

void printYourself(node* nodeToPrint, char* stringToPrint){
    if(nodeToPrint){


        int amount = nodeToPrint->counter;

        //order of printing should change if code was asked to print in regular or reverse order.
        //only one case will be used per run of the code (because goBackwards is boolean)
        if(goBackwards && !(nodeToPrint->isLeaf)){ 
            printYourChildren(nodeToPrint, stringToPrint);
        }

        if(amount>0){

            printf("%s\t%d\n", stringToPrint, amount);
        }

        if(!goBackwards && !(nodeToPrint->isLeaf)){
            printYourChildren(nodeToPrint, stringToPrint);
        }

    }
}//end printYourself

void printYourChildren(node* nodeToIterateOver, char* stringUntillNow){
    for (size_t i = firstLetter; i!=CHAR_SIZE && i!=-1; i = i+addToCounter)
        {

            char nextWord[longestWord];
            zeroOut(nextWord, longestWord); //initialize the array

            if(strlen(stringUntillNow)){strcpy(nextWord, stringUntillNow);} //only copy the string uptill now if it isn't empty

            char nextLetter = i+97; //+97 to ASCII table (0+97-->97-->a)

            nextWord[strlen(stringUntillNow)] = nextLetter; //add the next letter
            if(nodeToIterateOver->characterArray[i]){printYourself(nodeToIterateOver->characterArray[i], nextWord);}
            
        }
        
    
}

void zeroOut(char* zeroMe, int length){
    for (size_t i = 0; i < length; i++)
    {
        zeroMe[i]='\0';
    }
    
}

void initNode(node* nodeToInit){
    nodeToInit->counter=0;
    nodeToInit->isLeaf=false;
    for (size_t i = 0; i < CHAR_SIZE; i++) {nodeToInit->characterArray[i] = NULL;}
}

int main(int argc, char const *argv[]){

    head = (node*) malloc(sizeof(node)); //create head node of the Trie tree
    initNode(head);
    head->counter=-1; //this is to make the head node unique - it will be the only one to have -1 as value. This is used to distinguish it when later checking if slaveNode is currently on the head node or not.
    node* slaveNode = head;
    
    int currentWordLength = 0;
    int currentCharInt = 35; //arbitrary value
    char currentChar = currentCharInt;
    while(currentCharInt!=EOF){
        currentCharInt = fgetc(stdin);
        if (currentCharInt==32 || currentCharInt==-1 || currentCharInt==10){// current char is space. Next word! OR current char is EOF. OR current char is newLine

            if((slaveNode->counter)!=-1){//only if the slaveNode isn't pointing at the head node, increase the counter (end of word) and set slaveNode back to head.
                slaveNode->counter++;
                slaveNode = head;
            }
            if (currentWordLength>longestWord){longestWord = currentWordLength;} //if needed, update longest word found.
            currentWordLength = 0; //reset currentWordLength 
        }
        else{//not space, advance along the tree.
            currentChar = currentCharInt;
            node* nextNode = insertNewLetter(slaveNode, currentChar);
            if(nextNode){//this is to protect the case of NULL returns from function.
                slaveNode=nextNode;
                currentWordLength++;
            }
            
        }
    }//end while (inserting all the input to the Trie)




    if(argc>1){ //only if this condition is TRUE it is possible to get the r command
        if(strlen(argv[1])==1){
            if(strcmp(argv[1], "r")==0){
                firstLetter = CHAR_SIZE-1; 
                goBackwards = true; 
                addToCounter = -1; //values that change the order of printing the words of the tree
            }
        }

    }
    
    
    longestWord = longestWord +1; // to account for \0 
    char* giveToPrintAsPointer = (char*) malloc(sizeof(char)*longestWord);
    zeroOut(giveToPrintAsPointer,longestWord);
    printYourself(head, giveToPrintAsPointer);

    if(giveToPrintAsPointer) {free(giveToPrintAsPointer);}
    node* headCopy = head;
    if(headCopy){killTree(headCopy);}
    


    
    return 0;
}
