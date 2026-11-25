# Student Database (C)

A console-based student record management system written in C, using binary file handling.

![Main menu](menu.png)

## Features
- Add a student record
- Search a student by record number
- List all students
- Edit a student's details
- Delete a student record

## How it works
Each student is stored as a struct (first name, last name, class, roll number, phone number, grade) in a binary file called Student_database.dat. The program uses fopen, fwrite, fread, fseek and ftell to add, read, edit and delete records.

## How to run
This program uses conio.h, so it runs on Windows.

1. Install a C compiler such as MinGW (gcc).
2. Compile: gcc student_database.c -o student_database
3. Run: student_database

## What I learned
- Binary file handling in C
- Working with structs
- Input validation and error handling
- Safely deleting records using a temporary file

## License
MIT
