#include <lcom/lcf.h>
#include "controller/timer/timer.h"
#include "controller/video/graphics.h"
#include "controller/keyboard/keyboard.h"
#include "controller/mouse/mouse.h"
#include "controller/KBC/KBC.h"
#include "model/model.h"
#include "model/sprite.h"
#include "viewer/menu_viewer.h"
#include "viewer/game_viewer.h"
#include "states/state.h"

extern Menu_state menu_state;
uint32_t timer_mask, keyboard_mask, mouse_mask;

int (main)(int argc, char *argv[]) {
    lcf_set_language("EN-US");
    lcf_trace_calls("/home/lcom/labs/src/debug/trace.txt");
    lcf_log_output("/home/lcom/labs/src/debug/output.txt");
    if (lcf_start(argc, argv)) return 1;
    lcf_cleanup();
    return 0;
}

int init() {

    if (timer_set_frequency(0, 30) ) return 1;

    if (set_main_buffer(VBE_DIRECT_600p) ) return 1;
    set_drawing_buffer();

    if (set_graphic_mode(VBE_DIRECT_600p) ) return 1;

    create_sprites();

    if (timer_subscribe_interrupt(&timer_mask) ) return 1;
    if (keyboard_subscribe_int(&keyboard_mask) ) return 1;
    if (mouse_subscribe_int(&mouse_mask) ) return 1;

    if (enable_data_reporting() ) return 1;

    return 0;
}


int cleanup() {

    if (vg_exit() ) return 1;

    destroy_sprites();

    if (timer_unsubscribe_int() ) return 1;
    if (keyboard_unsubscribe_int() ) return 1;
    if (mouse_unsubscribe_int() ) return 1;

    if (disable_data_reporting() ) return 1;

    return 0;
}


int (proj_main_loop)(int argc, char *argv[]) {
  
    if (init() ) return 1;

    draw_menu();

    int ipc_status;
    message msg;
    while (menu_state != EXIT) {
        if (driver_receive(ANY, &msg, &ipc_status) ) {
            printf("Error");
            continue;
        }
        if (is_ipc_notify(ipc_status)) {
            switch(_ENDPOINT_P(msg.m_source)) {
                case HARDWARE: 
                    if (msg.m_notify.interrupts & timer_mask) update_timer_state();
                    if (msg.m_notify.interrupts & keyboard_mask) update_keyboard_state();
                    if (msg.m_notify.interrupts & mouse_mask)  update_mouse_state();
            }
        }
    }
    
    if (cleanup() ) return 1;

    return 0;
}

  
