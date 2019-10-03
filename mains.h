
#ifndef MAINS_H
#define MAINS_H 1


#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>

#include "scl.h"

#include "restypes.h"
#include "rescore.h"

#define ALLOCATE_TYPE(TYPE) (TYPE *)malloc(sizeof(TYPE))

#define BUFFER_SIZE (1024 * 1024 * 16)          // 16 MB

#define PROGRAM_NAME "respiler"
#define USAGE "usage: %s [FILE]..."

int respiler_main(int argc, char **argv)
{
    const char *program_name;

    program_name = (argc != 0) ? argv[0] : PROGRAM_NAME;
    if (argc < 2)
    {
        printf(USAGE, program_name);
        return EXIT_NORMAL;
    }

    FILE *infile;
    int error = NO_ERROR;

    for (int i = 1; i < argc; i += 1)
    {
        infile = fopen(argv[i], "rb");
        if (!infile)
        {
            printf_error("can't open '%s': %s", argv[i], strerror(errno));
            return EXIT_ERROR;
        }

        analyzer_data_t data;

        initialize_analyzer_data(infile, &data, &error);
        if (error != NO_ERROR)
        {
            printf_error("while reading '%s': %s", argv[i], str_error(error));
            return EXIT_ERROR;
        }

        fclose(infile);
    }
    return EXIT_NORMAL;
}


#endif // MAINS_H
