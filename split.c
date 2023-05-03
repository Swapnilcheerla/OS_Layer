#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define LSIZ 128
#define RSIZ 10

char *charToBinaryWithParity(char ch);

char *charToBinaryWithParity(char ch)
{
    /// Assigning charcater to integer for getting the int value of char
    int parityChar = ch;
    char *parityString = malloc(200 * sizeof(char));

    int k = 7, j1;
    int i, j, keylen, msglen;
    char input[100], key[30], temp[30], quot[100], rem[30], key1[30];

    while (parityChar != 0)
    {
        if (parityChar % 2 == 0)
            parityString[k] = '0';
        if (parityChar % 2 == 1)
            parityString[k] = '1';
        /// incrementing count for parity checking purpose

        parityChar = parityChar / 2;
        k--;
    }
    /// appending zero for the remaning bits
    for (j1 = k; j1 >= 0; j1--)
    {
        parityString[j1] = '0';
    }

    // key="1000";
    // printf("Enter Key: ");
    // gets(key);
    key[0] = '1';
    key[1] = '0';
    key[2] = '0';
    key[3] = '0';
    key[4] = '\0';

    keylen = strlen(key);
    msglen = 7;
    strcpy(key1, key);
    for (i = 0; i < keylen - 1; i++)
    {
        parityString[msglen + i] = '0';
    }
    for (i = 0; i < keylen; i++)
        temp[i] = parityString[i];
    for (i = 0; i < msglen; i++)
    {
        quot[i] = temp[0];
        if (quot[i] == '0')
            for (j = 0; j < keylen; j++)
                key[j] = '0';
        else
            for (j = 0; j < keylen; j++)
                key[j] = key1[j];
        for (j = keylen - 1; j > 0; j--)
        {
            if (temp[j] == key[j])
                rem[j - 1] = '0';
            else
                rem[j - 1] = '1';
        }
        rem[keylen - 1] = parityString[i + keylen];
        strcpy(temp, rem);
    }
    strcpy(rem, temp);

    printf("\nQuotient is ");
    for (i = 0; i < msglen; i++)
        printf("%c", quot[i]);
    printf("\nRemainder is ");
    for (i = 0; i < keylen - 1; i++)
        printf("%c", rem[i]);
    printf("\nFinal data is: ");
    for (i = 0; i < msglen; i++)
        printf("%c", parityString[i]);
    for (i = 0; i < keylen - 1; i++)
        printf("%c", rem[i]);

    return parityString;
}

int main()
{
    char string[500] = "123456780001234567800012345678000";
    int i = 0;
    // char trimstring[500];
    char *trimstring = malloc(500 * sizeof(char));
    int c = 0;
    int k = 0;
    printf("my name : %s", charToBinaryWithParity('a'));
    while (string[i] != '\0')
    {
        trimstring[c] = string[i];
        c++;
        k = k + 1;

        if (k == 8)
        {
            i = i + 4;
            k = 0;
        }
        else
        {
            i = i + 1;
        }
    }
    trimstring[c] = '\0';
    // printf("%s", trimstring);
    //  Extract the first token

    return 0;
}