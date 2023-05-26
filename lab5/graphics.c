#include <lcom/lcf.h>


#include <stdint.h>
#include <stdio.h>
#include "graphics.h"


vbe_mode_info_t mode_info; 
// apontador para o início da memória virtual 
uint8_t *frame_buffer;

/* função de mapeamento da VRAM */
int (set_frame_buffer)(uint16_t mode){

  // retirar informação sobre o @mode
  memset(&mode_info, 0, sizeof(mode_info));
  if(vbe_get_mode_info(mode, &mode_info)) return 1;

  // cálculo do tamanho do frame buffer, em bytes
  uint8_t bytes_per_pixel = (mode_info.BitsPerPixel + 7) / 8;
  unsigned int frame_size = mode_info.XResolution * mode_info.YResolution * bytes_per_pixel;
  
  // preenchimento dos endereços físicos
  struct minix_mem_range physic_addresses;
  physic_addresses.mr_base = mode_info.PhysBasePtr; // início físico do buffer
  physic_addresses.mr_limit = physic_addresses.mr_base + frame_size; // fim físico do buffer
  
  // alocação física da memória necessária para o frame buffer
  if (sys_privctl(SELF, SYS_PRIV_ADD_MEM, &physic_addresses)) {
    printf("Physical memory allocation error\n");
    return 1;
  }

  // alocação virtual da memória necessária para o frame buffer
  frame_buffer = vm_map_phys(SELF, (void*) physic_addresses.mr_base, frame_size);0
  if (frame_buffer == NULL) {
    printf("Virtual memory allocation error");
    return 1;
  }

  return 0;
}
int (set_graphic_mode)(uint16_t submode) {
    reg86_t reg86;
    memset(&reg86, 0, sizeof(reg86)); // inicialização da estrutura com o valor 0 em todos os parâmetros
    reg86.intno = 0x10;               // intno é sempre 0x10      
    reg86.ah = 0x4F;                  // parte mais significativa de AX
    reg86.al = 0x02;                  // parte menos significativa de AX. 0x02 no caso de modo gráfico
    // reg86.ax = 0x4F02;             // equivamente às duas últimas instruções
    reg86.bx = submode | BIT(14);     // determinação do submodo com memória linear
    if (sys_int86(&reg86) != 0) {     // se houver algum erro, abortar a função
        printf("Set graphic mode failed\n");
        return 1;
    }
    return 0;
}
int (vg_draw_pixel)(uint8_t x, uint8_t y,uint32_t color){
    if(x > mode_info.XResolution || y > mode_info.YResolution) return 1;
    unsigned BytesPerPixel = (mode_info.BitsPerPixel + 7) / 8;

    // Índice (em bytes) da zona do píxel a colorir
    unsigned int index = (mode_info.XResolution * y + x) * BytesPerPixel;

    // A partir da zona frame_buffer[index], copia @BytesPerPixel bytes da @color
    if (memcpy(&frame_buffer[index], &color, BytesPerPixel) == NULL) return 1;

    return 0;
}
int (vg_draw_hline)(uint16_t x, uint16_t y, uint16_t len, uint32_t color){
    for(unsigned i=0;i<len;i++){
        if(vg_draw_pixel(x+i,y,color)!=0){
            vg_exit();
            return 1;
        }
    }
    return 0;
}
int (vg_draw_rectangle)(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t color){
    for(unsigned i = 0; i < height ; i++)
        if (vg_draw_hline(x, y+i, width, color) != 0) {
            vg_exit();
        return 1;
        }
  return 0;
}

int (normalize_color)(uint32_t color, uint32_t *new_color) {
  if (mode_info.BitsPerPixel == 32) {
    *new_color = color;
  } else {
    *new_color = color & (BIT(mode_info.BitsPerPixel) - 1);
  }
  return 0;
}

uint32_t (direct_mode)(unsigned j, unsigned i, uint8_t step, uint32_t first){
    uint32_t red = ((((1 << mode_info.RedMaskSize) - 1) & (first >> mode_info.RedFieldPosition)) + j * step) % (1 << mode_info.RedMaskSize);
    uint32_t green = ((((1 << mode_info.GreenMaskSize) - 1) & (first >> mode_info.GreenFieldPosition)) + i * step) % (1 << mode_info.GreenMaskSize);
    uint32_t blue = ((((1 << mode_info.BlueMaskSize) - 1) & (first >> mode_info.BlueFieldPosition)) + (i + j) * step) % (1 << mode_info.BlueMaskSize);

  return (red << mode_info.RedFieldPosition) | (green << mode_info.GreenFieldPosition) | (blue << mode_info.BlueFieldPosition);
}

uint32_t (indexed_mode)(uint16_t col, uint16_t row, uint8_t step, uint32_t first, uint8_t n) {
  return (first + (row * n + col) * step) % (1 << mode_info.BitsPerPixel);
}

