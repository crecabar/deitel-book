#include <stdio.h>
#include <stdlib.h>

int
main(void)
{
    int option;

    for (;;) {
        printf("\n");
        printf("Deitel C/C++ Exercises\n");
        printf("======================\n\n");
        printf("1. Chapter 6\n");
        printf("0. Exit\n\n");
        printf("Select an option: ");

        if (scanf("%d", &option) != 1) {
            fprintf(stderr, "Invalid input.\n");
            return EXIT_FAILURE;
        }

        switch (option) {
        case 0:
            return EXIT_SUCCESS;

        case 1:
            printf("\nChapter 6 selected.\n");
            break;

        default:
            printf("\nInvalid option.\n");
            break;
        }
    }
}

