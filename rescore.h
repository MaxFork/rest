
#ifndef RESCORE_H
#define RESCORE_H 1

#include <stdio.h>

#define SIMPLE_ANALYZER 1

static inline
void initialize_analyzer_data(FILE *file, analyzer_data_t *data, int *error)
{
    initialize_buffer_lines_iterator(file, &(data->iterator), error);
}

static inline
void analyze_data(analyzer_data_t *data, token_t *token, int *error)
{

#define ITER (data->iterator)
#define CH (BUFFER_LINES_ITERATOR_GET_INDEX(ITER))
#define END (ITER.end)
#define NEXT_INDEX (buffer_lines_iterator_next_index(&ITER))

#define SET_TOKEN_TYPE(TYPE) token->type = (TYPE)
#define SET_START_INDEX() token->start_index = \
    (buffer_lines_index_t) {.lnum = ITER.lnum, .index = ITER.index}
#define SET_END_INDEX() token->end_index = \
    (buffer_lines_index_t) {.lnum = ITER.lnum, .index = ITER.index}
#define SET_ERROR_FLAG(VALUE) ((*error) = VALUE)
#define RETURN return

#define IS_SPACE ((CH == ' ') || (CH == '\t'))
#define IS_LOWER ((CH >= 'a') && (CH <= 'z'))
#define IS_UPPER ((CH >= 'A') && (CH <= 'Z'))
#define IS_DIGIT ((CH >= '0') && (CH <= '9'))

#ifdef SIMPLE_ANALYZER

#include "resfig.h"

    if (END)
    {
        SET_TOKEN_TYPE(TOKEN_TYPE_NULL);
        RETURN;
    }

    while (IS_SPACE)
    {
        if (NEXT_INDEX)
        {
            SET_TOKEN_TYPE(TOKEN_TYPE_NULL);
            RETURN;
        }
    }

    if (CH == '\n')
    {
        SET_START_INDEX();
        NEXT_INDEX;
        SET_END_INDEX();
        SET_TOKEN_TYPE(TOKEN_TYPE_NEWLINE);
        RETURN;
    }
    else if (IS_LOWER)
    {
        SET_START_INDEX();

    keyword_loop:
        if (NEXT_INDEX)
        {
            
        }

        if (IS_LOWER)
            goto keyword_loop;
        else if (IS_UPPER || IS_DIGIT || (CH == '_'))
        {

        }
        else
        {

        }
    }
    else
    {
        SET_START_INDEX();
        SET_ERROR_FLAG(ERROR_BAD_ARGUMENTS);
        RETURN;
    }

#else
#include "analyzer.h"
#endif

#undef IS_SPACE
#undef IS_LOWER
#undef IS_UPPER
#undef IS_DIGIT

#undef SET_TOKEN_TYPE
#undef SET_START_INDEX
#undef SET_END_INDEX
#undef SET_ERROR_FLAG
#undef RETURN

#undef ITER
#undef CH
#undef END

}

#endif // RESCORE_H
