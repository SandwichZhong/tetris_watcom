#include "def.h"

int main(int argc, char ** argv) {
	int i, x, y;

	/* 因为双机调试未成功,所以用以下方法来调试
	   当命令行带有任意参数时进入调试模式 
	   调试模式下会写文件记录变量值 */
	if (argc > 1) {
		debugFlag = TRUE;
	}

	/* 操作指引 */
	guide();

	/* 程序初始化 */
	initialize();

	/* 程序主循环 */
	while (gameState != GAME_QUIT) {

		/* 游戏初始化 */
		initGame();

		/* 游戏主循环 */
		while (gameState != GAME_OVER && gameState != GAME_QUIT && gameState != GAME_ERROR) {

			/* 每秒执行 CLOCK_PER_SECOND=100 次 */
			if (timeCounter != currentTime) {
				currentTime = timeCounter;

				/* 每秒刷新FPS=50次屏幕 */
				if (currentTime % (CLOCK_PER_SECOND / FPS) == 1) {
					refresh();
				}
				/* 每t->speed * 10ms下移方块 t->speed介于10-50之间 */
				if ((currentTime % t->speed) == 1) {
					handleDown(MOVE_FORCE);
				}
				/* 判断游戏是否结束 */
				if (gameState == GAME_ON && isOver()) {
					gameover();
				}
			}
		}

		/* 若游戏结束或者强制退出则关闭游戏 */
		closeGame();
	}

	/* 退出程序 */
	quit();

	return 0;
}
