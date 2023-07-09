void Decrypt(unsigned char *data, char *key, int count)
{
  int i;
  for(i=0; i<count; i++)
  {
    if(i%2 == 0)
       data[i] = (data[i] - (key[i] << 1)) << 1;
    else
       data[i] = (data[i] - (key[i] >> 1)) >> 1;
  }
}