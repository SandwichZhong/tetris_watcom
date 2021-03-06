#include "def.h"

void interrupt(*old_9h)(void);

/* 中断函数处理按键事件 */
void interrupt int_9h(void) {
	unsigned char key;

	key = inportb(0x60);
	/*用 do-while(0)包裹以实现单次执行和按ESC时跳出 */
	do {
		if (key == 0x81) {
			gameState = GAME_QUIT;break;
		}
		switch (key) {
			case KB_W_DOWN:
			case KB_UP_DOWN:		handleFlip();				break;

			case KB_A_DOWN:
			case KB_LEFT_DOWN:		handleMove(MOVE_LEFT);		break;

			case KB_S_DOWN:
			case KB_DOWN_DOWN:		handleDown(MOVE_OP);		break;

			case KB_D_DOWN:
			case KB_RIGHT_DOWN:		handleMove(MOVE_RIGHT);		break;

			case KB_P_DOWN:			handlePause();				break;

			case KB_LSHIFT_DOWN:
			case KB_RSHIFT_DOWN:	/* 原留作彩蛋用,现废弃 */		break;

			case KB_SPACE_DOWN:									break;

			case KB_SPACE_UP:		switchSound();				break;

			case KB_ENTER_DOWN:									break;

			case KB_LSHIFT_UP:
			case KB_RSHIFT_UP:		/* 原留作彩蛋用,现废弃 */		break;
			default:											break;
		}
	} while (0);

	outportb(0x20, 0x20);
}

/* 注册中断函数并保存旧中断函数 */
void initKey() {
	old_9h = getvect(9);
	setvect(9, int_9h);
}

/* 将旧中断函数重新注册 */
void closeKey() {
	setvect(9, old_9h);
}

