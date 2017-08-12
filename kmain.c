#include "ports/ports.c"
#include "drivers/screen.c"

void kmain()
{
	clear_screen();
	kprint('x', WHITE_ON_BLACK, 2, 2);
}