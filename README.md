# markargs

The compiler is ongoing implementation of a programming language designed for calculating results of long numerical expressions.

<hr>

## Problem definition:

Given a bunch of mathematical expressions, find out which are constexpr, e.g. which names can be computed without user input, which ones require user input, and which ones can be computed if others are present. At the end program should ask for user input with names of the variables provided, and output all of the variables with their values after computations.

## Example:

a = 12
c = a + b + 1
In the example above, value of a is constexpr computable, value of b requires user input and c will be computable when others will be present.

## Language rules:

Only + - = operators are allowed

 - No consecutive numbers or variable names or any combination thereof <- implemented in tokenizer

 - No consecutive operators <- implemented in tokenizer

 - No leading operator (any of them) <- implemented in analyze

 - No number on left side of the = <- implemented in analyze

 - Only 1 = per expression <- implemented in analyze

 - variable names with no leading numbers are allowed <- implemented in analyze