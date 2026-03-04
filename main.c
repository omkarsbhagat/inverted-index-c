#include <stdio.h>
#include <stdlib.h>
#include "inverted_index.h"

int main(int argc, char *argv[])
{
    int choice;

    system("clear");

    /* inverted index heads */
    Wlist *head[27] = { NULL };

    /* file linked list */
    Flist *f_head = NULL;

    /* CLA validation */
    if (argc <= 1)
    {
        printf("ERROR : Enter valid number of arguments\n");
        printf("Usage : ./inverted file1.txt file2.txt ...\n");
        return FAILURE;
    }

    /* file validation */
    if (file_validation_list(&f_head, argv) == FAILURE)
    {
        printf("ERROR : No valid files found\n");
        return FAILURE;
    }

    while (1)
    {
        printf("\n----------- INVERTED SEARCH -----------\n");
        printf("1. Create Database\n");
        printf("2. Display Database\n");
        printf("3. Search Database\n");
        printf("4. Update Database\n");
        printf("5. Save Database\n");
        printf("6. Exit\n");
        printf("--------------------------------------\n");
        printf("Enter your choice : ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                if (create_Database(f_head, head) == SUCCESS)
                    printf("Database created successfully\n");
                else
                    printf("Database creation failed\n");
                break;

            case 2:
                display_Database(head);
                break;

            case 3:
            {
                char word[WORD_SIZE];

                printf("Enter the word to be searched\n");
                scanf("%s", word);

                /* convert word to lowercase */
                for (int i = 0; word[i]; i++)
                {
                    word[i] = tolower(word[i]);
                }

                /* calculate index */
                int index = tolower(word[0]) % 97;

                if (!(index >= 0 && index <= 25))
                {
                    printf("Invalid word\n");
                    break;
                }

                
                search_Database(head[index], word);
                break;
            }


            case 4:
                update_Database(head, &f_head);
                break;

            case 5:
                save_Database(head);
                break;
            
            case 6:
                printf("Exiting...\n");
                return SUCCESS;

            default:
                printf("Invalid choice\n");
        }
    }
}
