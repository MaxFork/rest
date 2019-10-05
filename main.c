
#include "scl.h"

int main(int argc, char **argv)
{
    const char *name = "code.rest";
    FILE *file;
    int error;
    buffer_lines_t buffer_lines;

    read_lines_name(name, &file, &buffer_lines, &error);
    if (error != NO_ERROR)
    {
        printf_error("%s", str_error(error));
        return EXIT_ERROR;
    }

    for (size_t lnum = 0; lnum < buffer_lines.lines.total; lnum += 1)
    {
        size_t index = buffer_lines_find_chr_not(&buffer_lines, lnum, " \t");
        if (index != BUFFER_LINES_GET_LEN(buffer_lines, lnum))
        {
            if (BUFFER_LINES_GET_CHAR(buffer_lines, lnum, index) == '#')
            {
                continue;
            }
        }
        printf(SIZE_M ": ", lnum + 1);
        buffer_lines_write_line(&buffer_lines, lnum, stdout);
    }

    fclose(file);
    return EXIT_NORMAL;
}
