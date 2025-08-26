# Rubik's Cube Solver

## How to Use

1. Compile the program:

```bash
g++ main.cpp -o cube

```bash
./cube <scramble_string>

2. Input Format:
Enter the cube colors as a single string with no spaces,
all lowercase. Order the faces left to right, top to bottom,
starting with:
white, orange, green, red, blue, yellow.
For example:
```bash
./cube wogbry... (total 54 characters)
The program will output the solution sequence
