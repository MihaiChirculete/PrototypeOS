	/* Type definitions */
typedef unsigned long int addr;

void *memset(void *b, int c, int len)
{
  unsigned char *p = b;
  while(len > 0)
    {
      *p = c;
      p++;
      len--;
    }
  return(b);
}