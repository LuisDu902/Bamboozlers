#include <lcom/lcf.h>
#include "controllers/timer/timer.h"
#include "controllers/video/graphics.h"
#include "controllers/keyboard/keyboard.h"
#include "controllers/mouse/mouse.h"
#include "model/model.h"
#include "model/sprite.h"
#include "view/view.h"

int (main)(int argc, char *argv[]) {
    lcf_set_language("EN-US");
    lcf_trace_calls("/home/lcom/labs/project/debug/trace.txt");
    lcf_log_output("/home/lcom/labs/project/debug/output.txt");
    if (lcf_start(argc, argv)) return 1;
    lcf_cleanup();
    return 0;
}
extern Sprite *mouse;
extern uint8_t scancode;

int (proj_main_loop)(int argc, char *argv[]) {
  
    if (map_vram(VBE_DIRECT_600p) != 0) return 1;

    if (set_graphic_mode(VBE_DIRECT_600p) != 0) return 1;

    vbe_mode_info_t mode_info;

    memset(&mode_info, 0, sizeof(mode_info));
    if (vbe_get_mode_info(VBE_DIRECT_600p, &mode_info) != 0)
        return 1;

    create_sprites();

    if (vg_draw_sprite(mouse) != 0) return 1;

    int ipc_status, r;
    message msg;
    uint32_t kbd_irq_set;

    if (keyboard_subscribe_int(&kbd_irq_set) != 0) return 1;

    while (scancode != ESC_BREAK){ /* You may want to use a different condition */
    /* Get a request message. */
    if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0){
        printf("driver_receive failed with: %d", r);
        continue;
    }

    if (is_ipc_notify(ipc_status))
    { /* received notification */
        switch (_ENDPOINT_P(msg.m_source)){
        case HARDWARE: /* hardware interrupt notification */
        if (msg.m_notify.interrupts & kbd_irq_set){
            read_scancode();
            
            if (scancode == ARROW_UP){ 
                mouse->y -= 20;
                if (mouse->y < 0) mouse->y = 0;
                if (vg_clear() != 0) return 1;
                if (vg_draw_sprite(mouse) != 0) return 1;
            }
            else if (scancode == ARROW_LEFT){
                mouse->x -= 20;
                if (mouse->x < 0) mouse->x = 0;
                if (vg_clear() != 0) return 1;
                if (vg_draw_sprite(mouse) != 0) return 1;
            }
            else if (scancode == ARROW_DOWN){ 
                mouse->y += 20;
                if (mouse->y > mode_info.YResolution - mouse->height) mouse->y = mode_info.YResolution - mouse->height;
                if (vg_clear() != 0) return 1;
                if (vg_draw_sprite(mouse) != 0) return 1;
            }
            else if (scancode == ARROW_RIGHT){ 
                mouse->x += 20;
                if (mouse->x > mode_info.XResolution - mouse->width) mouse->x = mode_info.XResolution - mouse->width;
                if (vg_clear() != 0) return 1;
                if (vg_draw_sprite(mouse) != 0) return 1;
            }
            
        }
        break;
        default:
        break; /* no other notifications expected: do nothing */
        }
    }
    }

    if (keyboard_unsubscribe_int() != 0) return 1;

    if (vg_exit()) return 1;

    return 0;
}

  
