#!/bin/bash

mkdir -p Books Music
for file in *.txt; do
    [ -f "$file" ] || continue
    mv -- "$file" Books/
done
for file in *.mp3; do
    [ -f "$file" ] || continue
    mv -- "$file" Music/
done
