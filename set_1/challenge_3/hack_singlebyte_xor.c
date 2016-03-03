#include <string.h>
#include <stdio.h>
#include "werror.h"

int main(int argc, unsigned char* argv[])
{
  if( argc < 1 )
    {
      werror("no input file");
      return -1;
    }
  
