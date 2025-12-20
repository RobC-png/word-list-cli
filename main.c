#include <stdio.h>
#include <stdlib.h>

typedef struct letternode {
    char letter;
    struct letternode* next;
} LetterNode;

typedef struct wordnode {
    LetterNode* word;
    struct wordnode* next;
} WordNode;

int compare_alphabethically(LetterNode* m, LetterNode* n) {
    int valueM = m != NULL ? m->letter : 0; // ASCII value of the letter
    int valueN = n != NULL ? n->letter : 0; // or 0 when node is NULL
    int diff = valueM - valueN;             // indicates which letter is the higher value

    // on equal value
    if (diff == 0 && m != NULL && n != NULL) {
        // continue recursively
        return compare_alphabethically(m->next, n->next);
    }

    return diff;
}

int wordLLSize(WordNode * head){
    int i = 0;
    while(head != NULL){
        head = head->next;
        i++;
    }
    return i;
}

char menu(){
    char input;
    printf("\nChoose action: (a)ppend, (i)nsert, (d)elete, (s)ort, (p)rint, e(x)it: ");
    scanf(" %c", &input);
    return input;
}

LetterNode * createLetterNode(char letter){
    LetterNode * newNode = (LetterNode *)malloc(sizeof(LetterNode));
    newNode->letter = letter;
    newNode->next = NULL;
    return newNode;
}

LetterNode * addLetterNodeAtEnd(LetterNode * head, LetterNode * nodeToAdd){
    //List Emtpy
    if(head == NULL){
        nodeToAdd->next = head;
        return nodeToAdd;
    }

    //list filled
    LetterNode * temp = head;
    while(temp->next != NULL)
        temp = temp->next;
    temp->next = nodeToAdd;
    return head;
}

void printWord(LetterNode * head){
    while(head != NULL){
        printf("%c", head->letter);
        head = head->next;
    }
}

WordNode * createWordNote(LetterNode * wordHead){
    WordNode * newHead = (WordNode *)malloc(sizeof(WordNode));
    newHead->word = wordHead;
    return newHead;
}

WordNode * addWordNodeFirst(WordNode * head, WordNode * nodeToAdd){
    nodeToAdd->next = head;
    return nodeToAdd;
}

WordNode * addWordNodeAt(WordNode * head, int index, WordNode * nodeToAdd){


    if(index == 0){
        return addWordNodeFirst(head, nodeToAdd);
    }
}

WordNode * append(WordNode * head){
    //getting input
    char wordArr[21] = {};
    printf("\nEnter Word: ");
    scanf(" %20s", wordArr);

    //converting string to LL
    LetterNode * wordLL = NULL;
    int i = 0;
    while(wordArr[i] != '\0'){
        wordLL = addLetterNodeAtEnd(wordLL, createLetterNode(wordArr[i]));
        i++;
    }

    printWord(wordLL);

    return head;
}

WordNode * insert(WordNode * head){
    int maxIndex = wordLLSize(head) - 1;
    int minIndex = 0;
    if(index > maxIndex || index < minIndex)
        printf("\nInvalid index");

    return head;
}

int main(){
    char input;
    WordNode * wordsLL = NULL;
    do{
        input = menu();
        switch(input){
        case 'a':
            printf("\nYOU CHOSE A");
            wordsLL = append(wordsLL);
            break;
        case 'i':
            printf("\nYOU CHOSE I");
            break;
        case 'd':
            printf("\nYOU CHOSE D");
            break;
        case 's':
            printf("\nYOU CHOSE S");
            break;
        case 'p':
            printf("\nYOU CHOSE P");
            break;
        case 'x':
            printf("\nYOU CHOSE X");
            break;
        }
    } while (input != 'x');

    return 0;
}
