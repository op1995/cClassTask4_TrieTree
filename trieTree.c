#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "trieTree.h"

bool goBackwards = false;
int firstLetter = 0;
int addToCounter = 1;
int longestWord = 0;

node* getNewNode(){
    node* newNode = (node*) malloc(sizeof(node));
    newNode->counter=0;
    newNode->isLeaf=true;
    for (size_t i = 0; i < CHAR_SIZE; i++) {newNode->characterArray[i] = NULL;}
    return newNode;
}

void insertNewWord(node* head, char* str){
    node* current = head;

    do
    {
        if(*str<65 || *str>122 || (*str>90 && *str<97)){ //non Alphabet character. Should be skipped.
            str++;
            continue;
        }

        if(*str>=65 && *str<=90){*str = *str + 32;} //change upper case letter to lower case

        if(current->characterArray[*str-'a']==NULL){current->characterArray[*str - 'a'] = getNewNode();} //if the next node doesn't exist, create it
        current->isLeaf=false;
        current = current->characterArray[*str - 'a']; //go to the next node!
        str++; //also, advance to the next letter of the given string

    }while(*str);
    // now that you are done moving along the tree, creating the needed nodes - you are done reading the string!
    //so you should increase the counter at the last node you've reached

    current->counter++;
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

        //order of perations should change if code was asked to print in regular or reverse order.
        //only one case will be used per run of the code (because goBackwards is boolean)
        if(goBackwards && !(nodeToPrint->isLeaf)){ 
            printYourChildren(nodeToPrint, stringToPrint);
        }

        if(amount!=0){

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
            if(i==-1){
                printf("Actually just checking if it gets here. i=-1 in printYourChildren\nShould probably free nextWord here as well\n");
            }
            char nextWord[longestWord];
            zeroOut(nextWord, longestWord); //initialize the array
           
            // for (size_t i = 0; i < longestWord; i++)
            // {
            //     nextWord[i] = '\0';
            // }//initialize the array

            if(strlen(stringUntillNow)){strcpy(nextWord, stringUntillNow);} //only copy the string uptill now if it isn't empty

            char nextLetter = i+97; //+97 to ASCII table (0+97-->97-->a)

            nextWord[strlen(stringUntillNow)] = nextLetter; //add the next letter

            printYourself(nodeToIterateOver->characterArray[i], nextWord);
            
        }
        
    
}

void zeroOut(char* zeroMe, int length){
    for (size_t i = 0; i < length; i++)
    {
        zeroMe[i]='\0';
    }
    
}

int main(int argc, char const *argv[]){

    if(argc==1){
        printf("Please use this program the intended way. Usage - give me a list of words. if the first argument is r, I will print the in reverse order.");
        exit(-1);
    }


    longestWord = strlen(argv[1]);
    for (size_t i = 1; i < argc; i++) //look for the longest word in the given input
    {
        int currentWordLength = strlen(argv[i]);
        if(currentWordLength>longestWord){longestWord = currentWordLength;}
    }
    longestWord++; //to allow place for '\0' in the answer array
    


    

    node* head = (node*) malloc(sizeof(node)); //create head node of the Trie tree
    head->counter=0;
    head->isLeaf=false;
    for (size_t i = 0; i < CHAR_SIZE; i++) {head->characterArray[i] = NULL;}

    char* currentWord = (char*) malloc(sizeof(char)*longestWord);
    int firstWordIndex = 1;
    if(strlen(argv[1])==1){
        if(strcmp(argv[1], "r")==0){
            firstLetter = CHAR_SIZE-1; 
            goBackwards = true; 
            addToCounter = -1; //values that change the order of printing the words of the tree
            firstWordIndex++; //if the order 'r' was given' it's a command. Don't insert it to the Trie.    
        }
    }
    for (size_t i = firstWordIndex; i < argc; i++)
    {
        zeroOut(currentWord,longestWord); //zeroOut the currentWord string before reusing it
        strcpy(currentWord, argv[i]);
        insertNewWord(head, currentWord);
    }
    free(currentWord);
    char* giveToPrintAsPointer = (char*) malloc(sizeof(char)*longestWord);
    zeroOut(giveToPrintAsPointer,longestWord);
    printYourself(head, giveToPrintAsPointer);

    if(giveToPrintAsPointer) {free(giveToPrintAsPointer);}
    node* headCopy = head;
    if(headCopy){killTree(headCopy);}
    


    
    return 0;
}
