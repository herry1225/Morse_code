/*
 * Morse Code Translator
 * ---------------------
 * Converts text to Morse code and Morse code back to text.
 * Also has a Morse chart and a practice quiz.
 *
 * Concepts used: arrays, strings, loops, functions, if-else, switch.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 36        /* 26 letters + 10 digits */
#define MAXLEN 200

/* symbols[i] and code[i] belong together: A -> ".-", B -> "-...", ... */
char symbols[SIZE + 1] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

char code[SIZE][6] = {
    ".-",   "-...", "-.-.", "-..",  ".",    "..-.", "--.",  "....", "..",   ".---",
    "-.-",  ".-..", "--",   "-.",   "---",  ".--.", "--.-", ".-.",  "...",  "-",
    "..-",  "...-", ".--",  "-..-", "-.--", "--..",
    "-----", ".----", "..---", "...--", "....-",
    ".....", "-....", "--...", "---..", "----."
};

/* ---------- helper functions ---------- */

/* reads a line of text and removes the newline at the end */
void readLine(char s[], int size) {
    int i = 0;
    if (fgets(s, size, stdin) == NULL) {
        printf("\nInput ended. Bye!\n");
        exit(0);
    }
    while (s[i] != '\0') {
        if (s[i] == '\n') {
            s[i] = '\0';
            break;
        }
        i++;
    }
}

/* returns the position of a character in the table, or -1 if not found */
int findSymbol(char c) {
    int i;
    if (c >= 'a' && c <= 'z') {
        c = c - 32;   /* make it uppercase */
    }
    for (i = 0; i < SIZE; i++) {
        if (symbols[i] == c) {
            return i;
        }
    }
    return -1;
}

/* ---------- main features ---------- */

void textToMorse(char text[]) {
    int i, j, idx;
    int dots = 0, dashes = 0;

    printf("\nMorse code: ");
    for (i = 0; text[i] != '\0'; i++) {
        if (text[i] == ' ') {
            printf("/ ");           /* word separator */
        } else {
            idx = findSymbol(text[i]);
            if (idx == -1) {
                printf("? ");       /* unsupported character */
            } else {
                printf("%s ", code[idx]);
                for (j = 0; code[idx][j] != '\0'; j++) {
                    if (code[idx][j] == '.') dots++;
                    else dashes++;
                }
            }
        }
    }
    printf("\nDots: %d | Dashes: %d\n", dots, dashes);
}

void morseToText(char morse[]) {
    char token[8];
    int len = 0, i, k, idx;
    char c;

    printf("\nDecoded text: ");
    for (i = 0; ; i++) {
        c = morse[i];
        if (c == '.' || c == '-') {
            if (len < 7) {
                token[len] = c;
                len++;
            }
        } else {
            /* a space, '/' or end of line finishes the current letter */
            if (len > 0) {
                token[len] = '\0';
                idx = -1;
                for (k = 0; k < SIZE; k++) {
                    if (strcmp(token, code[k]) == 0) {
                        idx = k;
                    }
                }
                if (idx == -1) printf("?");
                else printf("%c", symbols[idx]);
                len = 0;
            }
            if (c == '/') {
                printf(" ");
            }
            if (c == '\0') {
                break;
            }
        }
    }
    printf("\n");
}

void showChart(void) {
    int i;
    printf("\n------------ MORSE CODE CHART ------------\n");
    for (i = 0; i < SIZE; i++) {
        printf("%c = %-5s", symbols[i], code[i]);
        if ((i + 1) % 4 == 0) {
            printf("\n");
        } else {
            printf("   ");
        }
    }
    printf("\n------------------------------------------\n");
}

void quiz(void) {
    char answer[MAXLEN];
    int round, idx, score = 0;

    srand(time(NULL));
    printf("\n--- MORSE QUIZ (5 rounds) ---\n");
    for (round = 1; round <= 5; round++) {
        idx = rand() % SIZE;
        printf("Q%d: Type the Morse code for '%c': ", round, symbols[idx]);
        readLine(answer, MAXLEN);
        if (strcmp(answer, code[idx]) == 0) {
            printf("Correct!\n");
            score++;
        } else {
            printf("Wrong. The answer is %s\n", code[idx]);
        }
    }

    printf("\nYour score: %d / 5\n", score);
    if (score == 5) {
        printf("Excellent! You are a Morse master!\n");
    } else if (score >= 3) {
        printf("Good job! Keep practising.\n");
    } else {
        printf("Check the chart (option 3) and try again.\n");
    }
}

void showMenu(void) {
    printf("\n===== MORSE CODE TRANSLATOR =====\n");
    printf("1. Text to Morse code\n");
    printf("2. Morse code to text\n");
    printf("3. Show Morse chart\n");
    printf("4. Practice quiz\n");
    printf("5. Exit\n");
    printf("Enter your choice: ");
}

int main(void) {
    char input[MAXLEN];
    int choice = 0;

    while (choice != 5) {
        showMenu();
        readLine(input, MAXLEN);
        choice = atoi(input);

        switch (choice) {
            case 1:
                printf("\nEnter text (letters, digits, spaces): ");
                readLine(input, MAXLEN);
                textToMorse(input);
                break;
            case 2:
                printf("\nEnter Morse code (space between letters, '/' between words):\n");
                readLine(input, MAXLEN);
                morseToText(input);
                break;
            case 3:
                showChart();
                break;
            case 4:
                quiz();
                break;
            case 5:
                printf("\nGoodbye! ... . . / -.-- --- ..- / ... --- --- -.\n");
                break;
            default:
                printf("\nInvalid choice, try again.\n");
        }
    }
    return 0;
}