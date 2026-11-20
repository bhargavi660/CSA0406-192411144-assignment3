#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    size_t page_size = argc > 1 ? strtoul(argv[1], NULL, 10) : 1024;
    if (page_size == 0) { fprintf(stderr, "page size must be positive\n"); return 1; }
    size_t frames[] = {2, 5, 1, 7};
    size_t allocated_pages = sizeof(frames) / sizeof(frames[0]);
    while (1) {
        printf("Enter logical address (-1 to exit): ");
        long address;
        if (scanf("%ld", &address) != 1) return 1;
        if (address < 0) return 0;
        size_t logical = (size_t)address;
        size_t page = logical / page_size, offset = logical % page_size;
        if (page >= allocated_pages) {
            printf("PAGE FAULT: address %zu (page %zu) beyond %zu allocated pages\n",
                   logical, page, allocated_pages);
        } else {
            printf("Logical %zu -> page %zu, offset %zu -> physical %zu\n",
                   logical, page, offset, frames[page] * page_size + offset);
        }
    }
}
