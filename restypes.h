
#ifndef RESTYPES_H
#define RESTYPES_H 1

#include "restokens.h"

typedef struct
{
    token_type type;
    buffer_lines_index_t start_index;
    buffer_lines_index_t end_index;
} token_t;

typedef struct
{
    buffer_lines_iterator_t iterator;
} analyzer_data_t;

#endif // RESTYPES_H
