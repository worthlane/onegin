#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/stat.h>
#include <ctype.h>

#include "getoutinfo.h"
#include "mylib/errors.h"

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

    // Add 1 for NUL-terminator ---------------v
    info->buf = (char* ) calloc(info->text_len + 1, sizeof(char));

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

bool PrintText(const char** lines_pointers, const size_t line_amount, const char* header)
{
    assert(lines_pointers);

    FILE* fp = fopen(OUTPUT_FILE, "ab");

    if (fp == NULL)
    {
        perror("Failed to open file");
        printf("Ouptut file: \"%s\"\n", OUTPUT_FILE);
        return false;
    }

    if (header != NULL)
        fprintf(fp, "%s\n\n", header);

    for (size_t line = 0; line < line_amount; line++)
    {
        PrintLine(lines_pointers, line, fp);
    }

    fprintf(fp, "\n----------------------------------------------------------------------------\n\n");

    fclose(fp);

    return true;
}

//-------------------------------------------------------------------------------------------

void PrintLine(const char** lines_pointers, const size_t line, FILE* fp)
{
    assert(lines_pointers);

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

//-------------------------------------------------------------------------------------------

int CreateTextStorage(struct Storage* info)
{

    info->buf = CreateTextBuf(info);

    if (info->buf == NULL)
        return (int) ERRORS::READ_FILE;

    info->lines_ptrs = CreateLinePtrsArray(info);

    if (info->lines_ptrs == NULL)
        return (int) ERRORS::ALLOCATE_MEMORY;

    return (int) ERRORS::NONE;
}

//-------------------------------------------------------------------------------------------

bool ClearFile(const char* FILE_NAME)
{
    FILE* fp = fopen(FILE_NAME, "wb");

    if (fp == NULL)
    {
        perror("Failed to open file");
        printf("File: \"%s\"\n", FILE_NAME);
        return false;
    }

    fclose(fp);

    return true;
}

//-------------------------------------------------------------------------------------------

bool PrintBuf(const char* buf, const size_t text_len, const char* header)
{
    assert(buf);

    FILE* fp = fopen(OUTPUT_FILE, "ab");

    if (fp == NULL)
    {
        perror("Failed to open file");
        printf("Ouptut file: \"%s\"\n", OUTPUT_FILE);
        return false;
    }

    if (header != NULL)
        fprintf(fp, "%s\n\n", header);

    // fwrite(buf, sizeof(char), text_len, fp); // not working cuz of nulls

    for (size_t i = 0; i < text_len; i++)
    {
        int ch = buf[i];

        if (buf[i] == 0)
            ch = '\n';

        fputc(ch, fp);
    }

    fprintf(fp, "\n----------------------------------------------------------------------------\n");

    fclose(fp);

    return true;
}
