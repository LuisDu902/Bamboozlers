#include "viewer.h"

extern Menu_state menu_state;
extern Level_state level_state;

extern int minutes;
extern int seconds;
extern int counter;

extern Item_state item_state;

int(draw_sprite)(Sprite *sprite)
{
    uint32_t color;
    uint16_t width = sprite->width[sprite->i], height = sprite->height[sprite->i], x = sprite->x, y = sprite->y;

    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            color = sprite->pixmap_array[sprite->i][col + row * width];
            if (color == TRANSPARENT)
                continue;
            if (vg_draw_pixel(x + col, y + row, color))
                return 1;
        }
    }

    return 0;
}

int(draw_menu)()
{
    switch (menu_state)
    {
    case MENU:
        draw_main_menu();
        break;
    case LEVEL_SELECTION:
        draw_level_select_menu();
        break;
    case INSTRUCTIONS:
        draw_instructions_menu();
        break;
    case GAME:
        draw_game_menu();
        break;
    case GAME_OVER:
        draw_game_over_menu();
        break;
    case EXIT:
        return 0;
    }
    return draw_cursor();
}

int(draw_cursor)()
{
    switch (menu_state)
    {
    case MENU:
        return draw_menu_cursor();
    case GAME:
        return draw_game_cursor();
    case LEVEL_SELECTION:
        return draw_level_cursor();
       
    case INSTRUCTIONS:
        cursor->i = 0;
        return draw_sprite(cursor);

    case GAME_OVER:
        return draw_game_over_cursor();
    case EXIT:
        return 0;
    }

    return 0;
}

/* GAME OVER MENU */
int(draw_game_over_menu)()
{

    if (draw_sprite(game_over))
        return 1;
    if (draw_sprite(play_again))
        return 1;
    if (draw_sprite(game_exit))
        return 1;

    return 0;
}

int(draw_game_over_cursor)()
{
    if (select_item(play_again))
    {
        cursor->i = play_again->i = 1;
        game_exit->i = 0;
    }
    else if (select_item(game_exit))
    {
        cursor->i = game_exit->i = 1;
        play_again->i = 0;
    }
    else
    {
        cursor->i = game_exit->i = play_again->i = 0;
    }
    return draw_sprite(cursor);
}

/* INSTRUCTIONS MENU */
int (draw_instructions_menu)()
{    
    
    if (draw_sprite(instructions_text_1)) return 1;
    if (draw_sprite(instructions_text_2)) return 1;
    if (draw_sprite(instructions_text_3)) return 1;
    if (draw_sprite(instructions_text_4)) return 1;
    if (draw_sprite(instructions_text_5)) return 1;
    if (draw_sprite(instructions_text_6)) return 1;
    return 0;
}


/* LEVEL SELECTION MENU */

int(draw_level_select_menu)()
{
    if (draw_sprite(level_one))
        return 1;
    if (draw_sprite(level_two))
        return 1;
    if (draw_sprite(level_three))
        return 1;

    return 0;
}

int(draw_level_cursor)()
{
    if (select_item(level_one))
    {
        level_one->i = cursor->i = 1;
        level_two->i = (level_state == LEVEL_ONE) ? 0 : 2;
        level_three->i = (level_state == LEVEL_THREE) ? 2 : 0;
    }
    else if (select_item(level_two) && level_state != LEVEL_ONE)
    {
        level_two->i = cursor->i = 1;
        level_one->i = 0;
        level_three->i = (level_state == LEVEL_TWO) ? 0 : 2;
    }
    else if (select_item(level_three) && level_state == LEVEL_THREE)
    {
        level_three->i = cursor->i = 1;
        level_one->i = 0;
        level_two->i = 2;
    }
    else
    {
        cursor->i = level_one->i = 0;
        level_two->i = (level_state != LEVEL_ONE) ? 2 : 0;
        level_three->i = (level_state == LEVEL_THREE) ? 2 : 0;
    }
    return draw_sprite(cursor);
}

/* MAIN MENU */
int(draw_main_menu)()
{
    if (draw_sprite(logo)) return 1;
    if (draw_sprite(instructions))
        return vg_exit();
    if (draw_sprite(levels)) return vg_exit();
    return 0;
}

int(draw_menu_cursor)()
{
    if (select_item(levels))
    {
        cursor->i = levels->i = 1;
        instructions->i = 0;
    }
    else if (select_item(instructions))
    {
        cursor->i = instructions->i = 1;
        levels->i = 0;
    }
    else
    {
        cursor->i = instructions->i = levels->i = 0;
    }
    return draw_sprite(cursor);
}

/* GAME MENU */

int(draw_game_menu)()
{
    if (draw_map())
        return 1;
    if (draw_inventory())
        return 1;
    if (draw_sprite(background))
        return 1;
    if (draw_sprite(map))
        return 1;
    if (draw_sprite(lava))
        return 1;
    if (draw_sprite(bamboo))
        return 1;
    if (draw_timer())
        return 1;
    if (draw_sprite(home))
        return 1;
    if (draw_sprite(panda))
        return 1;

    if (draw_sprite(little_block))
        return 1;
    if (draw_sprite(big_block))
        return 1;
    if (draw_sprite(little_plank))
        return 1;
    if (draw_sprite(big_plank))
        return 1;
    return 0;
}

int(draw_map)()
{
    if (vg_draw_rectangle(20, 20, MAP_WIDTH, BORDER_WIDTH, 0xFFFFFF))
        return 1;
    if (vg_draw_rectangle(20, 480, MAP_WIDTH, BORDER_WIDTH, 0xFFFFFF))
        return 1;
    if (vg_draw_rectangle(20, 20, BORDER_WIDTH, MAP_HEIGHT, 0xFFFFFF))
        return 1;
    if (vg_draw_rectangle(775, 20, BORDER_WIDTH, MAP_HEIGHT, 0xFFFFFF))
        return 1;
    return 0;
}

int(draw_inventory)()
{
    if (draw_container(570, 500, 210))
        return 1;
    if (draw_container(440, 500, 120))
        return 1;
    if (draw_container(350, 500, 80))
        return 1;
    if (draw_container(260, 500, 80))
        return 1;
    if (draw_container(170, 500, 80))
        return 1;

    return 0;
}

int(draw_container)(uint16_t x, uint16_t y, uint16_t width)
{
    if (vg_draw_rectangle(x, y, width, 80, GREY))
        return 1;

    if (vg_draw_rectangle(x + 7, y + 7, 10, 2, 0xAFABAB))
        return 1;
    if (vg_draw_rectangle(x + 7, y + 7, 2, 10, 0xAFABAB))
        return 1;

    if (vg_draw_rectangle(x + width - 15, y + 7, 10, 2, 0xAFABAB))
        return 1;
    if (vg_draw_rectangle(x + width - 7, y + 7, 2, 10, 0xAFABAB))
        return 1;

    if (vg_draw_rectangle(x + 7, y + 71, 10, 2, 0xAFABAB))
        return 1;
    if (vg_draw_rectangle(x + 7, y + 63, 2, 10, 0xAFABAB))
        return 1;

    if (vg_draw_rectangle(x + width - 15, y + 71, 10, 2, 0xAFABAB))
        return 1;
    if (vg_draw_rectangle(x + width - 7, y + 63, 2, 10, 0xAFABAB))
        return 1;

    return 0;
}

int(draw_timer)()
{

    if (counter % 30 == 0)
    {
        seconds++;
        if (seconds % 60 == 0)
        {
            minutes++;
            seconds = 0;
        }
    }
    timer[0]->i = minutes / 10;
    timer[1]->i = minutes % 10;
    timer[2]->i = seconds / 10;
    timer[3]->i = seconds % 10;

    if (vg_draw_rectangle(20, 500, 140, 80, GREY))
        return 1;
    if (vg_draw_rectangle(87, 532, 4, 4, 0xFFFFFF))
        return 1;
    if (vg_draw_rectangle(87, 542, 4, 4, 0xFFFFFF))
        return 1;
    for (int i = 0; i < 4; i++)
    {
        if (draw_sprite(timer[i]))
            return 1;
    }
    return 0;
}

int draw_game_cursor()
{
    if (item_state == INIT)
    {
        if ((select_item(little_block) && !is_in_map(little_block)) ||
            (select_item(little_plank) && !is_in_map(little_plank)) ||
            (select_item(big_block) && !is_in_map(big_block)) ||
            (select_item(big_plank) && !is_in_map(big_plank)))
        {
            cursor->i = 1;
        }
        else
        {
            cursor->i = 0;
        }
    }
    else if (item_state == DRAG)
    {
        cursor->i = 2;
    }
    return draw_sprite(cursor);
}
