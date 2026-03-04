
#include "inverted_index.h"

int search_Database(Wlist *head, char *word)
{
    if (head == NULL)
    {
        printf("List is empty\n");
        return FAILURE;
    }

    while (head)
    {
        if (!strcmp(head->word, word))
        {
            printf("Word '%s' is present in %d file(s):\n",
                   word, head->file_count);

            Ltable *Thead = head->Tlink;

            while (Thead)
            {
                printf("  %s -> %d times\n",
                       Thead->file_name,
                       Thead->word_count);

                Thead = Thead->link;   
            }
            return SUCCESS;
        }
        head = head->link;
    }

    printf("Word '%s' not found\n", word);
    return FAILURE;
}
