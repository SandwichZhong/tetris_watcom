#include "def.h"

/* 以下为保存方块形状和旋转变化的数组 */
char shapes[][N][N * N] = {
	{
		{ 0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0 },
		{ 0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0 },
		{ 0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0 },
		{ 0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0 }
	},
	{
		{ 0,1,1,0,0,1,0,0,0,1,0,0,0,0,0,0 },
		{ 0,0,0,0,1,1,1,0,0,0,1,0,0,0,0,0 },
		{ 0,1,0,0,0,1,0,0,1,1,0,0,0,0,0,0 },
		{ 1,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0 }
	},
	{
		{ 1,1,0,0,0,1,0,0,0,1,0,0,0,0,0,0 },
		{ 0,0,1,0,1,1,1,0,0,0,0,0,0,0,0,0 },
		{ 0,1,0,0,0,1,0,0,0,1,1,0,0,0,0,0 },
		{ 0,0,0,0,1,1,1,0,1,0,0,0,0,0,0,0 }
	},
	{
		{ 0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0 },
		{ 0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0 },
		{ 0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0 },
		{ 0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0 }
	},
	{
		{ 0,1,0,0,1,1,0,0,1,0,0,0,0,0,0,0 },
		{ 1,1,0,0,0,1,1,0,0,0,0,0,0,0,0,0 },
		{ 0,1,0,0,1,1,0,0,1,0,0,0,0,0,0,0 },
		{ 1,1,0,0,0,1,1,0,0,0,0,0,0,0,0,0 }
	},
	{
		{ 1,0,0,0,1,1,0,0,0,1,0,0,0,0,0,0 },
		{ 0,1,1,0,1,1,0,0,0,0,0,0,0,0,0,0 },
		{ 1,0,0,0,1,1,0,0,0,1,0,0,0,0,0,0 },
		{ 0,1,1,0,1,1,0,0,0,0,0,0,0,0,0,0 }
	},
	{
		{ 0,1,0,0,0,1,1,0,0,1,0,0,0,0,0,0 },
		{ 0,0,0,0,1,1,1,0,0,1,0,0,0,0,0,0 },
		{ 0,1,0,0,1,1,0,0,0,1,0,0,0,0,0,0 },
		{ 0,1,0,0,1,1,1,0,0,0,0,0,0,0,0,0 }
	}
};

/* 游戏计时,每秒增加 CLOCK_PER_SECOND */
volatile unsigned int timeCounter = 0;
/* 当前游戏时间,实则为实现每秒执行若干次主循环而定义 */
volatile unsigned int currentTime = 0;
/*	游戏状态,不同的游戏状态会有不同的响应
	参见def.h里宏定义部分 */
volatile int gameState = GAME_STOP;
/* 调试flag,调试用 */
volatile unsigned int debugFlag = 0;
/* 保存闪烁开始时间 */
volatile unsigned int blinkingTime = 0;
/* 表示哪几行是满的,需要闪烁 */
volatile unsigned int blinkingVar = 0x0;
/* 最后人为操作时间,限制过于频繁的操作 */
volatile unsigned int lastTime = 0;
/*	方块当前是否被改变(上下左右操作),若正在被改变则不允许做操作
	原为防止按键操作和自动操作(每隔一段时间自动下移方块)冲突,尚不清楚是否有效 */
volatile int isChanging = FALSE;
/* 声音开关 */
volatile int soundSwitch = TRUE;

/* 保存上次及本次游戏矩阵,刷新游戏界面用 */
char map[2][X * E_Y] = { 0 };
int index = 0;

/* 以下三个rect为游戏中三个方框,分别用作游戏界面,下个方块预览和分数难度按钮显示 */
rect mainBox = {
	.x = MAINBOX_X,
	.y = MAINBOX_Y,
	.w = MAINBOX_W,
	.h = MAINBOX_H
};

rect showBox = {
	.x = SHOWBOX_X,
	.y = SHOWBOX_Y,
	.w = SHOWBOX_W,
	.h = SHOWBOX_H
};

rect funcBox = {
	.x = FUNCBOX_X,
	.y = FUNCBOX_Y,
	.w = FUNCBOX_W,
	.h = FUNCBOX_H
};

/* 以下三个rect为三个按钮对应的区域 */
rect playButtonRect = {
	.x = FUNCBOX_X + 20,
	.y = FUNCBOX_Y + 150,
	.w = BUTTONW,
	.h = BUTTONH
};

rect quitButtonRect = {
	.x = FUNCBOX_X + 20,
	.y = FUNCBOX_Y + 200,
	.w = BUTTONW,
	.h = BUTTONH
};

rect soundButtonRect = {
	.x = FUNCBOX_X + 20,
	.y = FUNCBOX_Y + 100,
	.w = BUTTONW,
	.h = BUTTONH
};

/* 以下为三个按钮 */
button playButton;
button quitButton;
button soundButton;

/* 以下为游戏结构体 */
tetris * t = NULL;

/* 以下为调试文件 */
FILE * debugFile = NULL;

/* 以下为声音文件,bgm舍弃 */
//wave * bgm = NULL;
wave * flip = NULL;
wave * gameOver = NULL;
wave * removeLine = NULL;
wave * drop = NULL;

//char bgmPath[] = "sound\\bgm.wav";
char flipPath[] = "sound\\flip.wav";
char gameOverpath[] = "sound\\gameover.wav";
char dropPath[] = "sound\\drop.wav";
char removeLinePath[] = "sound\\remove.wav";

/* 操作引导 */
void guide() {
	printf("*******************************************************************************\n");
	printf("*Tetris Guide:\n");
	printf("*\t %#c / W : Flip\n", 30);
	printf("*\t %#c / A : Turn Left\n", 17);
	printf("*\t %#c / D : Turn right\n", 16);
	printf("*\t %#c / S : Speed up\n", 31);
	printf("*\t P / Second Button : pause/play\n");
	printf("*\t space / First Button : Sound on/off\n");
	printf("*\t ESC / Third Button : Quit Game\n");
	printf("*Press any key to begin\n");
	printf("*******************************************************************************\n");
	getch();
}

/* 程序初始化,包括图形,声卡,随机种子,鼠标,按键,计时器初始化和绘制背景,加载音乐文件 */
void initialize() {
	initGraph(VESA_640x480x32bit);
	initSound();
	initTimer();
	initKey();
	paintBackground();
	initMouse();
	randomize();
	if (debugFlag) {
		debugFile = fopen("debug.txt", "w+");
	}
	//bgm = loadWave(bgmPath);
	flip = loadWave(flipPath);
	gameOver = loadWave(gameOverpath);
	drop = loadWave(dropPath);
	removeLine = loadWave(removeLinePath);
}

/* 程序结束 */
void quit() {
	closeKey();
	closeMouse();
	closeGraph();
	closeTimer();
	closeSound();
	//freeWave(bgm);
	freeWave(flip);
	freeWave(gameOver);
	freeWave(drop);
	freeWave(removeLine);
	if (debugFlag) {
		fclose(debugFile);
	}
}

/* 处理暂停 */
void handlePause() {
	if (gameState == GAME_ON) {
		gameState = GAME_PAUSE_BEGIN;
		playButton.state = BUTTON_DOWN;
	}
	else if (gameState == GAME_PAUSE) {
		gameState = GAME_RESUME;
		playButton.state = BUTTON_UP;
	}
	paintButton(&playButton);
}

/* 处理向左或向右移动,参数direction表示方向 */
void handleMove(int direction) {
	int step = 0;

	if (gameState != GAME_ON || isChanging == TRUE || currentTime - lastTime < MIN_TIME) {
		return;
	}
	if (direction == MOVE_LEFT) {
		step = -1;
	}
	else {
		step = 1;
	}

	isChanging = TRUE;
	/* 先移动,若重合则退回,然后刷新 */
	t->x = t->x + step;
	if (!isCrash()) {
		lastTime = currentTime;
	}
	else {
		t->x = t->x - step;
	}
	refresh();
	isChanging = FALSE;
}

/* 处理向下移动,参数isForce表示是否人为操作 */
void handleDown(int isForce) {

	if (gameState != GAME_ON) {
		return;
	}
	if (isForce != MOVE_FORCE) {
		if (currentTime - lastTime < MIN_TIME || isChanging == TRUE) {
			return;
		}
	}
	isChanging = TRUE;
	/* 先向下移动,若重合则退回并合并,检测是否有满行 */
	t->y = t->y + 1;
	if (isCrash()) {
		t->y = t->y - 1;
		if (soundSwitch) {
			playWave(drop, 1);
		}
		combine();
		rmLine();
	}
	lastTime = currentTime;
	refresh();
	isChanging = FALSE;
}

/* 处理旋转 */
void handleFlip() {
	int i;
	if (gameState != GAME_ON || currentTime - lastTime < MIN_TIME || isChanging == TRUE) {
		return;
	}
	isChanging = TRUE;
	/* 先旋转,若重合则回退 */
	t->flip = (t->flip + 1) % 4;
	for (i = 0; i < N * N; i++) {
		t->shape[i] = shapes[t->color][t->flip][i];
	}
	if (isCrash()) {
		if (t->flip == 0) {
			t->flip = 3;
		}
		else {
			t->flip -= 1;
		}
		for (i = 0; i < N * N; i++) {
			t->shape[i] = shapes[t->color][t->flip][i];
		}
	}
	else {
		if (soundSwitch) {
			playWave(flip, 1);
		}
	}
	lastTime = currentTime;
	refresh();
	isChanging = FALSE;
}

/* 初始化游戏,游戏变量初始化和界面绘制 */
void initGame() {
	int y, x;
	int i;

	paintBackground();

	paintBox(&mainBox, BOXTHICKNESS, BOXCOLOR);
	paintBox(&showBox, BOXTHICKNESS, BOXCOLOR);
	paintBox(&funcBox, BOXTHICKNESS, BOXCOLOR);

	playButton.r = playButtonRect;
	playButton.state = BUTTON_DOWN;

	quitButton.r = quitButtonRect;
	quitButton.state = BUTTON_UP;

	soundButton.r = soundButtonRect;
	soundButton.state = BUTTON_UP;

	paintButton(&soundButton);
	paintButton(&playButton);
	paintButton(&quitButton);
	
	
	currentTime = 0;
	timeCounter = 0;
	gameState = GAME_ON;
	blinkingVar = 0;
	isChanging = FALSE;
	lastTime = 0;

	t = (tetris *)malloc(sizeof(tetris));
	if (t == NULL) {
		gameState = GAME_ERROR;
	}
	blinkingTime = currentTime;

	t->speed = 50;

	for (i = 0; i < E_Y * X; i++) {
		t->cubes[i] = EMPTY;
		for (x = 0; x < 2; x++) {
			map[x][i] = EMPTY;
		}
	}
	i = random(TYPES);
	t->flip = 0;
	t->color = i;
	for (i = 0; i < N * N; i++) {
		t->shape[i] = shapes[t->color][t->flip][i];
	}
	t->score = 0;

	t->x = INIT_X;
	t->y = INIT_Y;
	i = random(TYPES);
	t->nextShape = i;
	for (y = 0; y < N; y++) {
		for (x = 0; x < N; x++) {
			paintUnit(x + 14, y + 5, EMPTY, UNIT_NORMAL);
			if (shapes[t->nextShape][0][y * N + x]) {
				paintUnit(x + 14, y + 5, t->nextShape, UNIT_NORMAL);
			}
		}
	}
	refreshScore();
}

/* 游戏结束 */
void closeGame() {
	int i;
	int y, x;
	if (debugFlag) {
		fputs("Debug Info:\n", debugFile);
		fprintf(debugFile, "address: %#x\n", t);
		fprintf(debugFile, "x: %d\n", t->x);
		fprintf(debugFile, "xaddress: %#x\n", &t->x);
		fprintf(debugFile, "y: %d\n", t->y);
		fprintf(debugFile, "yaddress: %#x\n", &t->y);
		fprintf(debugFile, "color: %d\n", t->color);
		fprintf(debugFile, "coloraddress: %#x\n", &t->color);
		fprintf(debugFile, "nextShape: %d\n", t->nextShape);
		fprintf(debugFile, "nextShapeaddress: %#x\n", &t->nextShape);
		fprintf(debugFile, "flip: %d\n", t->flip);
		fprintf(debugFile, "flipaddress: %#x\n", &t->flip);

		fprintf(debugFile, "score: %d\n", t->score);
		fprintf(debugFile, "scoreaddress: %#x\n", &t->score);
		fprintf(debugFile, "speed: %d\n", t->speed);
		fprintf(debugFile, "speedaddress: %#x\n", &t->speed);
		fprintf(debugFile, "blinkingTime: %d\n", blinkingTime);
		fprintf(debugFile, "blinkingTimeaddress: %#x\n", &blinkingTime);

		fprintf(debugFile, "cubesaddress: %#x\n", t->cubes);
		fputs("cubes:\n", debugFile);
		for (y = 0; y < E_Y; y++) {
			for (x = 0; x < X; x++) {
				fprintf(debugFile, "%4d ", t->cubes[y * X + x]);
			}
			fputs("\n", debugFile);
		}
		fprintf(debugFile, "shapeaddress: %#x\n", t->shape);
		fputs("shape:\n", debugFile);
		for (y = 0; y < N; y++) {
			for (x = 0; x < N; x++) {
				fprintf(debugFile, "%4d ", t->shape[y * N + x]);
			}
			fputs("\n", debugFile);
		}

		fputs("\n", debugFile);
	}
	free(t);
}

/* 难度提升 */
void levelUp() {
	if (t->score < 200) {
		t->speed = 50;
	}
	else if (t->score < 500) {
		t->speed = 45;
	}
	else if (t->score < 900) {
		t->speed = 40;
	}
	else if (t->score < 1400) {
		t->speed = 35;
	}
	else if (t->score < 2000) {
		t->speed = 30;
	}
	else if (t->score < 2500) {
		t->speed = 25;
	}
	else if (t->score < 3100) {
		t->speed = 20;
	}
	else if (t->score < 3800) {
		t->speed = 15;
	}
	else if (t->score < 4600) {
		t->speed = 10;
	}
}

/* 判断是否重合 */
int isCrash() {
	int y, x;
	int _y, _x;

	for (y = 0; y < N; y++) {
		for (x = 0; x < N; x++) {
			_y = y + t->y;
			_x = x + t->x;
			if (t->shape[y * N + x] != 0) {
				if (_x < 0 || _x >= X || _y >= E_Y) {
					return 1;
				}
				if (t->cubes[_y * X + _x] != EMPTY) {
					return 1;
				}
			}
		}
	}
	return 0;
}

/* 判断游戏是否结束 */
int isOver() {
	int y, x;
	for (y = EXTRA - 1; y > 0; y--) {
		for (x = 0; x < X; x++) {
			if (t->cubes[y * X + x] != EMPTY) {
				return 1;
			}
		}
	}
	return 0;
}

/* 方块着地时则将shape合并到cubes,并重新生成shape */
void combine() {
	int y, x;
	int _x, _y;
	for (y = 0; y < N; y++) {
		for (x = 0; x < N; x++) {
			_x = x + t->x;
			_y = y + t->y;
			if (t->shape[y * N + x] != 0) {
				if (_x >= 0 && _x < X && _y >= 0 && _y < E_Y) {
					t->cubes[_y * X + _x] = t->color;
				}
			}
		}
	}
	t->color = t->nextShape;
	t->flip = 0;
	for (x = 0; x < N * N; x++) {
		t->shape[x] = shapes[t->color][t->flip][x];
	}
	x = random(TYPES);
	t->nextShape = x;
	t->x = INIT_X;
	t->y = INIT_Y;
	//TODO
	for (y = 0; y < N; y++) {
		for (x = 0; x < N; x++) {
			paintUnit(x + 14, y + 5, EMPTY, UNIT_NORMAL);
			if (shapes[t->nextShape][0][y * N + x]) {
				paintUnit(x + 14, y + 5, t->nextShape, UNIT_NORMAL);
			}
		}
	}
}

/* 检测哪几行满了,需要消除,记录在变量blinkingVar里,在refresh中处理 */
void rmLine() {
	int y, x;
	int isOk = 1;
	int lines = 0;
	for (y = E_Y - 1; y > 0; y--) {
		for (x = 0, isOk = 1; x < X; x++) {
			if (t->cubes[y * X + x] == EMPTY) {
				isOk = 0;
				break;
			}
		}
		if (isOk) {
			lines++;
			blinkingVar = blinkingVar | (1 << y);
		}
	}
	/* 若有满行,则进入 GAME_BLINKING 状态,其余工作在refresh中完成 */
	if (lines > 0) {
		if (soundSwitch) {
			playWave(removeLine, 1);
		}
		gameState = GAME_BLINKING;
		blinkingTime = currentTime;
	}
}

/* 声音开关 */
void switchSound() {
	if (soundSwitch) {
		//stopWave(bgm);
		soundSwitch = FALSE;
	}
	else {
		soundSwitch = TRUE;
		//playWave(bgm, -1);
	}
	if (soundButton.state == BUTTON_DOWN) {
		soundButton.state = BUTTON_UP;
	}
	else {
		soundButton.state = BUTTON_DOWN;
	}
	paintButton(&soundButton);
}

/* 游戏结束 */
void gameover() {
	if (soundSwitch) {
		playWave(gameOver, 1);
	}
	gameState = GAME_OVER;
	sleep(2);
}
