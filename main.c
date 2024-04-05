#include <stdio.h>
#include <stdlib.h>
#include "main.h"

#define WORD_LENGTH 15
#define TRY_LEFT 10

int main(int argc, char *argv[])
{
    int running = 1;
    int menu = 0;

    char word[WORD_LENGTH];
    for (int i = 0; i < WORD_LENGTH - 1; i++)
    {
        word[i] = '_';
    }

    int tryLeft = TRY_LEFT;

    char lettersTried[TRY_LEFT + 1];
    for (int i = 0; i < TRY_LEFT; i++)
    {
        lettersTried[i] = ' ';
    }
    lettersTried[TRY_LEFT] = '\0';

    int foundLetters[WORD_LENGTH] = {0};

    char hiddenWord[WORD_LENGTH];
    for (size_t i = 0; i < WORD_LENGTH - 1; i++)
    {
        hiddenWord[i] = '_';
    }

    int wordIsValid = 0;

    char letter = '_';
    int letterIsValid = 0;

    while (running == 1)
    {
        switch (menu)
        {
        case 0:
            showMainMenu();
            menu = inputNb();
            break;

        case 1:
            printf("\nVeuillez choisir le mot: ");
            wordIsValid = inputWord(word);

            while (!strIsAlpha(word) || wordIsValid == 0)
            {
                if (wordIsValid == 0)
                {
                    printf("\n\nLe mot est trop long");
                }
                else
                {
                    printf("\n\nCe n'est pas un mot");
                }

                printf("\nVeuillez choisir un mot: ");
                wordIsValid = inputWord(word);
            }
            setTopStr(word);
            copySize(word, hiddenWord);
            menu = 0;
            break;

        case 2:
            printf("\n\nVeuillez deviner le mot: %s", hiddenWord);
            printf("\nIl vous reste %d essais", tryLeft);
            printf("\nVous avez déjà essayé les lettre suivantes: %s", lettersTried);
            printf("\nQuelle lettre voulez-essayer ? ");

            letter = '_';
            letterIsValid = inputLetter(&letter);

            while (letterIsValid == 0)
            {
                printf("\n\nLa lettre n'est pas valide\nQuelle lettre voulez-vous essayer ? ");
                letterIsValid = inputLetter(&letter);
            }

            if (strContainsLetter(word, letter))
            {
                setFoundLetters(word, letter, foundLetters);
                setHiddenWord(hiddenWord, word, foundLetters);
            }
            else
            {
                lettersTried[TRY_LEFT - tryLeft] = letter;
                tryLeft--;
            }

            if (checkWin(word, foundLetters))
            {
                menu = 1264;
            }
            if (tryLeft == 0)
            {
                menu = 8753;
            }

            break;

        case 3:
            printf("\nVous quittez le jeu");
            running = 0;
            break;

        case 1264:
            printf("\n\nVous avez trouvé le mot ! C'était : %s", word);
            menu = 6;
            break;

        case 8753:
            printf("\n\nVous avez perdu :(\nLe mot était %s", word);
            menu = 6;
            break;

        case 6:
            showMenu();
            menu = inputNb();
            break;

        default:
            printf("\n\n Ce n'est pas dans les possibilitées...");
            menu = 0;
            break;
        }
    }

    printf("\n\n");
    return 0;
}

void showMainMenu()
{
    printf("\n\n** Bienvenue au pendu **\n\n");
    printf("1: choisir le mot à deviner\n");
    printf("2: Essayer de deviner le mot\n");
    printf("3: Quitter\n");
}

void showMenu()
{
    printf("\n\n0: Retour\n3: Quitter\n");
}

int inputNb()
{
    char strNb[2];
    fgets(strNb, 2, stdin);
    emptyBuffer();

    int nb = strNb[0] - 48;

    return nb;
}

int inputWord(char *strWord)
{
    if (fgets(strWord, WORD_LENGTH, stdin) != NULL)
    {
        int wordIsValid = 0;

        for (int i = 0; i < WORD_LENGTH; i++)
        {
            if (strWord[i] == '\n')
            {
                strWord[i] = '\0';
                wordIsValid = 1;
            }
        }
        if (wordIsValid == 0)
        {
            emptyBuffer();
        }

        return wordIsValid;
    }
    else
    {
        emptyBuffer();
        return 0;
    }
}

int inputLetter(char *letter)
{
    char strLetter[3];
    if (fgets(strLetter, 3, stdin) != NULL)
    {
        if (strLetter[1] == '\n')
        {
            strLetter[1] = '\0';
            if (strIsAlpha(strLetter))
            {
                setTopStr(strLetter);
                *letter = strLetter[0];
                return 1;
            }
            else
            {
                return 0;
            }
        }
        else if (strLetter[0] == '\n')
        {
            return 0;
        }
        else
        {
            emptyBuffer();
            return 0;
        }
    }
    else
    {
        return 0;
        emptyBuffer();
    }
}

int strIsAlpha(const char *strWord)
{
    int i = 0;
    while (strWord[i] != '\0')
    {
        if (strWord[i] < 65 || strWord[i] > 122 || (strWord[i] > 90 && strWord[i] < 97))
        {
            return 0;
        }
        i++;
    }
    return 1;
}

void setTopStr(char *strWord)
{
    int i = 0;
    while (strWord[i] != '\0')
    {
        if (strWord[i] > 96 && strWord[i] < 123)
        {
            strWord[i] -= 32;
        }
        i++;
    }
}

void setFoundLetters(const char *word, char letter, int foundLetters[])
{
    int i = 0;
    while (word[i] != '\0')
    {
        if (word[i] == letter)
        {
            foundLetters[i] = 1;
        }
        i++;
    }
}

void setHiddenWord(char *hiddenWord, const char *word, int foundLetters[])
{
    int i = 0;
    while (word[i] != '\0')
    {
        if (foundLetters[i] == 1)
        {
            hiddenWord[i] = word[i];
        }
        else
        {
            hiddenWord[i] = '_';
        }
        i++;
    }
}

int strContainsLetter(const char *word, char letter)
{
    int i = 0;
    int contains = 0;
    while (word[i] != '\0')
    {
        if (word[i] == letter)
        {
            contains = 1;
        }
        i++;
    }
    return contains;
}

void copySize(const char *word, char *hiddenWord)
{
    int i = 0;
    while (word[i] != '\0')
    {
        i++;
    }
    hiddenWord[i] = '\0';
}

int checkWin(const char *word, const int foundLetters[])
{
    int i = 0;
    int win = 1;
    while (word[i] != '\0')
    {
        if (foundLetters[i] == 0)
        {
            win = 0;
        }
        i++;
    }
    return win;
}

void emptyBuffer()
{
    int c = 0;
    while (c != '\n' && c != EOF)
    {
        c = getchar();
    }
}