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

struct LineParams* CreateLinePtrsArray(struct Storage* info)
{
    assert(info);

    info->lines = (struct LineParams* ) calloc(info->line_amt, sizeof(struct LineParams));

    if (info->lines ==  NULL)
        return NULL;

    info->lines[0].string = (char* ) info->buf;

    size_t line       = 1;
    size_t string_len = 0;

    for (off_t i = 0; i < info->text_len; i++)
    {
        if (info->buf[i] == '\0')
        {
            info->lines[line - 1].len  = info->buf + i - info->lines[line - 1].string;
            info->lines[line++].string = info->buf + i + 1;

            string_len = 0;
        }
        string_len++;
    }

    return info->lines;
}

//-------------------------------------------------------------------------------------------

bool PrintText(const struct LineParams* lines, const size_t line_amount, const char* header)
{
    assert(lines);

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
        PrintLine(lines, line, fp);
    }

    fprintf(fp, "\n----------------------------------------------------------------------------\n\n");

    fclose(fp);

    return true;
}

//-------------------------------------------------------------------------------------------

void PrintLine(const struct LineParams* lines, const size_t line, FILE* fp)
{
    assert(lines);

    for (int i = 0; (lines[line].string)[i] != '\0'; i++)
    {
        fputc((lines[line].string)[i], fp);
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

    info->lines = CreateLinePtrsArray(info);

    if (info->lines == NULL)
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
