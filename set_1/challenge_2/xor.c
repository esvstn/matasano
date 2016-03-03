#include <string.h>
#include <stdio.h>
#include "werror.h"

unsigned char char2nibble(unsigned char c)
{
  if('0' <= c && c <= '9')
    {
      return c - '0';
    }
  else if('a' <= c && c <= 'f')
    {
      return c - 'a' + 10;
    }
  else if('A' <= c && c <= 'F')
    {
      return c - 'A' + 10;
    }
  werror(" char value is not in \"0\" - \"F\" range");
  return 0x10;
}

unsigned char nibble2char(unsigned char c)
{
  if( 0x0 <= c && c <= 0x9 )
    {
      return c + '0';
    }
  else if( 0xa <= c && c <= 0xf )
    {
      return c + 'a' - 10;
    }
  return 0;
}

unsigned char* unhex(unsigned char* src, unsigned char* dst, size_t len)
{
  int i;
  unsigned char lnibble, rnibble;
  if ( len % 2 != 0 )
    {
      werror("length is not an even number");
      return 0;
    }
  
  for(i=0; i < len/2; i++)
    {
      lnibble = char2nibble(src[i*2]);
      rnibble = char2nibble(src[(i*2)+1]);

      if( (lnibble > 0xf)  || (rnibble > 0xf) ) 
	{
	  werror("input string contains incorrect chars");
	  return 0;
	}
      dst[i] = (lnibble << 4) | rnibble;
    }
  return dst;	  
}

unsigned char* hex(unsigned char *src, unsigned char *dst, size_t len)
{
  int i;
  for(i=0; i < len; i++)
    {
      dst[i*2] = nibble2char(src[i] >> 4);
      dst[(i*2)+1] = nibble2char(src[i] & 0x0f);
    }
  dst[i*2]='\0';
  return dst;
}

unsigned char* xor(unsigned char* src, unsigned char* key, size_t len, size_t keylen)
{
  int blocks,i,j;
  if (len % keylen != 0)
    {
      werror("Length is not divisible by keylen evenly");
      return 0;
    }
  blocks = len / keylen;
  for(i=0; i * keylen < len; i++)
    {
      for(j=0; j<keylen; j++)
	{
	  src[ (i * keylen) + j ] = src[ (i * keylen) + j] ^ key[j];
	}
    }
  return src;
}

int main()
{
  unsigned char src[] = "1c0111001f010100061a024b53535009181c";
  unsigned char key[] = "686974207468652062756c6c277320657965";
  unsigned char dst[strlen(src)];
  int len = 0;

  len = strlen(src);
  unhex(src, src, len);
  unhex(key, key, len);
  xor(src, key, len, len);
  hex(src, dst, len/2);
  printf("%s\n", dst);
  return 0;
}
