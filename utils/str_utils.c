// Returns the length of a string
int strlen(char msg[])
{
	int c=0;

	while(*msg != '\0')
	{
		c++;
		msg++;
	}

	return c;
}