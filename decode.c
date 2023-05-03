#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#define LSIZ 2000
#define RSIZ 2000

unsigned long binaryToDecimal(char *binary, int length);
void binaryToText(char *binary, int binaryLength, char *text, int symbolCount);
void formatBinary(char *input, int length, char *output);
int validate(char *binary);
char *trimcrc(char ch[]);

char *trimcrc(char string[])
{
    // char string[100] = "0110000100011111111111";
    char *trimstring = malloc(500 * sizeof(char));
    int i = 0;
    // char trimstring[500];
    int c = 0;
    int k = 0;
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
    return trimstring;
}
int main(void)
{
    // char string[500] = "01100001000011000100000110001100000000000000";
    char *binary;
    int binaryLength;
    char client_message[RSIZ][LSIZ];
    char client_encodedMsg[RSIZ][LSIZ];
    FILE *fptr = NULL;
    FILE *fptrdecode = NULL;
    pthread_t id;
    int i = 0;
    int tot = 0;
    int line = 0;

    fptr = fopen("encode.txt", "r");
    fptrdecode = fopen("decode.txt", "w"); // "w" defines "writing mode"
    while (fgets(client_message[i], LSIZ, fptr))
    {
        client_message[i][strlen(client_message[i]) - 1] = '\0';
        i++;
    }
    tot = i;
    printf("%d", tot);
    printf("start\n");
    for (i = 0; i < 5; ++i)
    {
        if (strlen(client_message[i]) != 0)
        {
            printf("stringabc%s\n", client_message[i]);
        }
    }
    printf("finish");
    for (line = 0; line < tot; line++)
    {
        char *token = strtok(client_message[line], " ");
        // printf(" %s\n", client_message[0]);
        /* for (i = 0; i < tot; ++i)
        {
            printf(" %s\n", client_message[0]);
            //  addFraming(client_encodedMsg[i],client_message[i],tot);
        }
        */

        // loop through the string to extract all other tokens
        while (token != NULL)
        {
            printf(" %s\n", token); // printing each token
            binary = trimcrc(token);

            // scanf("%558[^\n]s", binary);
            binaryLength = strlen(binary);
            if (validate(binary))
            {
                int symbolCount = binaryLength / 8 + 1;
                char *text = malloc(symbolCount + 1);
                char *formattedBinary = malloc(binaryLength + 1);
                if (text == NULL || formattedBinary == NULL)
                    exit(1);
                if (binaryLength % 8 == 0)
                    --symbolCount;

                formatBinary(binary, binaryLength, formattedBinary);
                binaryToText(formattedBinary, strlen(formattedBinary), text, symbolCount);
                printf("%s in binary is the following text:\n%s\n", binary, text);
                // pthread_create(&id, NULL, foo, &text);

                fprintf(fptrdecode, "%s", text);

                fprintf(fptrdecode, " ");

                free(text);
                free(formattedBinary);
            }
            else
            {
                printf("The input should be a binary number, containing only zeros(0) and ones(1).\n");
            }
            token = strtok(NULL, " ");
        }
        fprintf(fptrdecode, "\n");
    }

    return 0;
}

void binaryToText(char *binary, int binaryLength, char *text, int symbolCount)
{
    int i;
    for (i = 0; i < binaryLength; i += 8, binary += 8)
    {
        char *byte = binary;
        byte[8] = '\0';
        *text++ = binaryToDecimal(byte, 8);
    }
    text -= symbolCount;
}

unsigned long binaryToDecimal(char *binary, int length)
{
    int i;
    unsigned long decimal = 0;
    unsigned long weight = 1;
    binary += length - 1;
    weight = 1;
    for (i = 0; i < length; ++i, --binary)
    {
        if (*binary == '1')
            decimal += weight;
        weight *= 2;
    }

    return decimal;
}

void formatBinary(char *input, int length, char *output)
{
    while (*input)
    {
        if (*input == '0' || *input == '1')
        {
            *output++ = *input++;
        }
        else
        {
            ++input;
            --length;
        }
    }
    output -= length;
}

int validate(char *binary)
{
    while (*binary)
    {
        if ((*binary != '0') && (*binary != '1') && (*binary != ' '))
            return 0;
        ++binary;
    }
    return 1;
}
