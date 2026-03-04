#include <stdio.h>
#include "inverted_index.h"
int display_Database(Wlist *head[])
{
    int flag = 0;

    printf("\nIndex\tWord\t\tFileCount\tFilename\tWordCount\n");
    printf("---------------------------------------------------------------\n");

    for (int i = 0; i < 26; i++)
    {
        if (head[i] != NULL)
        {
            Wlist *wtemp = head[i];

            while (wtemp)
            {
                Ltable *ltemp = wtemp->Tlink;

                while (ltemp)
                {
                    printf("%d\t%-12s\t%d\t\t%-12s\t%d\n",
                           i,
                           wtemp->word,
                           wtemp->file_count,
                           ltemp->file_name,
                           ltemp->word_count);

                    ltemp = ltemp->link;
                }

                wtemp = wtemp->link;
                flag = 1;
            }
        }
    }

    if (flag == 0)
    {
        printf("Database is empty\n");
        return FAILURE;
    }

    return SUCCESS;
}
