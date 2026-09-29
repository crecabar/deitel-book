#!/bin/sh

set -eu

for source in "$@"; do
    filename=$(basename "$source" .c)
    directory=$(dirname "$source")
    chapter_dir=$(basename "$directory")

    chapter=${chapter_dir#chapter_}

    number=${filename#*_}
    number=${number%%_*}

    chapter=$(printf '%s\n' "$chapter" | sed 's/^0*//')
    number=$(printf '%s\n' "$number" | sed 's/^0*//')

    [ -n "$chapter" ] || chapter=0
    [ -n "$number" ] || number=0

    name=${filename#*_*_}

    title=$(printf '%s\n' "$name" |
        tr '_' ' ' |
        awk '{
            for (i = 1; i <= NF; ++i) {
                $i = toupper(substr($i, 1, 1)) substr($i, 2)
            }
            print
        }')

    printf '%s\n' "    {"
    printf '%s\n' "        .chapter = $((10#$chapter)),"
    printf '%s\n' "        .number = $((10#$number)),"
    printf '%s\n' "        .title = \"$title\","
    printf '%s\n' "        .path = \"./build/$chapter_dir/$filename\","
    printf '%s\n' "    },"
done
