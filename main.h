#ifndef main_h
#define main_h

#include <stdio.h>
#include <stdlib.h>

void showMainMenu();
void showMenu();
int inputNb();
int inputWord(char *strWord);
int inputLetter(char *letter);
int strIsAlpha(const char *strWord);
void setTopStr(char *strWord);
void setFoundLetters(const char *word, char letter, int foundLetters[]);
void setHiddenWord(char *hiddenWord, const char *word, int foundLetters[]);
int strContainsLetter(const char *word, char letter);
void copySize(const char *word, char *hiddenWord);
int checkWin(const char *word, const int foundLetters[]);
void emptyBuffer();

#endif