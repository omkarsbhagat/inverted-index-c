#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "inverted_index.h"



int file_validation_list(Flist **f_head, char *argv[])
{
    int i = 1;
    int status;
    int valid_count = 0;

    while (argv[i] != NULL)
    {
        status = isFileempty(argv[i]);

        if (status == FILE_NOT_PRESENT)
        {
            printf("File %s is not available\n", argv[i]);
            printf("Hence we are not adding that file to Linked List\n");
        }
        else if (status == EMPTY)
        {
            printf("File %s is not having any content\n", argv[i]);
            printf("Hence we are not adding that file to Linked List\n");
        }
        else
        {
            int ret = create_list_file(f_head, argv[i]);

            if (ret == SUCCESS)
            {
                printf("The file has been Added : %s\n", argv[i]);
                valid_count++;
            }
            else if (ret == FILE_REPEAT)
            {
                printf("Duplicate file %s not added\n", argv[i]);
            }
        }
        i++;
    }

    if (valid_count == 0)
        return FAILURE;

    return SUCCESS;
}


int isFileempty(char *filename)
{
    FILE *fptr = fopen(filename, "r");

    /* File open failed */
    if (fptr == NULL)
    {
        if (errno == ENOENT)
        {
            return FILE_NOT_PRESENT;
        }
        return FAILURE;
    }

    /* Check for empty file */
    fseek(fptr, 0, SEEK_END);

    if (ftell(fptr) == 0)
    {
        fclose(fptr);
        return EMPTY;
    }

    fclose(fptr);
    return SUCCESS;
}


int create_list_file(Flist **f_head, char *filename)
{
    Flist *temp = *f_head;

    /* Check for duplicate file */
    while (temp != NULL)
    {
        if (strcmp(temp->filename, filename) == 0)
        {
            return FILE_REPEAT;
        }
        temp = temp->link;
    }

    /* Create new node */
    Flist *new = malloc(sizeof(Flist));
    if (new == NULL)
    {
        return FAILURE;
    }

    strcpy(new->filename, filename);
    new->link = NULL;

    /* Insert at last */
    if (*f_head == NULL)
    {
        *f_head = new;
        return SUCCESS;
    }

    temp = *f_head;
    while (temp->link != NULL)
    {
        temp = temp->link;
    }

    temp->link = new;
    return SUCCESS;
}
