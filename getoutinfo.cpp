#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/stat.h>
#include <ctype.h>

#include "getoutinfo.h"
#include "errors.h"

char* CreateTextBuf(struct Storage* info)
{
    assert(info);

    FILE* fp = fopen(INPUT_FILE, "rb");

    if (fp == NULL)
    {
        perror("Failed to open file");
        printf("Input file: \"%s\"\n", INPUT_FILE);
        return NULL;
    }

    info->text_len = CountFileLength(INPUT_FILE);

    info->buf = (char* ) calloc(info->text_len + 1, sizeof(char));
    // *text_len + 1 for confidence, that program will have enough memory

    if (fread(info->buf, sizeof(char), info->text_len, fp) != info->text_len)
        return NULL;

    if (info->buf[info->text_len]    != '\0')
        info->buf[info->text_len + 1] = '\0';

    for (int i = 0; i < info->text_len; i++)
    {
        if (info->buf[i] == '\n')
        {
            info->buf[i] = '\0';
            info->line_amt++;
        }
    }

    fclose(fp);

    return info->buf;
}

//-------------------------------------------------------------------------------------------

char** CreateLinePtrsArray(struct Storage* info)
{
    assert(info);

    info->lines_ptrs = (char** ) calloc(info->line_amt, sizeof(char*));

    if (info->lines_ptrs ==  NULL)
        return NULL;

    info->lines_ptrs[0] = (char* ) info->buf;

    size_t line = 1;

    for (off_t i = 0; i < info->text_len; i++)
    {
        if (info->buf[i] == '\0')
        {
            info->lines_ptrs[line++] = info->buf + i + 1;
        }
    }

    return info->lines_ptrs;
}

//-------------------------------------------------------------------------------------------

bool PrintText(const char** lines_pointers, const size_t line_amount)
{
    assert(lines_pointers);

    FILE* fp = fopen(OUTPUT_FILE, "wb");

    if (fp == NULL)
    {
        perror("Failed to open file");
        printf("Ouptut file: \"%s\"\n", OUTPUT_FILE);
        return false;
    }

    for (size_t line = 0; line < line_amount; line++)
    {
        PrintLine(lines_pointers, line, fp);
    }

    return true;
}

//-------------------------------------------------------------------------------------------

void PrintLine(const char** lines_pointers, const size_t line, FILE* fp)
{
    assert(fp);

    for (int i = 0; lines_pointers[line][i] != '\0'; i++)
    {
        fputc(lines_pointers[line][i], fp);
    }

    fputc('\n', fp);
}

//-------------------------------------------------------------------------------------------

off_t CountFileLength(const char* file_name)
{
    assert(file_name);

    struct stat buf;
    stat(file_name, &buf);

    return buf.st_size;
}



int CreateTextStorage(struct Storage* info)
{

    info->buf = CreateTextBuf(info);

    if (info->buf == NULL)
        return (int) ERRORS::READ_FILE;

    info->lines_ptrs = CreateLinePtrsArray(info);

    if (info->lines_ptrs == NULL)
        return (int) ERRORS::ALLOCATE_MEMORY;

    return (int) ERRORS::NOT;
}
