#include <string.h>
#include <stdio.h>

#define werror(a) printf("%s:%s(): %s\n", __FILE__, __FUNCTION__, a)

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

unsigned char base2char(unsigned char c)
{
  if(c < 0x1a)
    {
      return 'A' + c;
    } else
    if(c >= 0x1a && c < 0x34)
      {
	return 'a' + c - 0x1a;
      } else
      if(c >= 0x34 && c < 0x3e)
	{
	  return '0' + c - 0x34;
	} else
	if (c == 0x3e)
	  {
	    return '+';
	  } else
	  if (c == 0x3f)
	    {
	      return '/';
	    }     
  return 0;
}


size_t hex2base(unsigned char* src, unsigned char* dst, size_t len)
{
  int hc,bc;
  
  for(hc=bc=0; hc < len; hc+=3,bc+=4)
    {
      dst[bc + 0] = src[hc] >> 2;
      dst[bc + 1] = ((src[hc] << 4) & 0x3f) | src[hc+1] >> 4;
      dst[bc + 2] = ((src[hc+1] << 2) & 0x3f) | src[hc+2] >> 6;
      dst[bc + 3] = src[hc+2] & 0x3f;
    }
  return bc;
}

size_t base2str(unsigned char* src, size_t len)
{
  for(--len; len >= 0; len--)
    {
      src[len] = base2char(src[len]);
      printf("%c \n",src[len]);
    }
  return 0;
}


int main()
{
  unsigned char src[] = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d";
  unsigned char dst[strlen(src)/2];
  size_t len;

  printf("%s\n",src);
  
  if(!unhex(src, dst, strlen(src)))
    {
      return -1;
    }

  len = hex2base(dst, src, strlen(src)/2);
  base2str(src,len);
  printf("%s\n",src);
  return 0;
}	
