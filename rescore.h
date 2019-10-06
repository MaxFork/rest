
#ifndef RESCORE_H
#define RESCORE_H 1

#include <stdio.h>

#include "restypes.h"

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
#define CH (ITER.buffer.pntr[ITER.index])
#define END (ITER.end)
#define INC_INDEX (buffer_lines_iterator_inc_index(&ITER))
#define START_INDEX (token->start_index)
#define END_INDEX (token->end_index)

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

    if (END)
    {
        SET_TOKEN_TYPE(TOKEN_TYPE_NULL);
        RETURN;
    }

    while (IS_SPACE)
    {
        INC_INDEX;
        if (END)
        {
            SET_TOKEN_TYPE(TOKEN_TYPE_NULL);
            RETURN;
        }
    }

    if (CH == '\n')
    {
        SET_START_INDEX();
        INC_INDEX;
        SET_END_INDEX();

        SET_TOKEN_TYPE(TOKEN_TYPE_NEWLINE);
        RETURN;
    }
    else if (IS_LOWER)
    {
        SET_START_INDEX();
        INC_INDEX;

    keyword_loop:
        if (END)
        {

#define CMP_STRING(string) \
    ((token->start_index.index - ITER.index) == STRLEN(string)) && \
    (memcmp(ITER.buffer.pntr, string, STRLEN(string)) == 0)

            if (CMP_STRING("goto"))
            {
                SET_END_INDEX();

                SET_TOKEN_TYPE(TOKEN_TYPE_GOTO);
                RETURN;
            }

#undef CMP_STRING

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
#undef INC_INDEX
#undef START_INDEX
#undef END_INDEX

}

#endif // RESCORE_H
