#include <lcom/lcf.h>
#include "controllers/timer/timer.h"
#include "controllers/video/graphics.h"
#include "controllers/keyboard/keyboard.h"
#include "controllers/mouse/mouse.h"


int (main)(int argc, char *argv[]) {
    lcf_set_language("EN-US");
    lcf_trace_calls("/home/lcom/labs/project/debug/trace.txt");
    lcf_log_output("/home/lcom/labs/project/debug/output.txt");
    if (lcf_start(argc, argv)) return 1;
    lcf_cleanup();
    return 0;
}
extern xpm_map_t xpm;
extern uint8_t scancode;

int (proj_main_loop)(int argc, char *argv[]) {
  
    if (map_vram(0x105) != 0) return 1;

    if (set_graphic_mode(0x105) != 0) return 1;

    vbe_mode_info_t mode_info;

    memset(&mode_info, 0, sizeof(mode_info));
    if (vbe_get_mode_info(0x105, &mode_info) != 0)
        return 1;

    uint16_t x = 20;
    uint16_t y = 20;
    uint8_t color = 1;
    vg_draw_rectangle(x,y,20,20,color);

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
                y -= 20;
            }
            else if (scancode == ARROW_LEFT){
                x -= 20;
            }
            else if (scancode == ARROW_DOWN){ 
                y += 20;
            }
            else if (scancode == ARROW_RIGHT){ 
                x += 20;
            }
             vg_draw_rectangle(x,y,20,20,color++);
             if (color == 64) color = 1;
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

  
