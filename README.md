# Inverted Index Search

## Overview
The Inverted Index Search project is implemented in C using hashing and linked lists. It creates a searchable database from multiple text files by mapping words to the files in which they occur along with their occurrence count.

## Features
- File validation
- Database creation
- Word searching
- Database display
- Save database to file
- Update database from saved file

## Data Structures Used
- Hash Table (27 indexes)
- Main Linked List
- Sub Linked List

## Working
1. Read words from input text files.
2. Generate hash index based on the first character.
3. Store words in the main linked list.
4. Store file names and word counts in the sub linked list.
5. Perform fast search operations using hashing.

## Compilation
```bash
make
