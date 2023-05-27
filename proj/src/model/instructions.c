#include "instructions.h"

#include "xpm/instructions_text.xpm"


void create_instructions_sprites()
{
    xpm_map_t instructions_text_1_pixmaps[] = {(xpm_map_t)instructions_text_1_xpm};
    xpm_map_t instructions_text_2_pixmaps[] = {(xpm_map_t)instructions_text_2_xpm};
    xpm_map_t instructions_text_3_pixmaps[] = {(xpm_map_t)instructions_text_1_xpm};
    instructions_text_1 = create_sprite_xpm(instructions_text_1_pixmaps, 1, 25, 440);
    instructions_text_2 = create_sprite_xpm(instructions_text_2_pixmaps, 1, 25, 440);
    instructions_text_3 = create_sprite_xpm(instructions_text_3_pixmaps, 1, 25, 440);
}

void destroy_instructions_sprites()
{
    destroy_sprite(instructions_text);
   
}
