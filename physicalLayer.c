#include<stdio.h>
#include<math.h>
#include<string.h>
#include "encDec.h"

/// converting integer value to binary format and append it to sizeBinaryValue frame
/// size length of characters in file
void integerToBinary(int size, char sizeBinaryValue[]){
  int i=7,j;
  while(size != 0){
    if(size%2 == 0)
    sizeBinaryValue[i] = '0';
    if(size%2 == 1)
    sizeBinaryValue[i] = '1';
    size =size/2;
    i--;
  }
  for(j=i;j>=0;j--){
    sizeBinaryValue[j] = '0';
  }

}

/// This for converting 2222 ascii to binary, This we will do for every input file and inout
void synIntegerToBinary(int size, char synBinaryValue[]){
  int i=15,j,k;
  /// here syn number is 2222
  while(size != 0){
    /// if size value remainder is 0 assigning char 0 to array and similar for 1
    if(size%2 == 0)
    synBinaryValue[i] = '0';
    if(size%2 == 1)
    synBinaryValue[i] = '1';
    size =size/2;
    i--;
  }
  /// adding zero to remaining bits
  for(j=i;j>=0;j--){
    synBinaryValue[j] = '0';
  }
}

/// Converting the characters of file to binary and writing to character frame
void charToBinaryWithParity(char ch, char parityString[])
{
  ///Assigning charcater to integer for getting the int value of char
  int parityChar = ch;
  int i=7,j,k,count = 0;
  while(parityChar != 0){
    if(parityChar%2 == 0)
    parityString[i] = '0';
    if(parityChar%2 == 1)
    parityString[i] = '1';
/// incrementing count for parity checking purpose
    if(parityString[i]== '1'){
    count++;
    }
    parityChar =parityChar/2;
    i--;
  }
  /// appending zero for the remaning bits
  for(j=i;j>=1;j--){
    parityString[j] = '0';
  }
  /// checking parity
  if(count%2 ==0){
    parityString[0] = '1';
  }
  else{
    parityString[0] = '0';
  }
}

/// converting binary value to integer , this is for finding size
int binaryToInt(char sizeBinaryValue[]){
  int value=0,i;
  for(i=0; i< 8;i++){
    /// checking the index from reverse and finding power of ith value
    if(sizeBinaryValue[i]== '1'){
      value= value+ pow(2,7-i);
    }
  }
  return value;
}

/// converting the characters of binary to char and removing the parity which we have added
/// to every 8 bits string at beginning
void intToBinaryWithCheckParity(char parityString[], char deframech){
  int value=0,i,count =0;
  /// not considering 0th index as it has parity bit i.e. removing it
  for(i=1; i< 8;i++){
    if(parityString[i]== '1'){
      value= value+ pow(2,7-i);
      count ++;
    }
  }
  /// assigning each value by calcualting the ith index in the 
  /// array and calculating power and summing them
  deframech = value;
}

