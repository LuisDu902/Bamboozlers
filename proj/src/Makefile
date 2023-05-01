PROG=proj

.PATH: ${.CURDIR}/controllers/utils
.PATH: ${.CURDIR}/controllers/keyboard
.PATH: ${.CURDIR}/controllers/mouse
.PATH: ${.CURDIR}/controllers/timer
.PATH: ${.CURDIR}/controllers/video
.PATH: ${.CURDIR}/controllers/KBC
.PATH: ${.CURDIR}/model/
.PATH: ${.CURDIR}/view/

SRCS = 	main.c timer.c utils.c graphics.c KBC.c keyboard.c mouse.c model.c view.c sprite.c

CFLAGS += -pedantic -D_LCOM_OPTIMIZED_ -O2

DPADD += ${LIBLCF}
LDADD += -Wall -llcf -lxpm -llm
.include <minix.lcom.mk>
