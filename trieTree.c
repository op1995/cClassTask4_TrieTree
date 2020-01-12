#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "trieTree.h"


// #define CHAR_SIZE 26
bool goBackwards = false;
int firstLetter = 0;
int addToCounter = 1;
// int numberOfWordsAdded = 0;
// int copyArgc = 0;
// char** answer;
int longestWord = 0;

// typedef struct node {
//     bool isLeaf;
//     int counter;
//     struct node* characterArray[CHAR_SIZE];
// }node;

node* getNewNode(){
    node* newNode = (node*) malloc(sizeof(node));
    newNode->counter=0;
    newNode->isLeaf=true;
    for (size_t i = 0; i < CHAR_SIZE; i++) {newNode->characterArray[i] = NULL;}
    return newNode;
}

void insertNewWord(node* head, char* str){
    node* current = head;
    // int strLength = strlen(str);
    // for (size_t i = 0; i < strLength; i++)
    do
    {
        // printf("recived the character %c\n",*str);
        // int character_as_int = *str;
        // printf("character value = %d\n",character_as_int);

        if(*str<65 || *str>122 || (*str>90 && *str<97)){ //non Alphabet character. Should be skipped.
            // printf("skipping the character %c\n",*str);
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
    // printf("got to killTree\n");
    // node* currentNode = killMe;
    if(!(killMe->isLeaf)){
        // printf("killTree - starting for loop\n");
        for (size_t i = 0; i < CHAR_SIZE; i++){
            if(killMe->characterArray[i]) {killTree(killMe->characterArray[i]);}
        }
    }
    // printf("freeing a node\n");
    free(killMe);

    // for (size_t i = 0; i < CHAR_SIZE; i++){
    //     node* currentNode = killMe->characterArray[i];
    //     if(currentNode){killTree(currentNode);} //
    //     else {free(currentNode);}
    // }
    
}


// void printTree(node* printMe, char* stringUpTillNow){
    
//     if (printMe->isLeaf){
//     }

// }

void printYourself(node* nodeToPrint, char* stringToPrint){
    if(nodeToPrint){
        // printf("Started printYourself method\n");
        // printf("strlen(stringToPrint) = %ld\n",strlen(stringToPrint));
        // printf("stringToPrint = %s\n",stringToPrint);

        int amount = nodeToPrint->counter;
        // printf("amount = %d\n", amount);

        if(goBackwards && !(nodeToPrint->isLeaf)){
            // printf("got here - a\n");
            printYourChildren(nodeToPrint, stringToPrint);
        }

        if(amount!=0){
            // printf("got here - b\n");
            // char string[strlen(stringToPrint)+1];
            printf("%s\t%d\n", stringToPrint, amount);
        }

        if(!goBackwards && !(nodeToPrint->isLeaf)){
            // printf("got here - c\n");
            printYourChildren(nodeToPrint, stringToPrint);
        }
        // printf("got to free(nodeToPrint) in printYourself method\n");
        // if(nodeToPrint){free(nodeToPrint);}
    }
}//end printYourself

void printYourChildren(node* nodeToIterateOver, char* stringUntillNow){
    // printf("children - got here - a\n");
    for (size_t i = firstLetter; i!=CHAR_SIZE && i!=-1; i = i+addToCounter)
        {
            if(i==-1){
                printf("Actually just checking if it gets here. i=-1 in printYourChildren\nShould probably free nextWord here as well\n");
            }
            // int nextStringSize = strlen(stringUntillNow)+2; //TODO - should probably be 2
            char nextWord[longestWord];
            for (size_t i = 0; i < longestWord; i++)
            {
                nextWord[i] = '\0';
            }//initialize the array
            
            // strcpy(nextWord,"^");
                        // char* nextWord = (char*) malloc(sizeof(char)*nextStringSize);
            // nextWord = "N";
            // printf("created nextWord charArray. Also, nextStringSize = %d\n",nextStringSize);
            // printf("strlen(stringUntillNow) = %ld\n",strlen(stringUntillNow));
            if(strlen(stringUntillNow)){strcpy(nextWord, stringUntillNow);}
            // else{strcpy(nextWord,"^");} //just a value to not leav nextWord variable not initialized
            // printf("123, next Word = %s\n",nextWord);
            // printf("nextWord = %s",nextWord);
            char nextLetter = i+97;
                                        // printf("nextLetter = %c\n",nextLetter);
            // char* nextChar = (char*)(i+97);
            // printf("nextChar = %s",nextChar);

            // printf("nextWord before adding next letter = %s\n",nextWord);
            nextWord[strlen(stringUntillNow)] = nextLetter;
            // char nextLetter = i+97;
            // char* nextLetter = (char*) ((char)i+97);
            // strcat(nextWord, nextLetter);
                    // printf("If you got here, it worked! nextWord = %s\n",nextWord);

            // char* tester = (char*) malloc(sizeof(char)*10);
            // tester = "T";
            // char* tester2 = "A";
            // strcat(tester, tester2); //THIS WORKED
            // printf("tester = %s\n",tester);

            // strcat(tester, nextWord); //THIS WORKED
            // printf("tester = %s\n",tester);

            // strcat(nextWord, (char*)(i+97));
            // strcat(nextWord, tester);
                    // printf("children - got here - b - after creating the string to forward\n");
            printYourself(nodeToIterateOver->characterArray[i], nextWord);
            // if(i==CHAR_SIZE-1){free(nextWord);} //only on older version, that used malloc || at the last iteration, free the malloced string
            
        }
        
    
}

void zeroOut(char* zeroMe, int length){
    for (size_t i = 0; i < length; i++)
    {
        zeroMe[i]='\0';
    }
    
}

int main(int argc, char const *argv[]){

    if(argc<2){
        printf("Please use this program the intended way. Usage - give me a list of words. if the first argument is r, I will print the in reverse order.");
        exit(-1);
    }

    // answer = malloc(argc*sizeof(char*));

    longestWord = strlen(argv[1]);
    for (size_t i = 1; i < argc; i++) //look for the longest word in the given input
    {
        int currentWordLength = strlen(argv[i]);
        if(currentWordLength>longestWord){longestWord = currentWordLength;}
    }
    longestWord++; //to allow place for '\0' in the answer array
    // for (size_t i = 0; i < argc; i++) {answer[i] = malloc(sizeof(char)*longestWord);} //dynamiclly set the size of each string in the answer array to length of longest input word
    


    

    node* head = (node*) malloc(sizeof(node)); //create head node of the Trie tree
    head->counter=0;
    head->isLeaf=false;
    for (size_t i = 0; i < CHAR_SIZE; i++) {head->characterArray[i] = NULL;}

    // char* currentWord = NULL;
    char* currentWord = (char*) malloc(sizeof(char)*longestWord);
    int firstWordIndex = 1;
    if(strlen(argv[1])==1){
        // printf("strlen(argv[1])==1\n");
        if(strcmp(argv[1], "r")==0){
            // printf("strcmp(argv[1], \"r\")\n");
            firstLetter = CHAR_SIZE-1; 
            goBackwards = true; 
            addToCounter = -1; //values that change the order of printing the words of the tree
            firstWordIndex++; //if the order 'r' was given' it's a command. Don't insert it to the Trie.    
        }
    }
    for (size_t i = firstWordIndex; i < argc; i++)
    {
        // currentWord = (char*) malloc(sizeof(char)*(strlen(argv[i])));
        zeroOut(currentWord,longestWord); //zeroOut the currentWord string before reusing it
        strcpy(currentWord, argv[i]);
        // printf("is next line use of uninitialied value?\n");
        insertNewWord(head, currentWord);
        // printf("inserted the word - %s\n",currentWord);
    }
    free(currentWord);
    // printf("after inserting all the words to the Trie\n");
    char* giveToPrintAsPointer = (char*) malloc(sizeof(char)*longestWord);
    zeroOut(giveToPrintAsPointer,longestWord);
    printYourself(head, giveToPrintAsPointer);

    if(giveToPrintAsPointer) {free(giveToPrintAsPointer);}
    node* headCopy = head;
    if(headCopy){killTree(headCopy);}
    // if(head){free(head);}
    


    
    return 0;
}
