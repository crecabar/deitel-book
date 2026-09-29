#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#include "exercise.h"

#define EXERCISE_COUNT (sizeof exercises / sizeof exercises[0])

static const struct exercise exercises[] = {
    #include "exercises.inc"
};

static int read_option(const char *prompt, int *value);

static int run_exercise(const struct exercise *exercise);

static void chapter_menu(unsigned int chapter);

static void print_chapters(void);

static int chapter_exists(unsigned int chapter);

int main(void)
{
    int option;

    for (;;) {
        printf("\n");
        printf("Deitel C/C++ Exercises\n");
        printf("======================\n\n");

        print_chapters();

        printf("0. Exit\n\n");

        int result = read_option("Select a chapter: ", &option);

        if (result == -1) {
            putchar('\n');
            return EXIT_SUCCESS;
        }

        if (result == 0) {
            printf("\nInvalid option.\n");
            continue;
        }

        if (option == 0) {
            return EXIT_SUCCESS;
        }

        if (option < 0 ||
            !chapter_exists((unsigned int)option)) {
            printf("\nInvalid option.\n");
            continue;
        }

        chapter_menu((unsigned int)option);
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

    if (strchr(buffer, '\n') == NULL) {
        int ch;

        while ((ch = getchar()) != '\n' && ch != EOF) {
            ;
        }

        return 0;
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

static void chapter_menu(unsigned int chapter)
{
    int option;

    for (;;) {
        printf("\nChapter %u\n", chapter);
        printf("=========\n\n");

        for (size_t i = 0; i < EXERCISE_COUNT; ++i) {
            if (exercises[i].chapter == chapter) {
                printf("%u. %s\n",
                       exercises[i].number,
                       exercises[i].title);
            }
        }

        printf("0. Back\n\n");

        int result = read_option("Select an exercise: ", &option);

        if (result == -1) {
            putchar('\n');
            return;
        }

        if (result == 0) {
            printf("\nInvalid option.\n");
            continue;
        }

        if (option == 0) {
            return;
        }

        if (option < 0) {
            printf("\nInvalid option.\n");
            continue;
        }

        const struct exercise *selected = NULL;

        for (size_t i = 0; i < EXERCISE_COUNT; ++i) {
            if (exercises[i].chapter == chapter &&
                exercises[i].number == (unsigned int)option) {
                selected = &exercises[i];
                break;
            }
        }

        if (selected == NULL) {
            printf("\nInvalid option.\n");
            continue;
        }

        printf("\nRunning %u.%u - %s\n\n",
               selected->chapter,
               selected->number,
               selected->title);

        int status = run_exercise(selected);

        if (status > 0) {
            fprintf(stderr,
                    "\nExercise exited with status %d.\n",
                    status);
        } else if (status < 0) {
            fprintf(stderr,
                    "\nExercise did not terminate normally.\n");
        }
    }
}

static void print_chapters(void)
{
    unsigned int previous_chapter = 0;

    for (size_t i = 0; i < EXERCISE_COUNT; ++i) {
        if (exercises[i].chapter != previous_chapter) {
            printf("%u. Chapter %u\n",
                   exercises[i].chapter,
                   exercises[i].chapter);

            previous_chapter = exercises[i].chapter;
        }
    }
}

static int chapter_exists(unsigned int chapter)
{
    for (size_t i = 0; i < EXERCISE_COUNT; ++i) {
        if (exercises[i].chapter == chapter) {
            return 1;
        }
    }

    return 0;
}

