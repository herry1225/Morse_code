# Morse Code Translator in C


I made this program for my C programming course. It's a small command-line tool that turns normal text into Morse code, turns Morse code back into text, and even quizzes you so you can learn the code yourself.

I picked Morse code because it needs exactly the things we studied in class: arrays, strings, loops, functions, `if-else` and `switch`. I didn't use structures, pointers or file handling. I wanted to see how much I could build with just the basics.

---

## Table of Contents

1. [What the program can do](#what-the-program-can-do)
2. [A quick look at Morse code](#a-quick-look-at-morse-code)
3. [Running it on your computer](#running-it-on-your-computer)
4. [Step-by-step walkthrough (screenshots)](#step-by-step-walkthrough-screenshots)
5. [More sample outputs](#more-sample-outputs)
6. [How the code works](#how-the-code-works)
7. [C concepts used](#c-concepts-used)
8. [Problems I ran into](#problems-i-ran-into)
9. [Limitations](#limitations)
10. [Ideas for later](#ideas-for-later)

---

## What the program can do

When you start it, a menu appears with five choices:

| Option | What happens |
|--------|--------------|
| **1. Text to Morse** | You type a sentence and get the Morse code. It also tells you how many dots and dashes it used. |
| **2. Morse to text** | You paste in Morse code and get the readable message back. |
| **3. Morse chart** | Prints the whole table (A to Z and 0 to 9) so you can look things up. |
| **4. Practice quiz** | Asks for the Morse code of 5 random characters and gives you a score at the end. |
| **5. Exit** | Closes the program with a small Morse goodbye. |

The menu comes back after every action, so you can keep using it as long as you like.

---

## A quick look at Morse code

Morse code writes every letter and digit as a pattern of short signals (dots) and long signals (dashes). For example:

- `E` is just one dot: `.`
- `T` is just one dash: `-`
- `S` is three dots: `...`
- `O` is three dashes: `---`

So the famous distress signal SOS is `... --- ...`.

The program follows these simple writing rules:

- Leave a **space** between two letters.
- Put a **/** between two words.
- Capital and small letters give the same result.
- Letters and digits are supported. Anything else (like `!` or `@`) is shown as `?`.

---

## Running it on your computer

You only need a C compiler. I used GCC.

```bash
git clone https://github.com/<your-username>/morse-code-translator.git
cd morse-code-translator
gcc main.c -o morse
./morse
```

On Windows with MinGW, use this instead:

```bash
gcc main.c -o morse.exe
morse.exe
```

If you use Code::Blocks, Dev-C++ or a similar editor, just open `main.c`, then build and run it.

---

## Step-by-step walkthrough (screenshots)

Here is a full run of the program, step by step. All screenshots are from my own computer.

### Step 1: Convert text to Morse code

Choose option **1** from the menu and type any text. I typed my name, *Harshit*. The program prints the Morse code and counts the dots and dashes (16 dots and 3 dashes).
<img width="546" height="538" alt="Screenshot 2026-11-02 140826" src="https://github.com/user-attachments/assets/34574e22-9915-40d8-9e1e-5ab654208937" />



### Step 2: Convert Morse code back to text

Choose option **2** and paste the Morse code from the previous step. Put a space between letters and a `/` between words. The program decodes it back to **HARSHIT**.
<img width="506" height="577" alt="Screenshot 2026-11-02 140850" src="https://github.com/user-attachments/assets/1090506e-5c0a-4a80-976c-4ecd8c17d51b" />



### Step 3: Look up the Morse chart

Choose option **3** to see the full table for A to Z and 0 to 9. This is the same table the program uses internally. It's handy for learning or checking a letter.

(The chart is at the bottom of the screenshot above.)

### Step 4: Take the practice quiz

Choose option **4**. The program picks 5 random characters and asks for the Morse code of each one. It tells you right away whether you were correct and shows your score at the end.


<img width="442" height="401" alt="Screenshot 2026-11-02 140911" src="https://github.com/user-attachments/assets/7e20e824-f884-4d51-9a9c-0f08c2b7f2d5" />


### Step 5: Exit

Choose option **5** to close the program. It says goodbye in Morse code: `... . . / -.-- --- ..- / ... --- --- -.` (SEE YOU SOON).

<img width="446" height="232" alt="Screenshot 2026-11-02 140928" src="https://github.com/user-attachments/assets/5cab77de-587c-4d02-a660-2905a4812b0f" />

---

## More sample outputs

These are a few extra outputs from my program.

### Text to Morse

```
Enter your choice: 1

Enter text (letters, digits, spaces): Hello World

Morse code: .... . .-.. .-.. --- / .-- --- .-. .-.. -..
Dots: 19 | Dashes: 13
```

### Unsupported characters

```
Enter text (letters, digits, spaces): hi!

Morse code: .... .. ?
Dots: 6 | Dashes: 0
```

The `!` isn't in the table, so it becomes a `?` instead of crashing the program.

### Morse to text

```
Enter your choice: 2

Enter Morse code (space between letters, '/' between words):
.... . .-.. .-.. --- / .-- --- .-. .-.. -..

Decoded text: HELLO WORLD
```

### The chart

```
------------ MORSE CODE CHART ------------
A = .-      B = -...    C = -.-.    D = -..
E = .       F = ..-.    G = --.     H = ....
I = ..      J = .---    K = -.-     L = .-..
M = --      N = -.      O = ---     P = .--.
Q = --.-    R = .-.     S = ...     T = -
U = ..-     V = ...-    W = .--     X = -..-
Y = -.--    Z = --..    0 = -----   1 = .----
2 = ..---   3 = ...--   4 = ....-   5 = .....
6 = -....   7 = --...   8 = ---..   9 = ----.
------------------------------------------
```

### The quiz

```
--- MORSE QUIZ (5 rounds) ---
Q1: Type the Morse code for 'K': -.-
Correct!
Q2: Type the Morse code for '7': --.
Wrong. The answer is --...
...
Your score: 4 / 5
Good job! Keep practising.
```

The questions are random, so every round is different.

---

## How the code works

### 1. Storing the Morse table

The whole program depends on two arrays that run side by side:

```c
char symbols[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
char code[36][6] = { ".-", "-...", "-.-.", ... };
```

The character at position `i` in `symbols` matches the Morse pattern at position `i` in `code`. So `symbols[1]` is `'B'` and `code[1]` is `"-..."`. Translating anything is just a matter of finding the right position.

### 2. Text to Morse

The program goes through the text one character at a time:

1. If the character is a space, print `/`.
2. Otherwise, search the `symbols` array for it (small letters are first changed to capitals).
3. If it is found, print the matching pattern from `code` and count its dots and dashes.
4. If it is not found, print `?`.

### 3. Morse to text

This direction was harder. The program reads the Morse string one character at a time and builds up the current letter in a small array. When it meets a space, a `/` or the end of the line, it knows the letter is finished. It then compares the collected pattern against every entry of the `code` table with `strcmp()`. If one matches, it prints the letter. If none match, it prints `?`. A `/` also prints a space between words.

### 4. The quiz

The quiz uses `rand()` to pick a random position in the table, shows that character, and compares what you typed with the real pattern using `strcmp()`. It keeps a running score and gives a different message depending on how well you did.

### Functions in the program

| Function | Job |
|----------|-----|
| `main()` | Shows the menu in a `while` loop and calls the right function using `switch` |
| `showMenu()` | Prints the menu |
| `textToMorse()` | Converts text to Morse and counts dots and dashes |
| `morseToText()` | Converts Morse back to text |
| `showChart()` | Prints the Morse chart in rows of four |
| `quiz()` | Runs the 5-question practice round |
| `findSymbol()` | Finds a character's position in the table (and handles small letters) |
| `readLine()` | Reads a whole line, including spaces, and removes the newline at the end |

---

## C concepts used

| Concept | Where I used it |
|---------|-----------------|
| Arrays | `symbols[]` and the 2D array `code[][]` hold the Morse table |
| Strings | `strcmp()` to compare patterns, plus handling text with spaces |
| Loops | Walking through the input, searching the table, quiz rounds and the menu |
| Functions | Every feature is its own function, which keeps `main()` short |
| if-else | Telling letters from spaces, checking if a symbol exists, quiz messages |
| switch | Picking the right menu option |

---

## Problems I ran into

- **Reading a sentence with spaces.** `scanf("%s")` stops at the first space, so "Hello World" would only read "Hello". I switched to `fgets()` and wrote my own small `readLine()` function to clean up the newline.
- **Mixing numbers and text input.** Reading the menu choice with `scanf` left an extra newline in the input, which broke the next text entry. Reading the choice as a line and converting it with `atoi()` fixed this.
- **Decoding Morse.** Separating one letter from the next was the trickiest part. Building each letter in a small buffer and finishing it at every space or `/` solved it.
- **Bad input.** Early versions printed garbage for characters like `!`. Adding the `?` fallback made the program much more reliable.

---

## Limitations

- Only A to Z and 0 to 9 are supported, with no punctuation.
- Input is limited to 200 characters per line.
- In the decoder, a single letter pattern can be at most 7 signals long. Anything longer shows as `?`.
- Quiz answers must be typed exactly as in the chart, with no extra spaces.

---

## Ideas for later

- Add punctuation such as `.`, `,` and `?`.
- Play real beeps for the dots and dashes.
- Save quiz high scores in a file.
- Add a difficulty level, such as quizzing on whole words.

---

## About me

Made by **[Harshit]**, [B.tech CSE / First year], [Chandigarh University].

Feel free to download the code, try it out and suggest improvements.
