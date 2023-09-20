#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/stat.h>
#include <ctype.h>

#include "input_and_output.h"
#include "mylib/errors.h"
#include "mylib/colorlib.h"

static int FillLineStruct(struct Storage* info, struct ErrorInfo* error);
static int AllocateBuf(FILE* fp, char** buf, const off_t buf_len, struct ErrorInfo* error);
static int AllocateLines(struct LineInfo** lines, char* buf, const off_t text_len,
                         size_t* line_amt, struct ErrorInfo* error);

static int AllocateLines(struct LineInfo** lines, char* buf, const off_t text_len,
                         size_t* line_amt, struct ErrorInfo* error)
{
    *lines = (struct LineInfo* ) calloc(*line_amt, sizeof(struct LineInfo));

    if (*lines ==  NULL)
        return (int) (error->code = ERRORS::ALLOCATE_MEMORY);

    (*lines)[0].string = buf;

    for (int i = 0; i < text_len; i++)
    {
        if (buf[i] == '\n')
        {
            buf[i] = '\0';
            (*line_amt)++;
        }
    }

    (*line_amt)++;

    return (int) ERRORS::NONE;
}

//-------------------------------------------------------------------------------------------

static int AllocateBuf(FILE* fp, char** buf, const off_t buf_len, struct ErrorInfo* error)
{
    // Add 1 for NUL-terminator --v
    *buf = (char* ) calloc(buf_len + 1, sizeof(char));

    if (!*buf)
        return (int) (error->code = ERRORS::ALLOCATE_MEMORY);

    off_t symbols_read = fread(*buf, sizeof(char), buf_len, fp);

    if (symbols_read != buf_len)
        return (int) (error->code = ERRORS::READ_FILE);

    return (int) ERRORS::NONE;
}

//-------------------------------------------------------------------------------------------

static int FillLineStruct(struct Storage* info, struct ErrorInfo* error)
{
    assert(info);

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

bool PrintAllLines(FILE* stream, const struct LineInfo* lines,
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

void PrintOneLine(FILE* stream, const struct LineInfo* line, struct ErrorInfo* error)
{
    assert(line);

    for (int i = 0; (line->string)[i] != '\0' && i < line->len; i++)
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

int CreateTextStorage(struct Storage* info, struct ErrorInfo* error, const char* FILE_NAME)
{
    assert(info);

    FILE* fp = fopen(FILE_NAME, "rb");

    if (fp == NULL)
    {
        error->data = (char*) FILE_NAME;
        return (int) (error->code = ERRORS::OPEN_FILE);
    }

    off_t buf_size = GetFileLength(FILE_NAME);

    //===================== CREATING BUFFER

    AllocateBuf(fp, &info->buf, buf_size, error);

    if (error->code != ERRORS::NONE)
        return (int) error->code;

    //===================== END OF CREATING BUFFER

    //===================== CREATING LINES STRUCTURES

    AllocateLines(&info->lines, info->buf, buf_size, &info->line_amt, error);

    if (error->code != ERRORS::NONE)
    {
        info->line_amt = 0;
        return (int) error->code;
    }

    info->text_len = buf_size;

    FillLineStruct(info, error);

    if (error->code != ERRORS::NONE)
        return (int) error->code;

    //===================== END OF CREATING LINES STRUCTURES

    if (info->lines == NULL)
    {
        info->line_amt = 0;
        return (int) (error->code = ERRORS::ALLOCATE_MEMORY);
    }

    return (int) (error->code = ERRORS::NONE);
}

//-------------------------------------------------------------------------------------------

bool EraseFile(const char* FILE_NAME)
{
    FILE* fp = fopen(FILE_NAME, "wb");

    if (fp == NULL)
        return false;

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
