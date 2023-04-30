#include <lcom/lcf.h>
#include "graphics.h"

int(set_graphic_mode)(uint16_t mode)
{
    reg86_t r86;

    memset(&r86, 0, sizeof(r86));

    r86.intno = 0x10;
    r86.ah = 0x4F;
    r86.al = 0x02;
    r86.bx = mode | BIT(14);

    return sys_int86(&r86);
}

int(set_text_mode)()
{
    reg86_t r86;

    memset(&r86, 0, sizeof(r86));

    r86.intno = 0x10;
    r86.ah = 0x00;
    r86.al = 0x03;

    return sys_int86(&r86);
}

int(map_vram)(uint16_t mode)
{
    struct minix_mem_range mr;
    unsigned int bytes_per_pixel;
    unsigned int frame_size; /* VRAM's size, but you can use the frame-buffer size, instead */

    /* Use VBE function 0x01 to initialize vram_base and vram_size */
    memset(&mode_info, 0, sizeof(mode_info));
    if (vbe_get_mode_info(mode, &mode_info) != 0)
        return 1;

    bytes_per_pixel = (mode_info.BitsPerPixel + 7) / 8;
    frame_size = bytes_per_pixel * mode_info.XResolution * mode_info.YResolution;

    mr.mr_base = mode_info.PhysBasePtr;
    mr.mr_limit = mr.mr_base + frame_size;

    if (sys_privctl(SELF, SYS_PRIV_ADD_MEM, &mr) != 0)
        return 1;

    frame_buffer = vm_map_phys(SELF, (void *)mr.mr_base, frame_size);

    if (frame_buffer == NULL)
        return 1;
    return 0;
}

int(vg_draw_pixel)(uint16_t x, uint16_t y, uint32_t color)
{

    unsigned int bytes_per_pixel = (mode_info.BitsPerPixel + 7) / 8;

    unsigned int index = (mode_info.XResolution * y + x) * bytes_per_pixel;

    if (memcpy(&frame_buffer[index], &color, bytes_per_pixel) == NULL) return 1;
    return 0;
}

int(vg_draw_hline)(uint16_t x, uint16_t y, uint16_t len, uint32_t color)
{
    for (int i = 0; i < len; i++)
    {
        if (vg_draw_pixel(x + i, y, color) != 0)
            return 1;
    }
    return 0;
}

int(vg_draw_rectangle)(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t color)
{
    for (int i = 0; i < height; i++)
    {
        if (vg_draw_hline(x, y + i, width, color) != 0)
            return 1;
    }
    return 0;
}

int (vg_clear)(){
    memset(&mode_info, 0, sizeof(mode_info));
    if (vbe_get_mode_info(0x105, &mode_info) != 0)
        return 1;
    int width = mode_info.XResolution;
    int height = mode_info.YResolution;

    for (int i = 0; i < width; i++){
        for (int j = 0; j < height; j++){
            if(vg_draw_pixel(i,j,0) != 0) return 1;
        }
    }
    return 0;
}

int(vg_draw_xpm)(xpm_map_t xpm, uint16_t x, uint16_t y)
{

    xpm_image_t img;
    uint8_t *map;
    map = xpm_load(xpm, XPM_8_8_8_8, &img);

    for (int col = 0; col < img.width; col++){
        for (int row = 0; row < img.height; row++){
            if (vg_draw_pixel(x + row, y + col, *map) != 0)
                return 1;
            map++;
        }
    }
    return 0;
}
