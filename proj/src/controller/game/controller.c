#include "controller.h"

bool is_in_map(Sprite *item) {
  return item->x + item->width[item->i] <= 15 + MAP_WIDTH && item->x >= 25 &&
         item->y + item->height[item->i] <= 20 + MAP_HEIGHT && item->y >= 25;
}

bool collide(Sprite *s1, Sprite *s2) {
  if (s1 == s2)
    return false;

  uint16_t left = (s1->x > s2->x) ? s1->x : s2->x;
  uint16_t right = (s1->x + s1->width[s1->i] < s2->x + s2->width[s2->i]) ? s1->x + s1->width[s1->i] : s2->x + s2->width[s2->i];
  uint16_t top = (s1->y > s2->y) ? s1->y : s2->y;
  uint16_t bottom = (s1->y + s1->height[s1->i] < s2->y + s2->height[s2->i]) ? s1->y + s1->height[s1->i] : s2->y + s2->height[s2->i];

  for (int y = top; y < bottom; ++y) {
    for (int x = left; x < right; ++x) {
      uint32_t s1_color = s1->pixmap_array[s1->i][x - s1->x + (y - s1->y) * s1->width[s1->i]];
      uint32_t s2_color = s2->pixmap_array[s2->i][x - s2->x + (y - s2->y) * s2->width[s2->i]];
      if (s1_color != TRANSPARENT && s2_color != TRANSPARENT) {
        return true;
      }
    }
  }

  return false;
}

void map_set_up(int level) {
  panda_state = INACTIVE;
  panda->i = big_plank->i = little_plank->i = counter = seconds = minutes = 0;

  switch (level) {
    case 0:
      setPos(panda, 40, 100);
      setPos(home, 370, 50);
      setPos(bamboo, 370, 350);

      break;
    case 1:
      setPos(panda, 40, 100);
      setPos(home, 530, 330);
      setPos(bamboo, 580, 90);
      break;
    case 2:
      setPos(panda, 230, 100);
      setPos(home, 405, 307);
      setPos(bamboo, 320, 310);
      break;
  }

  setPos(little_block, 282, 520);
  setPos(big_block, 364, 512);
  setPos(little_plank, 455, 535);
  setPos(big_plank, 582, 535);
  isRightPressed = isLeftPressed = false;

  map->i = lava->i = level;
}

bool above(Sprite *item) {

  if (item->height[0] != 455 && panda->y + panda->height[panda->i] >= item->y + 1)
    return false;
  uint16_t feet = panda->height[panda->i] - 1;

  uint16_t yAbs = panda->y + feet;
  uint16_t yPos = yAbs - item->y;

  for (int i = 0; i < panda->width[panda->i]; i++) {
    uint16_t xAbs = panda->x + i;
    uint16_t xPos = xAbs - item->x;

    // Check if the positions are within valid bounds
    if (yPos < item->height[item->i] && xPos < item->width[item->i]) {
      uint32_t panda_color = panda->pixmap_array[panda->i][i + (feet * panda->width[panda->i])];
      uint32_t item_color = item->pixmap_array[item->i][xPos + (yPos * item->width[item->i])];

      if (panda_color != TRANSPARENT && item_color != TRANSPARENT) {
        return true;
      }
    }
  }
  return false;
}

void move_left() {
  panda->x -= XSPEED;
}

void move_right() {
  panda->x += XSPEED;
}

void jump(uint32_t time, uint32_t y) {
  panda->y = y - YSPEED * time + time * time * (GRAVITY) / 2;
  panda->yspeed = YSPEED - GRAVITY * time;
}

void fall(uint32_t time, uint32_t y) {
  panda->y = y + time * time * (GRAVITY) / 2;
  panda->yspeed = GRAVITY * time;
}

bool above_any_item() {
  return above(map);
}

bool collide_with_items() {

  if (collide(panda, little_block)) {
    collide_item = little_block;
    return true;
  }
  else if (collide(panda, little_plank)) {
    collide_item = little_plank;
    return true;
  }
  else if (collide(panda, big_plank)) {
    collide_item = big_plank;
    return true;
  }
  else if (collide(panda, big_block)) {
    collide_item = big_block;
    return true;
  }
  if (collide(panda, map)) {
    collide_item = map;
    return true;
  }
  return false;
}
bool hit_floor() {
  return panda->y + panda->height[panda->i] > 20 + MAP_HEIGHT;
}
void handle_boundary_conditions() {
  if (panda->x < 25)
    panda->x = 25;
  if (panda->y < 25)
    panda->y = 25;
  if (panda->x + panda->width[panda->i] > 15 + MAP_WIDTH)
    panda->x = 15 + MAP_WIDTH - panda->width[panda->i];
  if (panda->y + panda->height[panda->i] >= 20 + MAP_HEIGHT)
    panda->y = 20 + MAP_HEIGHT - panda->height[panda->i];
}

void fix_collision() {
  if (!above(collide_item)) {
    if (isRightPressed) {
      if (collide_item->height[0] != 455 && panda->x < collide_item->x)
        while (collide(panda, collide_item)) {
          panda->x--;
        }

      else if (collide_item->height[0] == 455)
        while (collide(panda, collide_item)) {
          panda->x--;
        }
      else {
        move_left();
      }
    }
    else {
      if (collide_item->height[0] != 455 && panda->x + panda->width[panda->i] > collide_item->x + collide_item->width[collide_item->i])
        while (collide(panda, collide_item)) {
          panda->x++;
        }
      else if (collide_item->height[0] == 455)
        while (collide(panda, collide_item)) {
          panda->x++;
        }
      else {
        move_right();
      }
    }
  }
}

void fix_jump_collision() {
  while (collide(panda, collide_item))
    panda->y++;
}

void fix_fall_collision() {
  while (collide(panda, collide_item))
    panda->y--;
}

void update_panda_animation() {

  if (panda_state == JUMP) {
    panda->i = (isRightPressed) ? 6 : 7;
  }
  else {
    if (isRightPressed) {
      if (panda->i > 2)
        panda->i = 0;
      panda->i = (panda->i + 1) % 3;
    }
    else {
      if (panda->i < 3)
        panda->i = 3;
      panda->i = (panda->i + 1) % 3 + 3;
    }
  }
}

bool is_selected_item() {
  if (select_item(little_block) && !is_in_map(little_block))
    item = little_block;
  if (select_item(big_block) && !is_in_map(big_block))
    item = big_block;
  if (select_item(little_plank) && !is_in_map(little_plank))
    item = little_plank;
  if (select_item(big_plank) && !is_in_map(big_plank))
    item = big_plank;

  if (item != NULL) {
    off_x = cursor->x - item->x;
    off_y = cursor->y - item->y;
    item_x = item->x;
    item_y = item->y;
    return true;
  }
  return false;
}

void update_item_pos() {
  item->x = cursor->x - off_x;
  item->y = cursor->y - off_y;
}

void check_item_pos() {

  if (!is_in_map(item) || collide(item, panda) ||
      collide(item, little_block) || collide(item, big_block) ||
      collide(item, little_plank) || collide(item, big_plank) ||
      collide(item, map) || collide(item, lava) ||
      collide(item, home) || collide(item, bamboo)) {
    item->x = item_x;
    item->y = item_y;
    item->i = 0;
  }

  item = NULL;
}

void update_item_animation() {
  if (scancode == R_KEY)
    item->i = (item->i + 1) % item->num_pixmaps;
  else
    item->i = (item->i - 1 + item->num_pixmaps) % item->num_pixmaps;
}

void update_inventory() {
  setPos(bamboo, 190, 515);
}

bool select_item(Sprite *item) {
  return cursor->x >= item->x && cursor->x <= item->x + item->width[item->i] &&
         cursor->y >= item->y && cursor->y <= item->y + item->height[item->i];
}
