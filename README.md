# Deitel Book's Exercises

A collection of my solutions to the programming exercises from Deitel & Deitel's *C/C++ How to Program*.

Each exercise is implemented as an independent C program and can be compiled and executed on its own. The repository also includes an interactive launcher that automatically discovers the available chapters and exercises.

## Book Edition

The exercises in this repository follow the **second edition** of Deitel & Deitel's *C/C++ How to Program*.

Exercise and chapter numbers may differ from those in other editions of the book.

## Building

Build the launcher and all available exercises with:

```sh
make
```

The generated files are placed under `build/`.

Run the interactive launcher with:

```sh
./build/deitel
```

To remove all generated files:

```sh
make clean
```

## Repository Structure

```text
.
├── launcher/
│   ├── exercise.h
│   └── main.c
├── scripts/
│   └── generate_catalog.sh
├── src/
│   └── chapter_06/
│       └── 06_38_string_reverse.c
├── Makefile
└── README.md
```

Each exercise is a standalone program with its own `main()` function.

For example:

```sh
./build/chapter_06/06_38_string_reverse
```

runs exercise 6.38 directly without using the launcher.

## Adding an Exercise

Exercises are discovered automatically from the `src/` directory. No changes to the `Makefile` or launcher are required when adding a new exercise.

Files must follow this convention:

```text
src/chapter_CC/CC_NN_exercise_title.c
```

where:

- `CC` is the chapter number.
- `NN` is the exercise number.
- `exercise_title` is a lowercase `snake_case` description used to generate the title displayed by the launcher.

For example:

```text
src/chapter_06/06_38_string_reverse.c
```

is automatically interpreted as:

```text
Chapter:  6
Exercise: 38
Title:    String Reverse
```

After adding a source file, simply run:

```sh
make
```

The build system will automatically:

1. discover the new source file;
2. compile it as an independent executable;
3. regenerate the exercise catalog; and
4. make it available through the interactive launcher.

For example, adding:

```text
src/chapter_07/07_01_hello_world.c
```

and running `make` creates:

```text
build/chapter_07/07_01_hello_world
```

and makes Chapter 7 and exercise 7.1 available in the launcher.

## Compiler Settings

The exercises are currently compiled as C17 with:

```text
-std=c17 -Wall -Wextra -Wpedantic -Werror
```

Warnings are therefore treated as compilation errors.

## Launcher

The launcher is intentionally separate from the exercises. Exercises do not depend on it and remain ordinary standalone C programs.

On POSIX systems, the launcher executes each exercise in a child process using `fork()`, `exec()` and `waitpid()`. When the exercise terminates, control returns to the launcher.

## Requirements

The project requires:

- a C17-compatible C compiler;
- POSIX process APIs;
- POSIX-compatible shell utilities; and
- `make`.

It is developed and tested primarily on macOS and Linux.

## Disclaimer

This repository contains my own attempts to solve the exercises from Deitel & Deitel's *C/C++ How to Program*. It is intended for personal study and experimentation.
