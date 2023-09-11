#include "stdio.h"
#include "stdlib.h"

#include "getoutinfo.h"
#include "sorter.h"

int main()
{
    FILE* fp = fopen(FILE_NAME, "r");

    if (fp == NULL)
    {
        perror("Failed to open file");
        printf("Input file: %s\n", FILE_NAME);
        return 1;
    }

    fseek(fp, 0, SEEK_END);
    size_t text_len = ftell(fp);

    char* text = (char* ) calloc(text_len, sizeof(char));

    size_t line_amount = 0;

    fclose(fp);

    bool success = ReadFile(text, &line_amount);
    if (!success)
    {
        perror("Failed to read file data");
        return 2;
    }

    char** lines_pointers = (char** ) calloc(line_amount, sizeof(char*));
    lines_pointers[0] = text;

    CreatePtrArray(lines_pointers, text, text_len);

    StdSort(lines_pointers, line_amount);

    PrintText((const char**) lines_pointers, line_amount);

    free(lines_pointers);
    free(text);
}

