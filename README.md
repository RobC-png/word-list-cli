# Word List Manager (C)

Interactive command-line application that manages a list of words using
nested linked lists (word list → letter list).

Each word is stored as a linked list of characters, allowing fine-grained
control over memory and traversal.

## Features
- Append, insert, and delete words
- Words represented as linked lists of characters
- Sorting using insertion sort on linked lists
- Sort by alphabetical order or word length
- Ascending and descending order selection
- Explicit dynamic memory management with cleanup

## Concepts Demonstrated
- Pointer-based data structures
- Nested linked lists
- Manual memory management (`malloc` / `free`)
- Function pointers for comparator abstraction
- Recursive algorithms
- Linked list traversal and mutation

## Build & Run
```bash
gcc main.c -o wordlist
./wordlist
