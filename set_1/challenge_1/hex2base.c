#include <stdio.h>
#include <string.h>

int str2hex(unsigned char* src)
{
  int i;
  int srclen = strlen(src);

  for(i=0; i <= srclen; i++)
    {
      if('0' <= src[i] && src[i] <= '9')
	{
	  src[i] = src[i] - '0';
	}
      else if('a' <= src[i] && src[i] <= 'f')
	{
	  src[i] = src[i] - 'a' + 10;
	}
      else if('A' <= src[i] && src[i] <= 'F')
	{
	  src[i] = src[i] - 'A' + 10;
	}
      else if(src[i] == 0) return i;
      else return -1;
    }
  return -2;
}

unsigned char base2chr(unsigned char c)
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


size_t hex2basestr(unsigned char* src, size_t len)
{
  int hc,bc;
  
  for(hc=bc=0; hc < len; hc+=3,bc+=2)
    {
      src[bc] = base2chr((src[hc + 0] << 2) | (src[hc + 1] >> 2));
      src[bc + 1] = base2chr(((src[hc + 1] << 4) & 0x30) | src[hc + 2]);  
    }
  src[bc + 1] = '\0';
  return bc;
}


int main()
{
  unsigned char src[] = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d";
  size_t len;

  printf("%s\n",src);
  if(0 > (len = str2hex(src)))
    {
      printf("chr2hex failed: return %d", len);
      return -1;
    }

  hex2basestr(src, len);
  printf("%s\n",src);
  return 0;
}	
