#include <string.h>
#include <stdio.h>
#include "werror.h"

static unsigned long int* count_score(unsigned char* str, unsigned long int* arr)
{
  size_t i, len;

  len = strlen(str);
  
  for(i=0; i < len; i++)
    {
      arr[str[i]]++;
    }
  return arr;
}

void fill_arr_zero(unsigned long int* arr, size_t len)
{
  size_t i;
  for(i=0; i < len; i++)
    {
      arr[i]=0;
    }
}

void printarr(unsigned long int* arr, size_t len)
{
  char i;
  for(i=0; i<len;i++)
    {
      printf("[%d] = \t %lu \t \\\\ %c\n", i, arr[i], i);
    }
}

int main(int argc, unsigned char* argv[])
{
 unsigned long int arr[256];
#if 0
  if( argc < 1 )
    {
      werror("no input file");
      return -1;
    }
#endif
  
  fill_arr_zero(arr, 256);
  count_score("abba",arr);
  printarr(arr, 256);
}
