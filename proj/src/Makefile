PROG=proj

.PATH: ${.CURDIR}/controller/utils
.PATH: ${.CURDIR}/controller/keyboard
.PATH: ${.CURDIR}/controller/mouse
.PATH: ${.CURDIR}/controller/timer
.PATH: ${.CURDIR}/controller/video
.PATH: ${.CURDIR}/controller/KBC
.PATH: ${.CURDIR}/model/
.PATH: ${.CURDIR}/viewer/
.PATH: ${.CURDIR}/states/

SRCS = 	main.c timer.c utils.c graphics.c KBC.c keyboard.c mouse.c model.c viewer.c sprite.c game.c menu.c menu_viewer.c game_viewer.c state.c menu_state.c game_state.c

CFLAGS += -pedantic -D_LCOM_OPTIMIZED_ -O2

DPADD += ${LIBLCF}
LDADD += -Wall -llcf -lxpm -llm
.include <minix.lcom.mk>
