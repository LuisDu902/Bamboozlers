#include <lcom/lcf.h>
#include <lcom/lab3.h>
#include "i8042.h"
#include <stdbool.h>
#include <stdint.h>
#include "keyboard.h"
#include "timer.c"

extern int error; 
extern uint32_t counter;
extern uint8_t scancode;
extern uint32_t timer_counter;
int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need it]
  lcf_trace_calls("/home/lcom/labs/lab3/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/lab3/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}

int(kbd_test_scan)() {
  /* To be completed by the students */
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
                        kbd_print_scancode(!(scancode & BIT(7)),1,array);
                      }
                      else {
                        array[1]= scancode;
                        kbd_print_scancode(!(scancode & BIT(7)),2,array);
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
  kbd_print_no_sysinb(counter);
  return 0;
}

int(kbd_test_poll)() {
  /* To be completed by the students */
  uint8_t array[2];
  while( scancode != ESC ) { /* You may want to use a different condition */
    kbd_ih();
    if (!error){
      array[0] = scancode;
      if (scancode == 0xE0)
        array[1]=scancode;
      else  
        kbd_print_scancode(!(scancode & BIT(7)), 1, array);
    }
    else{
      array[1] = scancode;
      kbd_print_scancode(!(scancode & BIT(7)), 2, array);
    }
  }
  enable_int();
  kbd_print_no_sysinb(counter);
  return 1;
}

int(kbd_test_timed_scan)(uint8_t n) {
  /* To be completed by the students */
  uint8_t irq_set,bit_no;
  message msg;
  int ipc_status,r;
  uint8_t array[2];
  int timer_cnt=0;
  if (keyboard_subscribe_int(&bit_no)!=0){
    return 1;
  }
   uint8_t irq_set_timer,timer_bit_no;
  
  if(timer_subscribe_int(&timer_bit_no)!= 0) return 1;
  
  irq_set_timer = BIT(timer_bit_no);
  irq_set = BIT(bit_no);
  while(scancode != ESC && timer_cnt!=n){
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
                        kbd_print_scancode(!(scancode & BIT(7)),1,array);
                      }
                      else {
                        array[1]= scancode;
                        
                        kbd_print_scancode(!(scancode & BIT(7)),2,array);
                      }
                    }
                    timer_counter=0;
                    timer_cnt=0;
                }

                else if (msg.m_notify.interrupts & irq_set_timer) { /* subscribed interrupt */
                   timer_int_handler();
                   if (timer_counter % 60 == 0){
                    timer_print_elapsed_time();
                    timer_cnt++;
                   }
                }
                break;

            default:
                break; /* no other notifications expected: do nothing */	
        }
    } else { /* received a standard message, not a notification */
        /* no standard messages expected: do nothing */
        break;
    }
  
 }
  if (keyboard_unsubscribe_int() != 0) return 1 ;
  if(timer_unsubscribe_int()!=0)  return 1;
  kbd_print_no_sysinb(counter);
  return 0;

}

