#ifndef TRIETREE_H_
#define TRIETREE_H_

#define CHAR_SIZE 26

typedef struct node {
    bool isLeaf;
    int counter;
    struct node* characterArray[CHAR_SIZE];
}node;

node* getNewNode();

void insertNewWord(node* head, char* str);

void killTree(node* killMe);

void printYourself(node* nodeToPrint, char* stringToPrint);

void printYourChildren(node* nodeToIterateOver, char* stringUntillNow);



#endif /* TRIETREE_H_ */