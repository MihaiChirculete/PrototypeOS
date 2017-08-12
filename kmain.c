#include "ports/ports.c"
#include "utils/str_utils.c"
#include "drivers/screen.h"
#include "drivers/screen.c"

void kmain()
{	

	/*            Messages to be printed on the screen               */
	char os_msg1[] = {201, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 187, '\0'};
	char os_msg2[] = {186, 'P','r', 'o', 't', 'o', 't', 'y', 'p', 'e', ' ','O', 'S', 186,'\0'};
	char os_msg3[] = {200, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 188, '\n', '\0'};

	char kernel_loaded[] = "Kernel successfully loaded!\n";
	/***************************************************************************************************/

	int center = 40 - strlen(os_msg2)/2;


	clear_screen();	// Clear the screen

	// Display the messages
	kprint_string(os_msg1, WHITE_ON_BLACK, center, 0);
	kprint_string(os_msg2, WHITE_ON_BLACK, center, 1);
	kprint_string(os_msg3, WHITE_ON_BLACK, center, 2);

	write(kernel_loaded, 0x0f);
	
}