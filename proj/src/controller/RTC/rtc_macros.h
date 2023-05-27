#ifndef _LCOM_RTC_MACROS_H_
#define _LCOM_RTC_MACROS_H_

#include <minix/sysutil.h>
#include <lcom/lcf.h>

// Macros
#define RTC_MASK            5
#define IRQ_RTC             8
#define IN_REG              0x70
#define OUT_REG             0x71

#define REG_UPD             10
#define REG_COUNT           11

#define SECONDS             0
#define MINUTES             2
#define HOURS               4   
#define DAY                 7
#define MONTH               8
#define YEAR                9

#define UPD          BIT(7)

#endif

