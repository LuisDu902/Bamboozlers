PROG=proj

.PATH: ${.CURDIR}/controller/utils
.PATH: ${.CURDIR}/controller/keyboard
.PATH: ${.CURDIR}/controller/mouse
.PATH: ${.CURDIR}/controller/timer
.PATH: ${.CURDIR}/controller/video
.PATH: ${.CURDIR}/controller/KBC
.PATH: ${.CURDIR}/controller/RTC
.PATH: ${.CURDIR}/controller/game
.PATH: ${.CURDIR}/model/
.PATH: ${.CURDIR}/viewer/
.PATH: ${.CURDIR}/states/

SRCS = 	main.c timer.c utils.c graphics.c KBC.c keyboard.c mouse.c controller.c model.c viewer.c sprite.c state.c rtc.c

CFLAGS += -pedantic -D __LCOM_OPTIMIZED__

DPADD += ${LIBLCF}
LDADD += -Wall -llcf -lxpm -llm
.include <minix.lcom.mk>
