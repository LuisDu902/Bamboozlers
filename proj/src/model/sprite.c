#include <lcom/lcf.h>
#include "sprite.h"


Sprite *create_sprite_xpm(xpm_map_t sprite, int x, int y){

  Sprite *sp = (Sprite *) malloc (sizeof(Sprite));
  if( sp == NULL ) return NULL;

  sp->x = x;
  sp->y = y;
  sp->xspeed = 0;
  sp->yspeed = 0;

  xpm_image_t img;
  sp->pixmap = (uint32_t *) xpm_load(sprite, XPM_8_8_8_8, &img);
  
  if( sp->pixmap == NULL ) {
    free(sp);
    return NULL;
  }

  sp->height = img.height;
  sp->width = img.width;

  return sp;

}

void destroy_sprite(Sprite *sprite) {
    if (sprite == NULL) return;
    if (sprite->pixmap) free(sprite->pixmap);
    free(sprite);
    sprite = NULL;
}
