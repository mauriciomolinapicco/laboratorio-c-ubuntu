#include <stdio.h>
#include <string.h>

int main(void) 
{
    FILE *file = fopen("phonebook.csv", "a");
    if (file == NULL)
    {
        return 1;
    }
    char name[50] = "Mauricio";
    char number[50] = "+1122334455";

    fprintf(file, "%s:%s\n", name, number);
    fclose(file); 
}