# CLRS Solving Systems of Linear Equations

This repository contains my implementation of a few algorithms described in 
"Introduction to Algorithms" (CLRS) specifically for Chapter 28, Matrix
Operations.

A few notes about the code layout: `main.cpp` is the driver that runs on general
inputs, and `tests.cpp` is a driver that runs some of the examples from the CLRS
book.

This project has Make targets to simplify the build process. Simply run `make`
to build the main project, and `make tests` to specifically build the test
executable.

The main driver takes in input via stdin in the described format below and
produces a solution (if non-singular).

Use input redirection to easily run the program: `./solve < input-0.txt`.

## Input Format

The input format is meant to capture the data in an equation Ax=b. We do this by
noting the dimension of A, and augmenting the matrix as [A|b].

The input format for the main driver is as follows:
Line 0: A comment line 
Line 1: n, the number of rows & columns of the Matrix (must not be over or under
determined)
Lines 2-(n+1): each line represents a row of the augmented matrix


See `input-0.txt` and `input-1.txt`.

## Code Notes

### AlmostEquals

Strict floating point comparisons are bound to fail. In order to accurately test
equality for matrices of floating point values, we employ Google Test's
"AlmostEquals.h", which compares under some threshold with support for edge
cases and different platforms.

`utils.h` defines a comparator to use AlmostEquals in STL algorithms.
