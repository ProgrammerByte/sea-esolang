# Welcome to the Sea Esoteric Programming Language
Run ASCII art of the sea as code. This interpreter was written entirely in vanilla C, see?

To use this interpreter run `make` in the root directory, then run `./sea <path_to_file>`

The file extension used throughout the examples is `.sea`, although there is no restriction on this.

## Table of Contents
  * [Section 1 - Static Memory Overview](#section-1---static-memory-overview)
    + [1.1 - The Surface and Floating Point Types](#11---the-surface-and-floating-point-types)
    + [1.2 - The Static Memory Model](#12---the-static-memory-model)
  * [Section 2 - Chevron Operators](#section-2---chevron-operators)
    + [2.1 - Forwards Operations Detection](#21---forwards-operations-detection)
    + [2.2 - Forwards Mathematical Operators](#22---forwards-mathematical-operators)
      - [Forwards Subtraction Example](#forwards-subtraction-example)
      - [Forwards Addition Example](#forwards-addition-example)
      - [Forwards Multiplication Example](#forwards-multiplication-example)
      - [Forwards Division Example](#forwards-division-example)
    + [2.3 - Assignment](#23---assignment)
    + [2.4 - Branching By Label](#24---branching-by-label)
    + [2.5 - Branch By Column](#25---branch-by-column)
    + [2.6 - Backwards Mathematical Operators](#26---backwards-mathematical-operators)
      - [Backwards Subtraction Example](#backwards-subtraction-example)
      - [Backwards Division Example](#backwards-division-example)
    + [2.7 - Operator Composition](#27---operator-composition)
  * [Section 3 - Input and Output](#section-3---input-and-output)
    + [3.1 The Fisherman Operator (output)](#31-the-fisherman-operator--output)
    + [3.2 - Writing a Hello World Program](#32---writing-a-hello-world-program)
    + [3.3 - The Diver Operator (read character from terminal)](#33---the-diver-operator--read-character-from-terminal)
    + [3.4 - Taking a Number as an Input](#34---taking-a-number-as-an-input)
  * [Section 4 - Advanced Memory via Scoping](#section-4---advanced-memory-via-scoping)
    + [4.1 - Changing the Scope](#41---changing-the-scope)
    + [4.2 - Scope Locality](#42---scope-locality)
    + [4.3 - FizzBuzz](#43---fizzbuzz)

## Section 1 - Static Memory Overview
In this section we will cover the basic typing and static memory model of Sea.

### 1.1 - The Surface and Floating Point Types
The surface of the sea is defined by the following characters:
- `-` defines the surface of the sea
- `,` additionally defines a character literal (also known as floating point characters) which behaves the same as integers for the operations
- `.` additionally defines a non-negative (integer or decimal) floating point number
There are also other characters which can be used for the surface as we will see later, however this is used as part of larger patterns (see input and output).

> **_NOTE:_** The sea level must be defined in the first column of the program, and must remain at the same height throughout the entire program. The only time when this is not needed is when the sea bed is above the sea level to form land which we will see later.

Additionally, we use `_` to define (flat) seabed.

The following is valid sea code which contains the literals `Q`, `35`, `30.0`, `12.64`, `0`, ` ` (space character):

```
   33 1
 Q 50 2
-,-..-.-.,
    0 6   
      4   
__________
```
It's important to note that strings are not supported, and `35` is an integer, whereas `30.0` is a decimal. This will be important when using mathematical operators.
<br>
<br>
<br>

### 1.2 - The Static Memory Model
Now that we have types, we now need to consider how memory works.

In Sea, each row in the sea between the surface and the sea bed acts as a register which can hold one value of any type, which we can access with an uppercase `X`. These values can be read or written to at any time and uses a simple type-inferencing system.

Additionally values must be defined before they are used otherwise you will get an error.

So looking back at our prior example we can modify it to:
```
   33 1
 Q 50 2
-,-..-.-.,
    0 6  X 
      4   
__________
```
Which adds a reference to the top-most row (although it's not currently doing anything interesting).
<br>
<br>
<br>

## Section 2 - Chevron Operators
Many operators in Sea are detected by either left (`<`) or right (`>`) chevrons (aka fish) which define backwards or forwards operations respectively. This section will explore these operations.

### 2.1 - Forwards Operations Detection
Sea code is read from top to bottom and left to right (like normal programming languages but flipped diagonally).

Once a `>` is detected all forward operators are pattern matched based off of the top and left-most `>` in the operator. The precedence for this detection is `+` > `-`, `*`, `/` i.e. addition is checked, then subtraction, etc. (to ensure we don't detect e.g. both addition and subtraction at the same time).

Once a match is established, then a top to bottom and left-to-right sweep (following prior flow) is performed starting from the left-most column in the operator, and the top row. This sweep is done to find values which can either be floating literals or memory locations.

Suppose we find 3 values, with the first two being values `a`, `b`, and the third being a memory address `c` under an operator `op`. The interpreter will then perform `c = a op b`.
<br>
<br>
<br>

### 2.2 - Forwards Mathematical Operators

Here are examples for all of the forwards mathematical operations, defined by a formation of `>`'s which all behave in the same manner aside from the operation they perform.

It's important to note that I could have just used `X` instead of `X0` and `X1`, however it's only here for code clarity.

Also the following code snippets assume that X0 has been defined at an earlier point in the program, otherwise the program will crash when trying to execute the operation.

#### Forwards Subtraction Example:
```  
 2      
 1     
-.---------
 >>> X0  
         X1
___________
```

which will compute `X1 = 21 - X0`.
<br>
<br>

#### Forwards Addition Example:
```  
 2      
 1     
-.---------
  >  X0  
 >>>     X1
  >
___________
```
which will compute `X1 = 21 + X0`.
<br>
<br>

#### Forwards Multiplication Example:
```  
 2      
 1     
-.---------
 > >  X0  
  >      X1
 > >
___________
```
which will compute `X1 = 21 * X0`.
<br>
<br>

#### Forwards Division Example:
```  
 2      
 1     
-.---------
   >  X0  
  >      X1
 > 
___________
```
which will compute `X1 = 21 / X0`.

If both of the operands are integers then integer division will be performed, however if one or both of the operands are decimals, then floating point division will be used.
<br>
<br>
<br>

### 2.3 - Assignment

There is no assignemnt operator in Sea, so you will need to substitute it with arithmetic.

Suppose I wanted to load the character 'Z' into a row, then I could do:

```
 Z
-,.-
>>>X
____
```
which performs `X = 'Z' - 0`.
<br>
<br>
<br>

### 2.4 - Branching By Label

The branch forward operator is defined by `->` and jumps to the closest column to the right of the operator with the specified label (written to the right of the operator, separated by a space). Labels are written under the sea bed and do not contain any spaces. Additionally, a branch only happens if the value held at that memory location is less than or equal to zero. Here is a simple example to demonstrate this:

```
-..------------
  X0 -> LTZ
>>>
_______________
            L
            T
            Z
```
In the above example, `X0` is set to zero, and a branch to `LTZ` occurs as `X0 <= 0` is satisfied.

There is also a corresponding branch back operator which is defined by `<-`, and does the exact same thing but in the opposite direction.

For example, the following will get stuck in an infinite loop:
```
-..------------
  X0 <- LTZ
>>>
_______________
L             
T             
Z             
```
<br>
<br>
<br>

### 2.5 - Branch By Column

Branching forwards by column (`~>`) happens unconditionally, however the branch destination is the column number (zero-indexed) stored in the corresponding memory location.

In the following code an unconditional branch to column 10 occurs:

```
 1
 0
-..------------
  X0 ~>   D
>>>
_______________    
```
The D denotes branch destination for illustrative purposes only.

If you use the branch forward by column operator, then you cannot branch backwards otherwise the interpreter will crash, for example:
```
-..------------
D X0 ~>   
>>>
_______________    
```
If you want to branch backwards by column then you should use the `<~` operator instead i.e. for the above example we should instead use:
```
-..------------
D X0 <~   
>>>
_______________    
```
<br>
<br>

### 2.6 - Backwards Mathematical Operators

Backwards mathematical operators behave in the same way as their forwards counterparts, however are defined by `<`'s, and read values from right to left instead from left to right.

#### Backwards Subtraction Example:
```
 2   
 1 
-.-----
 X0 <<<
     X1
_______
```

which will compute `X0 = X1 - 21`.
<br>

## Backwards Division Example

```
 2   
 1 
-.-----
 X0  <
    <X1
   <
_______
```

which will compute `X0 = X1 / 21`.
<br>
Backwards addition, and multiplication also exist and follow the same pattern as that set out above.
<br>
<br>
<br>

### 2.7 - Operator Composition

Because of how all operators are based on pattern matching, it's entirely valid to make operators overlap such that the overall shape can still be found.

For example, if I just had
```
>>>
>>>
>>>
```
Then I will detect a subtraction on rows 0 and 2, and an addition on row 1.

This can also be used to save space for example consider the following code snippet:

```
   1
---.-
X XX
X>
>>>>
X>
_____
```
Keeping our naming convention as `X0`, `X1`, `X2`, and `X3` for the memory locations from top to bottom, we start by computing `X3 = X1 + X2`, then `X1 = X1 - 1`.
<br>
<br>
<br>

## Section 3 - Input and Output

In this section we set out how to perform basic input and output, and build programs with some level of interactivity.

### 3.1 The Fisherman Operator (output)

The fisherman operator is defined by a stick figure and a fishing rod. The stick figure is defined by
```
O
L
A
```
Where `A` sits on the surface, and additionally the fishing rod is defined by:
```
O _
L/ \
A   |
    |
    :
    |
    0
```
Where the `0` sits on a row to be output as a number.

Here is a complete example for outputting the number 12.4:

```
 1     O _ 
 2     L/ \
-..----A---|
 4         |
>>>  X     0
____________
```

Additionally, a `o` can be used to output the value as a character, e.g. the following will output the letter `a`:
```
       O _ 
 a     L/ \
-,.----A---|
           |
>>>  X     o
____________
```
<br>
<br>

### 3.2 - Writing a Hello World Program

Now that we can output characters, we can chain multiple outputs together to create a "Hello World" program as follows:
```
 O _  O _  O _  O _  O _  O _  O _  O _  O _  O _  O _  O _
 L/H\ L/e\ L/l\ L/l\ L/o\ L/ \ L/W\ L/o\ L/r\ L/l\ L/d\ L/!\
-A-,.|A-,.|A-,.|A-,.|A-,.|A-,.|A-,.|A-,.|A-,.|A-,.|A-,.|A-,.|
    Xo   Xo   Xo   Xo   Xo   Xo   Xo   Xo   Xo   Xo   Xo   Xo
>>>  >>>  >>>  >>>  >>>  >>>  >>>  >>>  >>>  >>>  >>>  >>>
_____________________________________________________________
```
<br>
<br>

### 3.3 - The Diver Operator (read character from terminal)

The diver operator is defined by a stick figure as follows:
```
O
|
^
```
where the `|` sits on the sea surface.

The diver finds the next `X` to the right (like the forwards mathematical operators), and places the most recently input character from the terminal there (execution will halt if no characters have been entered).

The following shows an example of a simple program which takes one character from the terminal and outputs it immediately:
```
       O _ 
   O   L/ \
---|---A---|
   ^       |
    X      o
____________
```
<br>
<br>

### 3.4 - Taking a Number as an Input

There is no direct way to take a number as an input in sea, however we can recursively read characters and stop once a non-digit is detected. In pseudocode form this may look like:
```
input = get_char()
num = 0
while(input >= '0' && input <= '9'):
  num = (num * 10) + input - '0'
  input = get_char()
print(num)
```
Whereas in Sea it looks like this:
```
                                         1              O _      
         O     /        :          0     0              L/ \     
-..------|-----,--------,----------,-----.--------------A---|----
   X     ^                            > >XX > XX            0    
 >>>>     X   X         X         X    >   >>>                   
               X -> FIN  X -> FIN  X  > >   > X                  
  X           >>>       >>>       >>>          <- INPUT          
______________________________________________________________________
        I                                                   F   
        N                                                   I   
        P                                                   N   
        U
        T
```

> **_NOTE:_** The character `/` is equal to `'0' - 1`, and `:` is equal to `'9' + 1`
<br>
<br>

### Section 4 - Advanced Memory via Scoping

It's possible to change how much memory we are working with throughout the program, and limit some memory to specific locations through scoping.

## 4.1 - Changing the Scope

As the surface is fixed and the amount of memory we can work with is the distance between the sea bed and the surface, we can allow the sea bed to slope to change which memory we can access.

The sea bed is additionally defined by the characters `/`, and `\` indicating that the sea bed has sloped up by one character, and sloped down by one character respectively.

In practice this may look like this:

```
-------------------
               ____
___ X0        /
   \  X1     /
    \_______/
```
In the above example, we start by allocating two more memory locations (X0 and X1 respectively), and then eventually reduce our scope to zero values (due to no gap between the surface and the sea bed).
<br>
<br>
<br>

## 4.2 - Scope Locality

When altering the sea bed you can even go above the surface for example:

```
                     _
                  __/ \
-----------------/     \------
               _/       \
___ X0        /          \X0'
   \  X1     /            \___
    \_______/
```
In the above example the two bodies of water are independent i.e. `X0 != X0'`.

Continuing from the previous example, if there is a blockage between any two `X`'s on the same row, then they are fundamentally different memory locations, for example consider:

```
-----------
X0      X0'     
X1   _  X1'   
X2  / \ X2'   
___/   \___
```
In the above example `x0 = x0'`, however `x1 != x1'`, and `x2 != x2'`.

This behaviour can be used to create pseudofunctions where the shared part of the sea is where inputs, outputs, and return columns should be placed, with the rest of the "function's" scope being private. This is seen in a few places in the "FizzBuzz" example.
<br>
<br>
<br>

## 4.3 - FizzBuzz

Combining everything in this language, here is a (complicated for what it's worth) FizzBuzz program written entirely in Sea, taking a numerical input from the user, and then counting from 1 to the number entered.

```
                                                                                                1               1                                                                                                                                ___
                                         1                                                      0               1        O _                                                                         _     O _  O _  O _  O _                 __/ B \      O _  O _  O _  O _                      2O _
         O     /        :          0     0                         1   5 3      1               0        1      7        L/ \           1                                                         __/F\    L/F\ L/i\ L/z\ L/z\               /    U  \_    L/B\ L/u\ L/z\ L/z\                 _   2L/ \                 _
-..------|-----,--------,----------,-----.-------------------------.---....-..--.---.--..-------.-.------.-----...-------A---|----------.--------------------------------------------------------/   I \---A-,.|A-,.|A-,.|A-,.|..-----------/     Z    \---A-,.|A-,.|A-,.|A-,.|..-------------/N\-,.A---|..-------------/Q
   X     ^                            > >XX > XX                  X             >X                                           0          XX X                          X >  X                    /    Z  \     Xo   Xo   Xo   Xo X <- FIVE  /      Z     \     Xo   Xo   Xo   Xo X -> NEWLINE / E \>>>  Xo X <- ENDLOOP / U
 >>>>     X   X         X         X    >   >>>                     >           >>>  X           >>>            X>>>                                                   X>X>                     /     Z   \>>>  >>>  >>>  >>>  >>>         /              \>>>  >>>  >>>  >>>  >>>          _/  W  \     >>>           /  I
               X -> INIT X -> INIT X  > >   > X                   >>>    >>>    >                 X           >>> X                                                   > >             <~      /           \______________________________/                \_______________________________/    L   \_________________/   T
  X           >>>       >>>       >>>          <- INPUT            >   >>>         >>>              -> FIZZ          -> BUZZ                                          X>X> >>>X              /                                                                                                 I
__________________________________________________________________          >>>X      >>>        -> MOD >         -> MOD  -> NEWLINE                  <- LOOP    _       X  X               /                                                                                                  N
        I                                               I         \     X                              >>>    X                                                 /M\________________________/                                                                                                   E
        N                                               N          \       X       X                    >                                                      / O                        
        P                                               I           \                   X               X  X           -> NEWLINE      >                      /  D                        
        U                                               T            \X                                                               >>> X                  /                             
        T                                                             \                                                                >  >>>X  -> QUIT     /
                                                                       \___________________________________________________________________________________/
                                                                                   L                          F                       E
                                                                                   O                          I                       N
                                                                                   O                          V                       D
                                                                                   P                          E                       L
                                                                                                                                      O
                                                                                                                                      O
                                                                                                                                      P
```
