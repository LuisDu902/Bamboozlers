#ifndef _LCOM_I8042_H_
#define _LCOM_I8042_H_

#include <lcom/lcf.h>

/** @defgroup macros macros*/

/*KEYBOARD MACROS*/

#define KBD_IRQ 1 /**< @brief Keyboard IRQ line */

#define KBC_ERROR (BIT(7)|BIT(6))

#define KBC_ST_REG  0x64
#define KBC_CMD_REG 0x64
#define KBC_OUT_BUF 0x60

#define READ_CMD_BYTE 0x20
#define WRITE_CMD_BYTE 0x60

#define ESC_MAKE 0x01
#define ESC_BREAK 0x81

#define SC_FIRST_BYTE 0xE0

#define DELAY_US 20000

#define KBC_AUX BIT(5)
#define KBC_IBF BIT(1)
#define KBC_OBF BIT(0)

/*MOUSE MACROS*/

#define MOUSE_IRQ 0x0C /*IRQ_12*/

#define MOUSE_CMD_BYTE 0xD4

#define ENABLE_CMD 0xF4
#define DISABLE_CMD 0xF5

#define MOUSE_ACK 0xFA /*everything is ok*/
#define MOUSE_NACK 0xFE
#define MOUSE_ERROR 0xFC

typedef enum {INIT, LEFT, VERTEX, RIGHT, END} state_t;
typedef enum {L_MOVE, R_MOVE, MOV_END, NO_MOVE, OTHER} movement_t;

#endif /* _LCOM_I8042_H */
