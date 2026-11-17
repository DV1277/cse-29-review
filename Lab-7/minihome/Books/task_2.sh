#!/bin/bash

threshold=$1
mkdir -p Novels Short_Stories

for file in *.txt; do
    [ -f "$file" ] || continue
    num_words=$(wc -w < "$file")

    if [ "$num_words" -gt "$threshold" ]; then
        mv -- "$file" Novels/
    else
        mv -- "$file" Short_Stories/
    fi
done
