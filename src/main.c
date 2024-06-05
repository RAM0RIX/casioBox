#include <gint/display.h>
#include <gint/keyboard.h>
#include <gint/keycodes.h>
#include "box.h"

int main(void)
{
	// extern bopti_image_t img_dragon;
	extern font_t font;
        dfont(&font);
	struct tblr borders = {3, 3, 3, 3};
	bHandle box1 = createBox(BOX_TYPE_NULL, 0, 0, BOX_MAX_WIDTH, BOX_MAX_HEIGHT, borders, "", NULL, 0);
	
	for(;;)
	{
            dclear(C_WHITE);
	    drawBox(box1);
	    dtext(9, 9, C_BLACK,"RAM0RIX X");
            dupdate();
	    if (getkey().key == KEY_EXIT ) break;
	}

	return 1;
}
