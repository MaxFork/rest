
#include <ctype.h>

#include "scl.h"
#include "rescore.h"

int main(int argc, char **argv)
{
    const char *name = "code.rest";
    FILE *file;

    buffer_lines_t buffer_lines;
    int error = NO_ERROR;

    if (check_fopen(&file, name, "rb"))
        return EXIT_ERROR;

    read_lines(file, &buffer_lines, &error);
    if (error)
    {
        print_error_msg(error);
        return EXIT_ERROR;
    }

    buffer_index_t view;

    for (size_t lnum = 0; lnum < buffer_lines.lines.total; lnum += 1)
    {
        lstrip_chr(buffer_lines.buffer.pntr, &(view.start), &(view.end), );
        view = buffer_lines.lines.pntr[lnum];
        view.start = find_chr_not_index(buffer_lines.buffer.pntr, view.start,
            view.end, " \t");
    }

    fclose(file);
    return EXIT_NORMAL;
}
