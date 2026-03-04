#include "inverted_index.h"

int save_Database(Wlist *head[])
{
    char fname[FNAME_SIZE];

    printf("Enter the filename to save database : ");
    scanf("%s", fname);

    FILE *fptr = fopen(fname, "w");
    if (fptr == NULL)
    {
        printf("ERROR : Unable to open file\n");
        return FAILURE;
    }

    for (int i = 0; i < 26; i++)
    {
        if (head[i] != NULL)
        {
            fprintf(fptr, "@[%d]\n", i);

            Wlist *temp = head[i];
            while (temp)
            {
                fprintf(fptr, "word is [%s]: file_count:%d ",
                        temp->word, temp->file_count);

                Ltable *lt = temp->Tlink;
                while (lt)
                {
                    fprintf(fptr, "file:%s and word_count:%d ",
                            lt->file_name, lt->word_count);
                    lt = lt->link;
                }

                fprintf(fptr, "\n");
                temp = temp->link;
            }
        }
    }

    fclose(fptr);
    printf("Database saved successfully\n");
    return SUCCESS;
}
