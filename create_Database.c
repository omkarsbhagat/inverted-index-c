#include "inverted_index.h"

/* Create database */
int create_Database(Flist *f_head, Wlist *head[])
{
    while (f_head)
    {
        read_datafile(f_head, head, f_head->filename);
        f_head = f_head->link;
    }

    return SUCCESS;
}

/* Read file and create inverted index */
Wlist *read_datafile(Flist *file, Wlist *head[], char *filename)
{
    FILE *fptr = fopen(filename, "r");
    if (fptr == NULL)
        return NULL;

    char word[WORD_SIZE];

    while (fscanf(fptr, "%s", word) != EOF)
    {
         for (int i = 0; word[i]; i++)
        {
            word[i] = tolower(word[i]);
        }
        int index = tolower(word[0]) % 97;
        if (!(index >= 0 && index <= 25))
            index = 26;

        if (head[index] == NULL)
        {
            insert_at_last(&head[index], word, filename);
        }
        else
        {
            Wlist *temp = head[index];
            int flag = 1;

            while (temp)
            {
                if (!strcmp(temp->word, word))
                {
                    update_word_count(&temp, filename);
                    flag = 0;
                    break;
                }
                temp = temp->link;
            }

            if (flag)
                insert_at_last(&head[index], word, filename);
        }
    }
    fclose(fptr);
    return NULL;
}

/* Insert new word */
int insert_at_last(Wlist **head, char *word, char *filename)
{
    Wlist *new = malloc(sizeof(Wlist));
    strcpy(new->word, word);
    new->file_count = 1;
    new->link = NULL;

    Ltable *lt = malloc(sizeof(Ltable));
    strcpy(lt->file_name, filename);
    lt->word_count = 1;
    lt->link = NULL;

    new->Tlink = lt;

    if (*head == NULL)
        *head = new;
    else
    {
        Wlist *temp = *head;
        while (temp->link)
            temp = temp->link;
        temp->link = new;
    }
    return SUCCESS;
}

/* Update word count */
int update_word_count(Wlist **head, char *filename)
{
    Ltable *temp = (*head)->Tlink;

    while (temp)
    {
        if (!strcmp(temp->file_name, filename))
        {
            temp->word_count++;
            return SUCCESS;
        }
        temp = temp->link;
    }

    /* New file entry */
    Ltable *new = malloc(sizeof(Ltable));
    strcpy(new->file_name, filename);
    new->word_count = 1;
    new->link = (*head)->Tlink;

    (*head)->Tlink = new;
    (*head)->file_count++;

    return SUCCESS;
}
