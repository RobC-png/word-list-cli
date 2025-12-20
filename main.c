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
