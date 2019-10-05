
#ifndef CTYPES_H
#define CTYPES_H 1

/*
*       C Types Library
*/

#include <stdbool.h>
#include <stdint.h>

typedef uint8_t reference_count_t;

typedef struct
{
    char *pntr;
    size_t size;
} buffer_t;

typedef struct
{
    size_t start;
    size_t end;
} buffer_index_t;

typedef struct
{
    FILE *file;
    buffer_t buffer;
} file_buffer_t;

typedef struct
{
    buffer_index_t *pntr;
    size_t total;
} lines_t;

typedef struct
{
    buffer_t buffer;
    lines_t lines;
} buffer_lines_t;

typedef struct
{
    FILE *file;
    buffer_lines_t buffer_lines;
} file_buffer_lines_t;

typedef struct
{
    size_t lnum;
    size_t index;
} buffer_lines_index_t;

typedef struct
{
    buffer_lines_t;
    buffer_lines_index_t;
    bool end;
} buffer_lines_iterator_t;

// linked_buffer

typedef struct linked_buffer
{
    buffer_t;
    reference_count_t rc;
    struct linked_buffer *next;
} linked_buffer_t;

typedef struct
{
    linked_buffer_t *buffer;
    size_t index;
} linked_buffer_index_t;

typedef struct
{
    linked_buffer_index_t start;
    linked_buffer_index_t end;
} linked_buffer_line_t;

typedef struct
{
    char *inst_pntr;
    size_t inst_size;
} pattern_t;


#define BUFFER_INDEX_LEN(line) ((line).end - (line).start)

#define LINES_GET_START_INDEX(lines, lnum) ((lines).pntr[lnum].start)
#define LINES_GET_END_INDEX(lines, lnum) ((lines).pntr[lnum].end)

#define BUFFER_LINES_GET_PNTR(buffer_lines, lnum) \
    ((buffer_lines).buffer.pntr + (buffer_lines).lines.pntr[lnum].start)
#define BUFFER_LINES_GET_LEN(buffer_lines, lnum) \
    BUFFER_INDEX_LEN((buffer_lines).lines.pntr[lnum])
#define BUFFER_LINES_GET_CHAR(buffer_lines, lnum, index) \
    (BUFFER_LINES_GET_PNTR(buffer_lines, lnum)[index])

#define BUFFER_LINES_ITERATOR_GET_INDEX(iterator) \
    ((iterator).buffer.pntr[(iterator).index])

#endif // CTYPES_H
