
#ifndef SCL_H
#define SCL_H 1

/*
*       Simple C Library
*/

#ifdef COMPILE_SCL
#define SCL_DLL_EXPORT __declspec(dllexport)
#else
#define SCL_DLL_EXPORT __declspec(dllimport)
#endif

#include <stdbool.h>

#include "ctypes.h"

#if SIZE_MAX == ULLONG_MAX
#define SIZE_M "%I64u"
#elif SIZE_MAX == ULONG_MAX
#define SIZE_M "%I32u"
#else
#error unknown SIZE_MAX
#endif

#define EXIT_ERROR 1
#define EXIT_ARGUMENT_ERROR 2
#define EXIT_NORMAL 0

#define NO_ERROR 0
#define ERROR_NO_MEMORY 1
#define ERROR_FSEEK 2
#define ERROR_FTELL 3
#define ERROR_IO 4
#define ERROR_ZERO_FILE_SIZE 5
#define ERROR_INT_OVERFLOW 6
#define ERROR_FLOAT_OVERFLOW 7
#define ERROR_BAD_ARGUMENTS 8
#define ERROR_UNDEFINED_BEHAVIOR 0xFF

#define STRLEN(string) (sizeof(string) - 1)

#define ALLOCATE_TYPE(TYPE) (TYPE *)malloc(sizeof(TYPE))

#define ERROR_CASE(NAME) \
    case NAME: \
        return #NAME;

static inline
char *str_error(int error)
{
    switch (error)
    {
        ERROR_CASE(NO_ERROR)
        ERROR_CASE(ERROR_NO_MEMORY)
        ERROR_CASE(ERROR_FSEEK)
        ERROR_CASE(ERROR_FTELL)
        ERROR_CASE(ERROR_IO)
        ERROR_CASE(ERROR_ZERO_FILE_SIZE)
        ERROR_CASE(ERROR_INT_OVERFLOW)
        ERROR_CASE(ERROR_FLOAT_OVERFLOW)
        ERROR_CASE(ERROR_BAD_ARGUMENTS)
        ERROR_CASE(ERROR_UNDEFINED_BEHAVIOR)
    default:
        return "unknown error";
    }
}

#undef CASE

#define print_error(fmt) fprintf(stderr, "error: " fmt "\n")
#define printf_error(fmt, ...) fprintf(stderr, "error: " fmt "\n", __VA_ARGS__)

#define print_line(fmt)                 fprintf(stdout, fmt "\n")
#define printf_line(fmt, ...)           fprintf(stdout, fmt "\n", __VA_ARGS__)

#define fprint_line(file, fmt)          fprintf(file, fmt "\n")
#define fprintf_line(file, fmt, ...)    fprintf(file, fmt "\n", __VA_ARGS__)

long get_file_size(FILE *file, int *error)
{
    long file_size;
    if (fseek(file, 0, SEEK_END) == -1)
    {
        *error = ERROR_FSEEK;
        return 0;
    }

    file_size = ftell(file);
    if (file_size == -1)
    {
        *error = ERROR_FTELL;
        return 0;
    }

    if (fseek(file, 0, SEEK_SET) == -1)
    {
        *error = ERROR_FSEEK;
        return 0;
    }

    return file_size;
}

static inline
void read_file(FILE *file, buffer_t *buffer, int *error)
{
    long file_size;
    size_t read_number;

    file_size = get_file_size(file, error);
    if ((*error) != NO_ERROR)
    {
        return;
    }

    if (file_size == 0)
    {
        *error = ERROR_ZERO_FILE_SIZE;
        return;
    }

    #if LONG_MAX > SIZE_MAX
        #error LONG_MAX is greater than SIZE_MAX.
    #endif

    buffer->pntr = (char *)malloc(file_size);
    if (!(buffer->pntr))
    {
        *error = ERROR_NO_MEMORY;
        return;
    }
    buffer->size = file_size;

    read_number = fread(buffer->pntr, 1, file_size, file);
    if (read_number != (size_t)file_size)
    {
        *error = ERROR_IO;
        free(buffer->pntr);

        *buffer = (buffer_t) {.pntr = NULL, .size = 0};

        return;
    }
}

static inline
void split_lines(buffer_t *buffer, lines_t *lines, int *error)
{
    size_t index;
    size_t total;
    size_t lnum;
    size_t lines_size;

#define CH (buffer->pntr[index])
#define END (index == (buffer->size))

    index = 0;
    total = 0;

    while (1)
    {
        if (CH == '\r')
        {
            total += 1;

            index += 1;
            if (END)
                break;

            if (CH == '\n')
            {
                index += 1;
                if (END)
                    break;
            }
        }
        else if (CH == '\n')
        {
            total += 1;

            index += 1;
            if (END)
                break;
        }
        else
        {
            index += 1;
            if (END)
            {
                total += 1;
                break;
            }
        }
    }

    if (__builtin_mul_overflow(total, sizeof(line_t), &lines_size))
    {
        *error = ERROR_INT_OVERFLOW;
        return;
    }

    lines->pntr = (line_t *)malloc(lines_size);
    if (lines == NULL)
    {
        *error = ERROR_NO_MEMORY;
        return;
    }
    lines->total = total;

#define LINE (lines->pntr[lnum])

    index = 0;
    lnum = 0;

loop:
    LINE.start = index;

    while (1)
    {
        if (CH == '\n')
        {
            index += 1;
            LINE.end = index;

            if (END)
                break;

            lnum += 1;
            goto loop;
        }
        else if (CH == '\r')
        {
            CH = '\n';
            index += 1;
            LINE.end = index;

            if (END)
                break;

            if (CH == '\n')
            {
                index += 1;
                if (END)
                    break;
            }

            lnum += 1;
            goto loop;
        }
        else
        {
            index += 1;
            if (END)
            {
                LINE.end = index;
                break;
            }
        }
    }

    #undef CH
    #undef END
    #undef LINE
}

static inline
void read_lines(FILE *file, buffer_lines_t *buffer_lines, int *error)
{
    read_file(file, &(buffer_lines->buffer), error);
    if ((*error) != NO_ERROR)
    {
        return;
    }

    split_lines(&(buffer_lines->buffer), &(buffer_lines->lines), error);
    if ((*error) != NO_ERROR)
    {
        free(buffer_lines->buffer.pntr);
        buffer_lines->buffer = (buffer_t) {.pntr = NULL, .size = 0};
    }
}

static inline
void initialize_buffer_lines_iterator(FILE *file,
    buffer_lines_iterator_t *iterator, int *error)
{
    read_lines(file, &((buffer_lines_t) {.buffer = iterator->buffer,
        .lines = iterator->lines}), error);
    if ((*error) != NO_ERROR)
    {
        return;
    }
    iterator->lnum = 0;
    iterator->index = iterator->lines.pntr[0].start;
    iterator->end = false;
}

static inline
void buffer_lines_iterator_inc_index(buffer_lines_iterator_t *iterator)
{
    iterator->index += 1;
    if (iterator->index == iterator->lines.pntr[iterator->lnum].end)
    {
        iterator->lnum += 1;
        if (iterator->lnum == iterator->lines.total)
        {
            iterator->lnum -= 1;
            iterator->end = true;
            return;
        }
        iterator->index = iterator->lines.pntr[iterator->lnum].start;
    }
}

static inline
bool buffer_lines_iterator_next_index(buffer_lines_iterator_t *iterator)
{
    if (iterator->end)
        return true;
    buffer_lines_iterator_next_index(iterator);
    return iterator->end;
}

#define LOWERCASE "abcdefghijklmnopqrstuvwxyz"
#define UPPERCASE "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
#define LETTERS (LOWERCASE UPPERCASE)
#define DIGITS "0123456789"

static inline
int buffer_compare(buffer_t *buffer, size_t offset, size_t length,
    const char *string)
{
    return strncmp(buffer + offset, string, length);
}

static inline
bool chr_in(char ch, const char *string)
{
    while (*string)
    {
        if (ch == (*string))
        {
            return true;
        }
        string++;
    }
    return false;
}

static inline
bool find_chr_test(char *pntr, size_t length, bool (*test) (char ch))
{
    size_t index = 0;
    while (index < length)
    {
        if (test(pntr[index]))
        {
            return index;
        }
        index += 1;
    }
    return length;
}

static inline
bool rfind_chr_test(char *pntr, size_t length, bool (*test) (char ch))
{
    size_t index = length;
    while (index > 0)
    {
        index -= 1;
        if (test(pntr[index]))
        {
            return index;
        }
    }
    return length;
}

static inline
bool find_chr(char *pntr, size_t length, const char *string)
{
    size_t index = 0;
    while (index < length)
    {
        if (chr_in(pntr[index], string))
        {
            return index;
        }
        index += 1;
    }
    return length;
}

static inline
bool rfind_chr(char *pntr, size_t length, const char *string)
{
    size_t index = length;
    while (index > 0)
    {
        index -= 1;
        if (chr_in(pntr[index], string))
        {
            return index;
        }
    }
    return length;
}

static inline
bool find_chr_not(char *pntr, size_t length, const char *string)
{
    size_t index = 0;
    while (index < length)
    {
        if (!chr_in(pntr[index], string))
        {
            return index;
        }
        index += 1;
    }
    return length;
}

static inline
bool rfind_chr_not(char *pntr, size_t length, const char *string)
{
    size_t index = length;
    while (index > 0)
    {
        index -= 1;
        if (!chr_in(pntr[index], string))
        {
            return index;
        }
    }
    return length;
}

#undef SCL_DLL_EXPORT

#endif // SCL_H
