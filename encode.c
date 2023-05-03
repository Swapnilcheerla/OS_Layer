#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#define LSIZ 128
#define RSIZ 10

char *charToBinaryWithParity(char ch);

char *charToBinaryWithParity(char ch)
{
	/// Assigning charcater to integer for getting the int value of char
	int parityChar = ch;
	char *parityString = malloc(100 * sizeof(char));

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
	key[1] = '1';
	key[2] = '0';
	key[3] = '1';
	key[4] = '\0';

	keylen = strlen(key);
	msglen = 8;
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
	/*
	printf("\nQuotient is ");
	for (i=0;i<msglen;i++)
	 printf("%c",quot[i]);
	printf("\nRemainder is ");
	for (i=0;i<keylen-1;i++)
	 printf("%c",rem[i]);
	printf("\nFinal data is: ");
	for (i=0;i<msglen;i++)
	 printf("%c",parityString[i]);
	for (i=0;i<keylen-1;i++)
	 printf("%c",rem[i]);
	 */
	return parityString;
}

int main()
{
	// char parityString[100];
	char text_message[RSIZ][LSIZ];
	char client_encodedMsg[RSIZ][LSIZ];
	FILE *fptr = NULL;
	char singlechar;
	char *content;
	int i = 0;
	int tot = 0;
	int row = 0;
	int column = 0;
	FILE *fptra = NULL;
	fptr = fopen("intext.txt", "r");

	while (fgets(text_message[i], LSIZ, fptr))
	{
		text_message[i][strlen(text_message[i]) - 1] = '\0';
		i++;
	}
	tot = i;
	printf("%d", tot);
	// printf(" %s\n", text_message[0]);

	// Clean buffers:
	// memset(server_message,'\0',sizeof(server_message));
	// memset(text_message,'\0',sizeof(text_message));

	// Create socket:
	// printf(" %c\n", text_message[1][0]);
	fptra = fopen("encode.txt", "w"); // "w" defines "writing mode"

	for (row = 0; row < tot; row++)
	{
		for (column = 0; column <= strlen(text_message[row]) + 1; column++)
		{
			singlechar = text_message[row][column];
			content = charToBinaryWithParity(text_message[row][column]);
			if (singlechar == ' ')
			{
				fprintf(fptra, " ");
			}
			else
			{
				fprintf(fptra, "%s", content);
			}
		}
		fprintf(fptra, "\n");
	}

	//  addFraming(client_encodedMsg[i],text_message[i],tot);
	return 0;
}

// charToBinaryWithParity(text_message[0][0]);
// printf("%s",parityString);
//}
