#include "def.h"

void interrupt(*oldTimer)(void);

/* 计时 */
void interrupt newTimer(void) {
	(*oldTimer)();
	timeCounter++;
}

/* 注册计时器并保存旧计时器 */
void initTimer() {
	oldTimer = getvect(TIMER);
	disable();
	setvect(TIMER, newTimer);
	enable();
	setTimerFrequency(1193180 / CLOCK_PER_SECOND);
}

/* 恢复旧计时器 */
void closeTimer() {
	disable();
	setvect(TIMER, oldTimer);
	enable();
}
