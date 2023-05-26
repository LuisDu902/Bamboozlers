#ifndef _LCOM_UTILS_H_
#define _LCOM_UTILS_H_

#include <stdint.h>

#ifndef BIT
#define BIT(n) (1 << (n))
#endif


/**
 * @brief Invokes sys_inb() system call but reads the value into a uint8_t variable.
 *
 * @param port the input port that is to be read
 * @param value a pointer to the variable that is to be update with the value read
 * @return Return 0 upon success and non-zero otherwise
 */
int (util_sys_inb)(int port, uint8_t *value);

#endif /* _LCOM_UTILS_H */
