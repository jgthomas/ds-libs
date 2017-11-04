#include <stdlib.h>
#include "hash_types.h"
#include "hash_functions.h"
#include "printing.h"
#include "comparison.h"


TypeData String = { .hash = hash_string,
                    .compare = equal_string,
                    .print = print_string,
                    .size = sizeof(char *)};



TypeData Integer = { .hash = hash_int,
                     .compare = equal_int,
                     .print = print_int,
                     .size = sizeof(int) };
