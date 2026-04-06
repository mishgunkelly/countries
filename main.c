#include <stdio.h>
#include "countries.h"






int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }
    int result = God(argv[1], argv[2]);
    return result;
}