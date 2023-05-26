// IMPORTANT: you must include the following line in all your C files
#include <lcom/lcf.h>

#include <lcom/lab5.h>

#include <stdint.h>
#include <stdio.h>

// Any header files included below this line should have been created by you
#include "graphics.h"
#include "keyboard.h"


int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need it]
  lcf_trace_calls("/home/lcom/labs/lab5/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/lab5/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}
extern vbe_mode_info_t mode_info;
extern uint8_t scancode;
extern int error;
int(video_test_init)(uint16_t mode, uint8_t delay) {
  /* To be completed */
  if(set_frame_buffer(mode)) return 1;
  if(set_graphic_mode(mode))return 1;

  sleep(delay);
  if(vg_exit()) return 1;
  return 0;
}

int(video_test_rectangle)(uint16_t mode, uint16_t x, uint16_t y,
                          uint16_t width, uint16_t height, uint32_t color) {

  if(set_frame_buffer(mode)) return 1;
  if(set_graphic_mode(mode)) return 1;

  if(vg_draw_rectangle(x,y,width,height,color)!= 0) return 1;

  uint8_t irq_set,bit_no;
  message msg;
  int ipc_status,r;
  uint8_t array[2];
  if (keyboard_subscribe_int(&bit_no)!=0){
    return 1;
  }
  irq_set = BIT(bit_no);
  while(scancode != ESC){
     if (( r = driver_receive(ANY, &msg, &ipc_status)) != 0 ) { 
         printf("driver_receive failed with: %d", r);
        continue;
    }
    if (is_ipc_notify(ipc_status)) { /* received notification */
        switch (_ENDPOINT_P(msg.m_source)) {
            case HARDWARE: /* hardware interrupt notification */				
                if (msg.m_notify.interrupts & irq_set) { /* subscribed interrupt */
                    kbd_ih(); 
                    if(!error){
                      if (scancode != SIZE){
                        array[0] = scancode;
                        
                      }
                      else {
                        array[1]= scancode;
                      }
                    }
                    
                }
                break;
            default:
                break; /* no other notifications expected: do nothing */	
        }
    } else { /* received a standard message, not a notification */
        /* no standard messages expected: do nothing */
    }
  
 }
  if (keyboard_unsubscribe_int() != 0) return 1 ;
  if(vg_exit()) return 1;
  return 0;
}

int(video_test_pattern)(uint16_t mode, uint8_t no_rectangles, uint32_t first, uint8_t step) {
  /* To be completed */
  if(set_frame_buffer(mode)) return 1;
  if(set_graphic_mode(mode)) return 1;

  unsigned vertical = mode_info.YResolution / no_rectangles;
  unsigned horizontal = mode_info.XResolution / no_rectangles;

  for (unsigned i = 0 ; i < no_rectangles ; i++) {
    for (unsigned j = 0 ; j < no_rectangles ; j++) {

      uint32_t color;

      if (mode_info.MemoryModel == 0x06) {
        color = direct_mode(j,i,step,first);

      } else {
        color = indexed_mode(j, i, step, first, no_rectangles);
      }

      if (vg_draw_rectangle(j * horizontal, i * vertical, horizontal, vertical, color)) return 1;
    }
  }


  uint8_t irq_set,bit_no;
  message msg;
  int ipc_status,r;
  uint8_t array[2];
  if (keyboard_subscribe_int(&bit_no)!=0){
    return 1;
  }
  irq_set = BIT(bit_no);
  while(scancode != ESC){
     if (( r = driver_receive(ANY, &msg, &ipc_status)) != 0 ) { 
         printf("driver_receive failed with: %d", r);
        continue;
    }
    if (is_ipc_notify(ipc_status)) { /* received notification */
        switch (_ENDPOINT_P(msg.m_source)) {
            case HARDWARE: /* hardware interrupt notification */				
                if (msg.m_notify.interrupts & irq_set) { /* subscribed interrupt */
                    kbd_ih(); 
                    if(!error){
                      if (scancode != SIZE){
                        array[0] = scancode;
                      }
                      else {
                        array[1]= scancode;
                      }
                    }
                    
                }
                break;
            default:
                break; /* no other notifications expected: do nothing */	
        }
    } else { /* received a standard message, not a notification */
        /* no standard messages expected: do nothing */
    }
  
 }
  if (keyboard_unsubscribe_int() != 0) return 1 ;
  if(vg_exit()) return 1;
  return 0;
}

int(video_test_xpm)(xpm_map_t xpm, uint16_t x, uint16_t y) {
  /* To be completed */
  printf("%s(%8p, %u, %u): under construction\n", __func__, xpm, x, y);

  return 1;
}

int(video_test_move)(xpm_map_t xpm, uint16_t xi, uint16_t yi, uint16_t xf, uint16_t yf,
                     int16_t speed, uint8_t fr_rate) {
  /* To be completed */
  printf("%s(%8p, %u, %u, %u, %u, %d, %u): under construction\n",
         __func__, xpm, xi, yi, xf, yf, speed, fr_rate);

  return 1;
}

int(video_test_controller)() {
  /* To be completed */
  printf("%s(): under construction\n", __func__);

  return 1;
}
