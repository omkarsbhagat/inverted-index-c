#ifndef INVERTED_INDEX_H
#define INVERTED_INDEX_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* ---------- Macros ---------- */
#define FAILURE 0
#define SUCCESS 1
#define EMPTY 2
#define FILE_NOT_PRESENT 3
#define FILE_REPEAT 4

#define WORD_SIZE 26
#define FNAME_SIZE 30
#define HASH_SIZE 26

/* ---------- File Linked List ---------- */
typedef struct file_node
{
    char filename[FNAME_SIZE];
    struct file_node *link;
} Flist;

/* ---------- Link Table (Sub Node) ---------- */
typedef struct linkTable_node
{
    int word_count;                     // frequency of word in file
    char file_name[FNAME_SIZE];         // file name
    struct linkTable_node *link;        // next sub node
} Ltable;

/* ---------- Word Node (Main Node) ---------- */
typedef struct word_node
{
    int file_count;                     // number of files containing the word
    char word[WORD_SIZE];               // indexed word
    Ltable *Tlink;                      // pointer to link table
    struct word_node *link;             // next word node
} Wlist;

/* ---------- Function Prototypes ---------- */

/* File validation */
int file_validation_list(Flist **f_head, char *argv[]);
int isFileempty(char *filename);
int create_list_file(Flist **f_head, char *filename);

/* Database creation */
int create_Database(Flist *f_head, Wlist *head[]);
Wlist *read_datafile(Flist *file, Wlist *head[], char *filename);

/* Word handling */
int insert_at_last(Wlist **head, char *word, char *filename);
int update_word_count(Wlist **head, char *filename);

/* Database operations (to be implemented later) */
int display_Database(Wlist *head[]);
int search_Database(Wlist *head, char *search_word);
int update_Database(Wlist *head[], Flist **f_head);
int save_Database(Wlist *head[]);

#endif
