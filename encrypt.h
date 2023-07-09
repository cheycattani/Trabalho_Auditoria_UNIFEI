#include <stdio.h>
#include <stdlib.h>

typedef unsigned char byte;

void Encrypt(byte *data,char *key, int count)
{
  int i;
  for(i=0; i<count; i++) 
  {
    if (i%2 == 0)
       data[i] = (data[i] >> 1) + (key[i] << 1);
    else
        data[i] = (data[i] << 1) + (key[i] >> 1);
  }
}