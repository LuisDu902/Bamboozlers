// IMPORTANT: you must include the following line in all your C files
#include <lcom/lcf.h>

#include <stdint.h>
#include <stdio.h>

// Any header files included below this line should have been created by you
#include <mouse.h>
#include <timer.h>

//GLOBAL VARS
extern bool value;
extern uint8_t curr_byte;
extern uint8_t timer_counter;
uint8_t byte_num = 0;

int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need/ it]
  lcf_trace_calls("/home/lcom/labs/g4/lab4/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/g4/lab4/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}


int (mouse_test_packet)(uint32_t cnt) {
    int ipc_status, r;
    message msg;
    uint8_t mouse_bit_no;
    struct packet pp;

    if (mouse_enable_data_report()) return 1;
    if (mouse_subscribe_int(&mouse_bit_no)) return 1;

    while(cnt > 0) {
      if ( (r = driver_receive(ANY, &msg, &ipc_status)) != 0 ) { 
        printf("driver_receive failed with: %d", r);
        continue;
      }
      if (is_ipc_notify(ipc_status)) {
        switch (_ENDPOINT_P(msg.m_source)) {
            case HARDWARE:
                if (msg.m_notify.interrupts & BIT(mouse_bit_no)) {
                  mouse_ih();
                  if (value){
                    value = false;
                    continue;
                  }
                  
                  if (parse_packet(byte_num, &pp)) return 1;

                  if (byte_num == 2){
                    mouse_print_packet(&pp);
                    byte_num = 0;
                    cnt--;
                  }
                  else byte_num++;
                }
                break;
            default:
                break;
        }
      }
    }

    if (mouse_unsubscribe_int()) return 1;
    if (mouse_disable_data_report()) return 1;
    return 0;
}

int (mouse_test_async)(uint8_t idle_time) {
    int ipc_status, r;
    message msg;
    uint8_t timer_bit_no, mouse_bit_no, n = idle_time;
    struct packet pp;

    if (mouse_enable_data_report()) return 1;
    if (mouse_subscribe_int(&mouse_bit_no)) return 1;
    if (timer_subscribe_int(&timer_bit_no)) return 1;

    while(n > 0) {
      if ( (r = driver_receive(ANY, &msg, &ipc_status)) != 0 ) { 
        printf("driver_receive failed with: %d", r);
        continue;
      }
      if (is_ipc_notify(ipc_status)) {
        switch (_ENDPOINT_P(msg.m_source)) {
            case HARDWARE:
                if (msg.m_notify.interrupts & BIT(timer_bit_no)) {
                  timer_int_handler();

                  if (timer_counter % sys_hz() == 0){
                    n--;
                    timer_counter = 0;
                  }

                }
                if (msg.m_notify.interrupts & BIT(mouse_bit_no)) {
                  mouse_ih();
                  if (value){
                    value = false;
                    continue;
                  }
                  
                  if (parse_packet(byte_num, &pp)) return 1;

                  if (byte_num == 2){
                    mouse_print_packet(&pp);
                    byte_num = 0;
                  }
                  else byte_num++;

                  timer_counter = 0;
                  n = idle_time;
                }
                break;
            default:
                break;
        }
      }
    }

    if (timer_unsubscribe_int()) return 1;
    if (mouse_unsubscribe_int()) return 1;
    if (mouse_disable_data_report()) return 1;
    return 0;
}


int (mouse_test_gesture)(uint8_t x_len, uint8_t tolerance) {
    int ipc_status, r;
    message msg;
    uint8_t mouse_bit_no;
    struct packet pp;
    state_t state = INIT;

    if (mouse_enable_data_report()) return 1;

    if (mouse_subscribe_int(&mouse_bit_no)) return 1;

    while(state != END) {
      if ( (r = driver_receive(ANY, &msg, &ipc_status)) != 0 ) { 
        printf("driver_receive failed with: %d", r);
        continue;
      }
      if (is_ipc_notify(ipc_status)) {
        switch (_ENDPOINT_P(msg.m_source)) {
            case HARDWARE:
                if (msg.m_notify.interrupts & BIT(mouse_bit_no)) {
                  mouse_ih();
                  if (value){
                    value = false;
                    continue;
                  }
                  
                  if (parse_packet(byte_num, &pp)) return 1;

                  if (byte_num == 2){
                    mouse_print_packet(&pp);
                    byte_num = 0;

                    if (parse_movement(pp, x_len, tolerance, state)) return 1;
                    if (change_state(&state)) return 1;
                  }
                  else byte_num++;
                }
                break;
            default:
                break;
        }
      }
    }

    if (mouse_unsubscribe_int()) return 1;
    if (mouse_disable_data_report()) return 1;
    return 0;
}

/*
int (mouse_test_remote)(uint16_t period, uint8_t cnt) {
    printf("%s(%u, %u): under construction\n", __func__, period, cnt);
    return 1;
}
*/
