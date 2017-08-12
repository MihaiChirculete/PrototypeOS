#define MAX_ROWS 25
#define MAX_COLS 80

#define WHITE_ON_BLACK 0x0f

void kprint(char c, char attr, int x, int y)
{
	char *fb = (char *) 0x000B8000;

	int offset = (y * MAX_COLS + x) * 2;

	fb[offset] = c;
	fb[offset + 1] = attr;
}

void kprint_string(char msg[], char attr, int x, int y)
{
	while(*msg != '\0')
	{
		if(x>MAX_COLS)
		{
			x = 0;
			y++;
		}

		kprint(*msg, attr, x, y);

		x++;
		msg++;
	}
}

void clear_screen()
{
	int i, j;

	for(i=0; i<MAX_COLS; i++)
		for(j=0; j<MAX_ROWS; j++)
			kprint(' ', WHITE_ON_BLACK, i, j);

	fb_move_cursor(0x0000);
}