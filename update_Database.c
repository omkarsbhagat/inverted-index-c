#include "inverted_index.h"

int update_Database(Wlist *head[], Flist **f_head)
{
    char filename[FNAME_SIZE];

    printf("Enter the New Filename that need to be added\n");
    scanf("%s", filename);

    /* ---- check file availability & emptiness ---- */
    int status = isFileempty(filename);

    if (status == FILE_NOT_PRESENT)
    {
        printf("File %s is not present\n", filename);
        return FAILURE;
    }
    else if (status == EMPTY)
    {
        printf("File %s is empty\n", filename);
        return FAILURE;
    }

    /* ---- add file to file linked list ---- */
    int ret = create_list_file(f_head, filename);

    if (ret == FILE_REPEAT)
    {
        printf("File %s already exists\n", filename);
        return FAILURE;
    }
    else if (ret == FAILURE)
    {
        printf("Unable to add file\n");
        return FAILURE;
    }

    printf("File %s added successfully (UPDATE)\n", filename);

    /* ---- update database using ONLY the new file ---- */
    Flist *temp = *f_head;
    while (temp->link)
        temp = temp->link;

    read_datafile(temp, head, temp->filename);

    printf("Database updated successfully using file %s\n", filename);
    return SUCCESS;
}
