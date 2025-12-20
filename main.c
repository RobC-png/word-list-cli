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

void printWord(LetterNode * head){
    while(head != NULL){
        printf("%c", head->letter);
        head = head->next;
    }
}

void printWords(WordNode * head){
    //oops, emtpy list
    if(head == NULL){
        printf("\nempty list");
        return;
    }

    //filled list, don't forget the trailing \n
    printf("\n");
    while(head != NULL){
        printWord(head->word);
        printf(" ");
        head = head->next;
    }
    return;
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

WordNode * createWordNote(LetterNode * wordHead){
    WordNode * newHead = (WordNode *)malloc(sizeof(WordNode));
    newHead->word = wordHead;
    newHead->next = NULL;
    return newHead;
}

WordNode * addWordNodeFirst(WordNode * head, WordNode * nodeToAdd){
    nodeToAdd->next = head;
    return nodeToAdd;
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

    WordNode * newNode = createWordNote(wordLL);

    //List Emtpy
    if(head == NULL){
        newNode->next = head;
        return newNode;
    }

    //list filled
    WordNode * temp = head;
    while(temp->next != NULL)
        temp = temp->next;
    temp->next = newNode;
    return head;
}

WordNode * insertWordNodeAt(WordNode * head, int index, WordNode * nodeToAdd){

    if(index == 0){
        head = addWordNodeFirst(head, nodeToAdd);
        return head;
    }

    WordNode * before = head;
    for(int i = 0; i < index - 1; i++){
        before = before->next;
    }

    nodeToAdd->next = before->next;
    before->next = nodeToAdd;

    return head;
}

WordNode * insert(WordNode * head){
    //getting input
    int index;
    printf("\nEnter Index: ");
    scanf(" %d", &index);

    int maxIndex = wordLLSize(head);
    int minIndex = 0;

    //invalid index
    if(index > maxIndex || index < minIndex){
        printf("\nInvalid index");
        return head;
    }

    //valid index

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

    WordNode * newWord = createWordNote(wordLL);
    head = insertWordNodeAt(head, index, newWord);
    return head;
}

LetterNode * delLetterNode(LetterNode * head){

    if(head == NULL)
        return head;

    LetterNode * temp = head;
    head = head->next;
    free(temp);
    return head;
}

LetterNode * delLetterList(LetterNode * head){
    while(head != NULL)
          head = delLetterNode(head);
    return NULL; //not needed, but gets rid of pointer pointing to freed mem
}

WordNode * delWordNode(WordNode * head){

    if(head == NULL)
        return head;

    WordNode * temp = head;
    head = head->next;
    temp->word = delLetterList(temp->word); //free the letter LL
    free(temp); //but the pointer gets freed here anyway
    return head;
}

WordNode * delWordList(WordNode * head){
    while(head != NULL)
        head = delWordNode(head);
    return NULL; //not needed, but gets rid of pointer pointing to freed mem
}

WordNode * delete(WordNode * head){
    //getting input
    int index;
    printf("\nEnter Index: ");
    scanf(" %d", &index);

    int size = wordLLSize(head);

    //if the list is emtpy
    if(size == 0)
        return head;

    int maxIndex = size - 1;
    int minIndex = 0;

    //invalid index
    if(index > maxIndex || index < minIndex){
        printf("\nInvalid index");
        return head;
    }

    //valid index

    //if we delete from the beginning
    if(index == 0)
        return delWordNode(head);

    //keeping the old head to return it
    WordNode * before = head;

    //advancing to before the delete node
    for(int i = 0; i < index - 1; i++){
        before = before->next;
    }

    //make before link to nodeToDelete->next, free node to delete
    WordNode * nodeToDelete = before->next;
    before->next = nodeToDelete->next;
    //make sure to both delete the letter LL and the node itself
    delLetterList(nodeToDelete->word);
    free(nodeToDelete);

    return head;
}

int main(){
    char input;
    WordNode * wordsLL = NULL;
    do{
        input = menu();
        switch(input){
        case 'a':
            wordsLL = append(wordsLL);
            break;
        case 'i':
            wordsLL = insert(wordsLL);
            break;
        case 'd':
            wordsLL = delete(wordsLL);
            break;
        case 's':
            printf("\nYOU CHOSE S");
            break;
        case 'p':
            printWords(wordsLL);
            break;
        case 'x':
            wordsLL = delWordList(wordsLL); //theoretically not needed to reassign the wordsLL pointer, but just in case
            break;
        }
    } while (input != 'x');

    return 0;
}
