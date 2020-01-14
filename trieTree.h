#ifndef TRIETREE_H_
#define TRIETREE_H_

#define CHAR_SIZE 26

typedef struct node {
    bool isLeaf;
    int counter;
    struct node* characterArray[CHAR_SIZE];
}node;

node* getNewNode();

node* insertNewLetter(node* startNode, char character);

void insertNewWord(node* head, char* str);

void killTree(node* killMe);

void printYourself(node* nodeToPrint, char* stringToPrint);

void printYourChildren(node* nodeToIterateOver, char* stringUntillNow);

void zeroOut(char* zeroMe, int length);

void initNode(node* nodeToInit);


#endif /* TRIETREE_H_ */