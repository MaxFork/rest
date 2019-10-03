
#include "mains.h"
#include "scl.h"
#include "string.h"

int main(int argc, char **argv)
{
    string_t *name;
    string_t *hello_world;
    int error = NO_ERROR;

    name = allocate_string("Amin", &error);
    if (error != NO_ERROR)
    {
        printf_line("error: %s", str_error(error));
        return 0;
    }

    hello_world = allocate_string("Hello World! And Welcome to this World!",
        &error);
    if (error != NO_ERROR)
    {
        printf_line("error: %s", str_error(error));
        return 0;
    }

    dump_string(name);
    dump_string(hello_world);

    // return respiler_main(argc, argv);
}
