#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define LSIZ 128
#define RSIZ 10
void charToBinaryWithParity(char ch);

void charToBinaryWithParity(char ch)
{
  /// Assigning charcater to integer for getting the int value of char
  int parityChar = ch;
  char parityString[100];
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
}

int main(void)
{
  int socket_desc;
  struct sockaddr_in server_addr;
  char server_message[LSIZ];

  char client_message[RSIZ][LSIZ];
  char client_encodedMsg[RSIZ][LSIZ];
  FILE *fptr = NULL;
  int i = 0;
  int tot = 0;
  fptr = fopen("encode.txt", "r");
  while (fgets(client_message[i], LSIZ, fptr))
  {
    client_message[i][strlen(client_message[i]) - 1] = '\0';
    i++;
  }
  tot = i;
  printf("%d", tot);
  // printf(" %s\n", client_message[0]);
  for (i = 0; i < tot; ++i)
  {
    printf(" %s\n", client_message[0]);
    //  addFraming(client_encodedMsg[i],client_message[i],tot);
  }

  // Clean buffers:
  // memset(server_message,'\0',sizeof(server_message));
  // memset(client_message,'\0',sizeof(client_message));

  // Create socket:
  printf(" %s\n", client_message[0]);
  socket_desc = socket(AF_INET, SOCK_STREAM, 0);

  if (socket_desc < 0)
  {
    printf("Unable to create socket\n");
    return -1;
  }

  printf("Socket created successfully\n");

  // Set port and IP the same as server-side:
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(2000);
  server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

  // Send connection request to server:
  if (connect(socket_desc, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
  {
    printf("Unable to connect\n");
    return -1;
  }
  printf("Connected with server successfully\n");

  // Get input from the user:
  printf("Enter message: ");
  // gets(client_message);
  // for(i=0; i< strlen(server_message);i++)
  printf(" %s\n", client_message[0]);

  // Send the message to server:
  if (send(socket_desc, client_encodedMsg, sizeof(client_encodedMsg), 0) < 0)
  {
    printf("Unable to send message\n");
    return -1;
  }

  // Receive the server's response:
  if (recv(socket_desc, server_message, sizeof(server_message), 0) < 0)
  {
    printf("Error while receiving server's msg\n");
    return -1;
  }
  printf("Server's response: %s\n", server_message);

  // Close the socket:
  close(socket_desc);

  return 0;
}