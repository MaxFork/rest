
#include "scl.h"

int main(int argc, char **argv)
{
    const char *name = "code.rest";
    FILE *file;

    if (check_fopen(&file, name, "rb"))
        return EXIT_ERROR;

    fclose(file);
    return EXIT_NORMAL;
}
