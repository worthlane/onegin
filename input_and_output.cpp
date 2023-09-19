#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/stat.h>
#include <ctype.h>

#include "input_and_output.h"
#include "mylib/errors.h"
#include "mylib/colorlib.h"

int FillLineStruct(struct Storage* info, struct ErrorInfo* error)
{
    assert(info);

    info->lines = (struct LineParams* ) calloc(info->line_amt, sizeof(struct LineParams));

    if (info->lines ==  NULL)
        return (int) (error->code = ERRORS::ALLOCATE_MEMORY);

    info->lines[0].string = (char* ) info->buf;

    size_t line = 1;

    for (off_t i = 0; i < info->text_len; i++)
    {
        if (info->buf[i] == '\0')
        {
            info->lines[line - 1].len  = info->buf + i - info->lines[line - 1].string;
            info->lines[line++].string = info->buf + i + 1;
        }
    }

    return (int) (error->code = ERRORS::NONE);
}

//-------------------------------------------------------------------------------------------

bool PrintAllLines(FILE* stream, const struct LineParams* lines,
                   const size_t line_amount, struct ErrorInfo* error)
{
    assert(lines);

    for (size_t line = 0; line < line_amount; line++)
    {
        PrintOneLine(stream, &lines[line], error);
        if (error->code == ERRORS::PRINT_DATA)
            return false;
    }

    return true;
}

//-------------------------------------------------------------------------------------------

void PrintOneLine(FILE* stream, const struct LineParams* line, struct ErrorInfo* error)
{
    assert(line);

    for (int i = 0; (line->string)[i] != '\0'; i++)
    {
        if (fputc((line->string)[i], stream) == EOF)
        {
            error->code = ERRORS::PRINT_DATA;
            return;
        }
    }

    if (fputc('\n', stream) == EOF)
            error->code = ERRORS::PRINT_DATA;
}

//-------------------------------------------------------------------------------------------

off_t GetFileLength(const char* file_name)
{
    assert(file_name);

    struct stat buf;
    stat(file_name, &buf);

    return buf.st_size;
}

//-------------------------------------------------------------------------------------------

int CreateTextStorage(struct Storage* info, struct ErrorInfo* error)
{
    assert(info);

    FILE* fp = fopen(INPUT_FILE, "rb");

    if (fp == NULL)
    {
        error->param = (char*) INPUT_FILE;
        return (int) (error->code = ERRORS::OPEN_FILE);
    }

    info->text_len = GetFileLength(INPUT_FILE);

    // Add 1 for NUL-terminator ---------------------v
    if (!(info->buf = (char* ) calloc(info->text_len + 1, sizeof(char))))
        return (int) (error->code = ERRORS::ALLOCATE_MEMORY);

    if (fread(info->buf, sizeof(char), info->text_len, fp) != info->text_len)
        return (int) (error->code = ERRORS::READ_FILE);

    for (int i = 0; i < info->text_len; i++)
    {
        if (info->buf[i] == '\n')
        {
            info->buf[i] = '\0';
            (info->line_amt)++;
        }
    }

    (info->line_amt)++;

    FillLineStruct(info, error);
    if (error->code != ERRORS::NONE)
        return (int) error->code;

    if (info->lines == NULL)
        return (int) (error->code = ERRORS::ALLOCATE_MEMORY);

    return (int) (error->code = ERRORS::NONE);
}

//-------------------------------------------------------------------------------------------

bool EraseFile(const char* FILE_NAME)
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

void PrintBuf(FILE* stream, const char* buf, const size_t buf_len)
{
    assert(buf);

    for (size_t i = 0; i < buf_len; i++)
    {
        int ch = buf[i];

        if (buf[i] == '\0')
            ch = '\n';

        fputc(ch, stream);
    }

}

//-------------------------------------------------------------------------------------------

bool PrintHeader(FILE* stream, const char* header)
{
    if (fprintf(stream, "%s\n\n", header) == 0)
        return false;

    return true;
}

//-------------------------------------------------------------------------------------------

bool PrintSeparator(FILE* stream)
{
    if (fprintf(stream, "------------------------------------------------------------------\n") == 0)
        return false;

    return true;
}

//-------------------------------------------------------------------------------------------

int PrintError(struct ErrorInfo* error)
{
    switch (error->code)
    {
        case (ERRORS::NONE):
            return (int) error->code;

        case (ERRORS::OPEN_FILE):
            PrintRedText(stderr, "OPEN FILE ERROR\n"
                                 "FAILED TO OPEN FILE \"%s\"\n", error->param);
            return (int) error->code;

        case (ERRORS::READ_FILE):
            PrintRedText(stderr, "READ FILE ERROR\n"
                                 "FAILED TO READ INFO FROM FILE \"%s\"\n", error->param);
            return (int) error->code;

        case (ERRORS::ALLOCATE_MEMORY):
            PrintRedText(stderr, "MEMORY ALLOCATE ERROR\n"
                                 "FAILED TO ALLOCATE MEMORY IN \"%s\"\n", error->param);
            return (int) error->code;

        case (ERRORS::PRINT_DATA):
            PrintRedText(stderr, "DATA PRINT ERROR\n"
                                 "FAILED TO PRINT DATA IN \"%s\"\n", error->param);
            return (int) error->code;

        default:
            PrintRedText(stderr, "UNKNOWN ERROR\n", "");
            return (int) ERRORS::UNKNOWN;
    }
}
