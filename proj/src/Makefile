PROG=proj

.PATH: ${.CURDIR}/controller/utils
.PATH: ${.CURDIR}/controller/keyboard
.PATH: ${.CURDIR}/controller/mouse
.PATH: ${.CURDIR}/controller/timer
.PATH: ${.CURDIR}/controller/video
.PATH: ${.CURDIR}/controller/KBC
.PATH: ${.CURDIR}/controller/game
.PATH: ${.CURDIR}/model/
.PATH: ${.CURDIR}/viewer/
.PATH: ${.CURDIR}/states/

SRCS = 	main.c timer.c utils.c graphics.c KBC.c keyboard.c mouse.c map_controller.c item_controller.c panda_controller.c model.c viewer.c sprite.c game.c menu.c instructions.c game_over.c menu_viewer.c game_viewer.c game_over_viewer.c instructions_viewer.c state.c menu_state.c game_state.c instructions_state.c game_over_state.c

CFLAGS += -pedantic -D __LCOM_OPTIMIZED__

DPADD += ${LIBLCF}
LDADD += -Wall -llcf -lxpm -llm
.include <minix.lcom.mk>
