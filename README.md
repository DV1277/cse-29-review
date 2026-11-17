# CSE 29 review archive

Private study copy of saved coursework, collected November 17, 2026. Original code is preserved, not rewritten into reference solutions.

## Start here

- **Project-2/pwcrack.c**: password cracking, bit operations, strings, SHA-256. Submitted grade: 14/14.
- **Project-3/seash.c**: shell, processes, system calls, history, command parsing. Submitted grade: 95.95/100. This is the submitted version, including its remaining bugs.
- **Problem-Set-2/**: 16 submitted C files across six question groups.
- **Problem-Set-3/**: 19 submitted C files across four coding question groups. Question 5 is a GDB response question, not a code submission.
- **Lab-3/** through **Lab-7/**: debugging, shell tools, memory, Makefiles, structs, and OS-related lab work.
- **Project-1/** and **Problem-Set-1/** are included as earlier-topic review: binary, strings, and UTF-8.

## Folder inventory

| Folder | Code/build files |
| --- | ---: |
| Lab-3 | 8 |
| Lab-4 | 2 |
| Lab-5 | 9 |
| Lab-6 | 27 |
| Lab-7 | 8 |
| Project-1 | 1 |
| Project-2 | 1 |
| Project-3 | 1 |
| Problem-Set-1 | 20 |
| Problem-Set-2 | 16 |
| Problem-Set-3 | 19 |

Code/build files means `.c`, `.h`, `.sh`, or `Makefile`. Text fixtures and original credit files are separate from these counts.

## What the archive contains

Projects and problem sets come from saved submissions in Gradescope and PrairieLearn. Lab files come from Gradescope's submitted files, with any additional or different source in the ieng6 working copy placed under `ieng6-extra/`. Course-provided starter and support code is preserved alongside the student's changes, so inclusion does not imply every line was written from scratch by the student.

Source files and text fixtures are included. Compiled executables, object files, music files, and course automation metadata are omitted. Existing `CREDITS.txt` files are copied unchanged; nothing was submitted or resubmitted while making this archive.

`SOURCES.json` records source locations. `FILE-INVENTORY.json` gives file sizes and SHA-256 hashes. `SYNTAX-CHECK.json` records a syntax-only compiler check, not test-suite correctness. A successful syntax check does not prove the program has the right behavior.

Lab 6 includes a generated `million.c` stress-test file of about 83 MB. It is not a file to read line by line; the nearby generator script shows the idea. Compiling it may exhaust memory on a small machine.

## Building

Build unrelated exercises separately because many define their own `main` function. Use each directory's Makefile where present. OpenSSL exercises require the OpenSSL development headers and `-lcrypto`, for example:

```sh
cd Project-2
gcc pwcrack.c -o pwcrack -lcrypto
```

The course site is https://cse29.site . Its schedule labels Week 4 as System Calls, Week 5 as Structs and Malloc, Week 6 as OS Concepts, and Week 7 as Dynamic Memory Allocation. Earlier binary, UTF-8, shell, and pointer topics remain useful prerequisites.

## Verification result

88 of 89 C files passed a syntax-only compiler check. Four OpenSSL-dependent files were checked on ieng6. The generated Lab 6 `million.c` stress test exceeded compiler resources; its source is preserved unchanged. No behavioral correctness claim is made for these checks.
