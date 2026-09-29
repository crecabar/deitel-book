#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#include "exercise.h"

static const struct exercise exercises[] = {
    {
        .chapter = 6,
        .number = 38,
        .title = "String Reverse",
        .path = "./build/chapter_06/06_38_string_reverse",
    },
};

static int read_option(const char *prompt, int *value);

static int run_exercise(const struct exercise *exercise);

static void chapter_06_menu(void);

int main(void)
{
    int option;

    for (;;) {
        printf("\n");
        printf("Deitel C/C++ Exercises\n");
        printf("======================\n\n");
        printf("1. Chapter 6\n");
        printf("0. Exit\n\n");
        int result = read_option("Select an option: ", &option);

        if (result == -1) {
            return EXIT_SUCCESS;
        }

        if (result == 0) {
            printf("\nInvalid option.\n");
            continue;
        }

        switch (option) {
        case 0:
            return EXIT_SUCCESS;

        case 1:
            chapter_06_menu();
            break;

        default:
            printf("\nInvalid option.\n");
            break;
        }
    }
}

static int read_option(const char *prompt, int *value)
{
    char buffer[64];
    char *end;
    long result;

    printf("%s", prompt);

    if (fgets(buffer, sizeof buffer, stdin) == NULL) {
        return -1;
    }

    errno = 0;
    result = strtol(buffer, &end, 10);

    if (errno != 0 || end == buffer) {
        return 0;
    }

    while (*end == ' ' || *end == '\t') {
        ++end;
    }

    if (*end != '\n' && *end != '\0') {
        return 0;
    }

    if (result < INT_MIN || result > INT_MAX) {
        return 0;
    }

    *value = (int)result;

    return 1;
}

static int run_exercise(const struct exercise *exercise)
{
    pid_t pid;
    int status;

    pid = fork();

    if (pid == -1) {
        fprintf(stderr, "fork: %s\n", strerror(errno));
        return -1;
    }

    if (pid == 0) {
        execl(exercise->path, exercise->path, (char *)NULL);

        fprintf(stderr, "exec: %s\n", strerror(errno));
        _exit(EXIT_FAILURE);
    }

    while (waitpid(pid, &status, 0) == -1) {
        if (errno == EINTR) {
            continue;
        }
    
        fprintf(stderr, "waitpid: %s\n", strerror(errno));
        return -1;
    }

    if (WIFEXITED(status)) {
        return WEXITSTATUS(status);
    }

    if (WIFSIGNALED(status)) {
        fprintf(stderr,
                "Exercise terminated by signal %d.\n",
                WTERMSIG(status));
    }

    return -1;
}

static void chapter_06_menu(void)
{
    int option;

    for (;;) {
        printf("\n");
        printf("Chapter 6\n");
        printf("=========\n\n");
        printf("38. %s\n", exercises[0].title);
        printf("0. Back\n\n");
        int result = read_option("Select an exercise: ", &option);

        if (result == -1) {
            return;
        }

        if (result == 0) {
            printf("\nInvalid option.\n");
            continue;
        }

        switch (option) {
        case 0:
            return;

        case 38:
            printf("\nRunning %u.%u - %s\n\n",
                   exercises[0].chapter,
                   exercises[0].number,
                   exercises[0].title);

                   int status = run_exercise(&exercises[0]);

                   if (status > 0) {
                       fprintf(stderr,
                               "\nExercise exited with status %d.\n",
                               status);
                   } else if (status < 0) {
                       fprintf(stderr,
                               "\nExercise did not terminate normally.\n");
                   }
            break;

        default:
            printf("\nInvalid option.\n");
            break;
        }
    }
}

