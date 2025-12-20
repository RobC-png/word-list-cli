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

int wordSize(LetterNode * head){
    int i = 0;
    while(head != NULL){
        head = head->next;
        i++;
    }
    return i;
}

int compare_length(LetterNode* m, LetterNode* n){
    int mLen = wordSize(m);
    int nLen = wordSize(n);
    int diff = mLen - nLen;
    return diff;
}

void printWord(LetterNode * head){
    while(head != NULL){
        printf("%c", head->letter);
        head = head->next;
    }
}

void printWords(WordNode * head){
    //emtpy list
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

    //create a temp node to keep head
    WordNode * before = head;
    //loop to in front of the insertion index
    //index is already validated
    for(int i = 0; i < index - 1; i++){
        before = before->next;
    }

    //add the node between before and before->next
    nodeToAdd->next = before->next;
    before->next = nodeToAdd;

    return head;
}

WordNode * insert(WordNode * head){
    //getting input
    int index;
    printf("\nEnter Index: ");
    scanf(" %d", &index);

    //can also insert at maxIndex + 1, therefore no -1
    int maxIndex = wordLLSize(head);
    int minIndex = 0;

    //validate index
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

    //if the LetterLL is emtpy
    if(head == NULL)
        return head;

    //shift head and del old one
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

    //if WordLL is emtpy
    if(head == NULL)
        return head;

    //shift head and del old one
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

    //can only del existing indexes
    int maxIndex = size - 1;
    int minIndex = 0;

    //index validation
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

//base algo: insertion sort
WordNode * sort(WordNode * head, int (*compare)(LetterNode*, LetterNode*), int descending){
    
    //we set the first node to be sorted
    WordNode * sortedPoint = head;

    //if the head is emtpy there is nothing to sort
    //same thing if there only is one element
    if(sortedPoint == NULL || sortedPoint->next == NULL)
        return head;

    //loop through the list until the sorted point is the last node
    //then we know the list is sorted
    while(sortedPoint->next != NULL){

        //get the first node after the sorted point
        WordNode * nodeToSort = sortedPoint->next;

        //extract the nodeToSort from the LL
        //it still points to the next Node, but when traversing it wont be found
        sortedPoint->next = nodeToSort->next;

        //looping through the list again
        WordNode * temp = head; //keeping track of the inner loop position
        WordNode * prev = NULL; //stays 1 behind temp, for insertion
        int inserted = 0; //to check if the value was inserted in the middle or end

        //goes through the sorted list and checks where to insert the nodeToSort
        //stops when it reaches the first node outside of the sorted list
        while(temp != sortedPoint->next){

            //comparison result
            //cmp > 0: nodeToSort should come after temp (keep searching)
            //cmp == 0: nodeToSort equals temp (insert here)
            //cmp < 0: nodeToSort should come before temp (insert here)
            int cmp = compare(nodeToSort->word, temp->word);

            //flip when sorting desc
            cmp = descending ? -cmp : cmp;

            //insert the node before the temp node
            if(cmp <= 0){
                nodeToSort->next = temp;

                if(prev == NULL){
                    //inserting at the beginning
                    head = nodeToSort;
                } else{
                    //inserting in the middle
                    prev->next = nodeToSort;
                }
                
                //insertion point in the middle has been found, exit the inner loop
                inserted = 1;
                break;
            }

            //if the point wasnt found, check the next node
            prev = temp;
            temp = temp->next;
        }

        //if the inner loops stops with inserted = 0:
        //we need to insert at the end
        if(!inserted){
            //reinsert nodeToSort at the end of the sorted list
            nodeToSort->next = sortedPoint->next;
            sortedPoint->next = nodeToSort;
            //sortedPoint is now the confirmed end of the sorted list
            sortedPoint = sortedPoint->next;
        }
        //no need to move the sorted point forward, if it wasn't added at the end
    }
    return head;
}

WordNode * sortMenu(WordNode * head){
    //getting input
    char sortBy;
    printf("\nSort (a)lphabetically or by (l)ength? ");
    scanf(" %c", &sortBy);

    char ascDesc;
    printf("\nSort (a)scending or (d)escending? ");
    scanf(" %c", &ascDesc);

    head = sort(
        head,
        sortBy  == 'a' ? compare_alphabethically : compare_length,
        ascDesc == 'd' ? 1 : 0
    );

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
            wordsLL = sortMenu(wordsLL);
            break;
        case 'p':
            printWords(wordsLL);
            break;
        case 'x':
            //theoretically not needed to reassign the wordsLL pointer, but just in case
            wordsLL = delWordList(wordsLL);
            break;
        }
    } while (input != 'x');

    return 0;
}
