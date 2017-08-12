int cursor_x = 0, cursor_y = 0;

void kprint(char c, char attr, int x, int y)
{
	char *fb = (char *) 0x000B8000;		// frame buffer starting address

	int offset = (y * MAX_COLS + x) * 2;

	fb[offset] = c;
	fb[offset + 1] = attr;

	// Update the cursor
	fb_move_cursor(x+1, y);
	cursor_x = x+1;
	cursor_y = y;
}

// Write a string to the video memory
void kprint_string(char msg[], char attr, int x, int y)
{
	while(*msg != '\0')
	{
		if(x>MAX_COLS)
		{
			x = 0;
			y++;
		}

		if(*msg != '\n')
		{
			kprint(*msg, attr, x, y);
			x++;
		}
		else
		{
			x = 0;
			y++;

			// Update the cursor
			fb_move_cursor(x, y);
			cursor_x = x;
			cursor_y = y;
		}

		msg++;
	}
}

// Draw a box
void draw_box(int x, int y, int width, int height, char attr)
{
	// ╔ -> 201
	// ╗ -> 187

	// ║ -> 186

	// ╚ -> 200
	// ╝ -> 188
	// ═ -> 205

	int i;

	kprint(201, attr, x, y);	// top left corner
	for(i=1; i<width; i++)
		kprint(205, attr, x+i, y);	// top border
	kprint(187, attr, x+width, y);	// top right corner

	// left and right border
	for(i=1; i<height; i++)
	{
		kprint(186, attr, x, y+i);
		kprint(186, attr, x+width, y+i);
	}

	kprint(200, attr, x, y+height);		// bottom left corner
	for(i=1; i<width; i++)
		kprint(205, attr, x+i, y+height);	// bottom border

	kprint(188, attr, x+width, y+height);	// bottom right corner

}

// Writes a given string starting from the cursor's position
void write(char msg[], char attr)
{
	kprint_string(msg, attr, cursor_x, cursor_y);
}

// Fills the screen with blanks and moves the cursor to the beggining of the video memory
void clear_screen()
{
	int i, j;

	for(i=0; i<MAX_COLS; i++)
		for(j=0; j<MAX_ROWS; j++)
			kprint(' ', WHITE_ON_BLACK, i, j);


	// move the cursor
	fb_move_cursor(0, 0);

	// update the global variables that keep track of the cursor
	cursor_x = 0;
	cursor_y = 0;
}