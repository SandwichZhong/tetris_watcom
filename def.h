#ifndef DEF_H_
#define	DEF_H_

#include <graphics.h>

//define colors' ARGB
/*定义常用颜色的RGB值*/
#define		__ORANGE			((uint32) 0x00FF6600 )
#define		__GREEN				((uint32) 0x0000FF00 )
#define		__BLUE				((uint32) 0x003333FF )
#define		__CYAN				((uint32) 0x0066CCFF )
#define		__PURPLE			((uint32) 0x00CC00FF )
#define		__RED				((uint32) 0x00FF0000 )
#define		__YELLOW			((uint32) 0x00FFFF00 )
#define		__BROWN				((uint32) 0x00884411 )
#define		__PINK				((uint32) 0x00FFCCCC )
#define		__SKYBLUE			((uint32) 0x0000BBFF )
#define		__AQUAMARINE		((uint32) 0x0077FFDD )
#define		__OLIVERDRAB		((uint32) 0x00668822 )
#define		__TAN				((uint32) 0x00DDBB88 )
#define		__GOLDENROD			((uint32) 0x00DDAA22 )
#define		__DARKCYAN			((uint32) 0x00008888 )
#define		__LIMEGREEN			((uint32) 0x0033CC33 )

#define		__WHITE				((uint32) 0x00FFFFFF )
#define		__BLACK				((uint32) 0x00000000 )
#define		BGCOLOR				((uint32) 0x00DDEEFF )
#define		BGLINECOLOR			((uint32) 0x00C3D4E5 )
#define		BOXCOLOR			((uint32) 0x007788AA )
#define		FONTCOLOR			(__BLACK)

//ui related macros
/* 每个方块边长占据的像素 */
#define		UNIT_PIXELS			( 20 )
/* 每个方块线占据的像素 */
#define		LINE_PIXELS			( 1  )
/*	每个方块边缘加深或者变浅部分占据的像素
	使得方块有一定的立体感 */
#define		EXTRA_PIXELS		( 3  )

/* 背景线条数目 */
#define 	BGLINES				( 80 )

/* 屏幕高度宽度和位宽 */
#define		SCREEN_HEIGHT		( 480)
#define		SCREEN_WIDTH		( 640)
#define		SCREEN_BPP			( 4  )

/* 游戏中主矩阵和形状矩阵的长和宽,用24x10取代20x10方便处理消除满行 */
#define		Y					( 20 )
#define		E_Y					( 24 )
#define		EXTRA				( 4  )
#define		X					( 10 )
#define		N					( 4  )

/* 方块状态,用于刷新时制作闪烁特效 */
#define 	UNIT_NORMAL			(0x01)
#define 	UNIT_BLINKING 		(0x02)

/* 以下为游戏布局相关 */
#define		OFFSET_X			( 99 )
#define		OFFSET_Y			( 20 )
#define		BOXTHICKNESS		( 10 )
#define		BOXDISTANCE			( 40 )
#define		MAINBOX_X			( OFFSET_X + 2 )
#define		MAINBOX_Y			( OFFSET_Y + 2 )
#define		MAINBOX_W			( X * UNIT_PIXELS + (X) * LINE_PIXELS + 2 * BOXTHICKNESS )
#define		MAINBOX_H			( Y * UNIT_PIXELS + (Y) * LINE_PIXELS + 2 * BOXTHICKNESS )
#define		SHOWBOX_X			( OFFSET_X + MAINBOX_W + BOXDISTANCE )
#define		SHOWBOX_Y			( OFFSET_Y + 2 )
#define		SHOWBOX_W			( 200)
#define		SHOWBOX_H			( 150)
#define		FUNCBOX_X			( OFFSET_X + MAINBOX_W + BOXDISTANCE )
#define		FUNCBOX_Y			( OFFSET_Y + SHOWBOX_H + BOXDISTANCE )
#define		FUNCBOX_W			( 200)
#define		FUNCBOX_H			( 252)
#define		BUTTONTHICKNESS		( 0x2)
#define		BUTTONW				( 100)
#define		BUTTONH				( 40 )

#define		TEXTLENGTH			( 20 )

/* 按钮状态 */
#define		BUTTON_UP			(0x00)
#define		BUTTON_DOWN			(0x01)

/* 字体大小 */
#define		FONTSIZE			( 16 )

//game related macros
/* 以下为游戏状态相关宏定义,表示游戏阶段 */
/* GAME_ON 阶段为游戏主阶段可进行游戏操作 */
#define		GAME_ON				(0x00)
/* GAME_PAUSE 阶段为暂停阶段,此阶段不可进行游戏操作,游戏主矩阵不可见 */
#define		GAME_PAUSE			(0x01)
/* GAME_STOP 阶段为停止阶段,实际上没有用到 */
#define		GAME_STOP			(0x02)
/* GAME_OVER 阶段为游戏失败,本阶段会立刻结束重新开始游戏 */
#define		GAME_OVER			(0x04)
/* GAME_QUIT 阶段为退出游戏,本阶段会立刻结束程序 */
#define		GAME_QUIT			(0x08)
/* GAME_ERROR 阶段为游戏出错,表示游戏运行出错 */
#define		GAME_ERROR			(0x20)
/* GAME_BLINKING 为游戏动画阶段,此阶段不可操作,满的行会闪烁,持续0.5s */
#define		GAME_BLINKING		(0x40)
/* GAME_OTHER 保留阶段,未使用 */
#define		GAME_OTHER			(0x80)
/* GAME_RESUME 为暂停结束阶段,本阶段会重新绘制游戏主方框,然后进入 GAME_ON 阶段 */
#define		GAME_RESUME			(0x100)
/* GAME_PAUSE_BEGIN 为暂停开始阶段,本阶段会绘制图形覆盖游戏主界面,然后进入 GAME_PAUSE 阶段*/
#define		GAME_PAUSE_BEGIN	(0x200)

#define		TIMER				(0x1C)

/* 时钟震荡频率 */
#define		CLOCK_PER_SECOND	( 100)
/* 屏幕刷新率 */
#define		FPS					( 50 )

/* 方块种类 */
#define		TYPES				( 7  )

/* 方块初始坐标 */
#define		INIT_X				(  3 )
#define		INIT_Y				(  0 )

/* 移动方向 */
#define		MOVE_LEFT			(0x00)
#define		MOVE_RIGHT			(0x01)
/* 操作类型,人为or强制 */
#define		MOVE_FORCE			(0x01)
#define		MOVE_OP				(0x00)
/* 操作最短间隔时间 */
#define		MIN_TIME			(0x00)

#define		TRUE				(0x01)
#define		FALSE				(0x00)

/* 声音开关 */
#define		SOUND_ON			(0x01)
#define		SOUND_OFF			(0x00)

//define tetris types
#define		EMPTY				(0xFF)
#define 	TETRIS01			(0x00)
#define 	TETRIS02			(0x01)
#define 	TETRIS03			(0x02)
#define 	TETRIS04			(0x03)
#define 	TETRIS05			(0x04)
#define 	TETRIS06			(0x05)
#define 	TETRIS07			(0x06)
#define 	TETRIS08			(0x07)
#define 	TETRIS09			(0x08)
#define 	TETRIS10			(0x09)
#define 	TETRIS11			(0x0A)
#define 	TETRIS12			(0x0B)
#define 	TETRIS13			(0x0C)
#define 	TETRIS14			(0x0D)
#define 	TETRIS15			(0x0E)
#define 	TETRIS16			(0x0F)

//keys define
#define		KB_UP_DOWN			(0x48)
#define		KB_UP_UP			(0xC8)
#define		KB_DOWN_DOWN		(0x50)
#define		KB_DOWN_UP			(0xD0)
#define		KB_LEFT_DOWN		(0x4B)
#define		KB_LEFT_UP			(0xCB)
#define		KB_RIGHT_DOWN		(0x4D)
#define		KB_RIGHT_UP			(0xCD)
#define		KB_P_DOWN			(0x19)
#define		KB_P_UP				(0x99)
#define		KB_SPACE_DOWN		(0x39)
#define		KB_SPACE_UP			(0xB9)
#define		KB_ENTER_DOWN		(0x1C)
#define		KB_ENTER_UP			(0x9C)
#define		KB_W_DOWN			(0x11)
#define		KB_W_UP				(0x91)
#define		KB_S_DOWN			(0x1F)
#define		KB_S_UP				(0x9F)
#define		KB_A_DOWN			(0x1E)
#define		KB_A_UP				(0x9E)
#define		KB_D_DOWN			(0x20)
#define		KB_D_UP				(0xA0)
#define		KB_LSHIFT_DOWN		(0x2A)
#define		KB_LSHIFT_UP		(0xAA)
#define		KB_RSHIFT_DOWN		(0x36)
#define		KB_RSHIFT_UP		(0xB6)

//mouse macro
#define 	MOUSE_SIZE      	( 16 )
#define 	MOUSE_MOVE      	(0x01)
#define 	MOUSE_LEFT_DOWN 	(0x02)
#define 	MOUSE_LEFT_UP   	(0x04)
#define 	MOUSE_RIGHT_DOWN 	(0x08)
#define 	MOUSE_RIGHT_UP   	(0x10)
#define 	MOUSE_MIDDLE_DOWN	(0x20)
#define 	MOUSE_MIDDLE_UP  	(0x40)

//api macro
/* 让函数符合我的使用习惯 */
#define		setTimerFrequency	set_timer_frequency
#define 	closeGraph 			closegraph
#define 	loadWave			load_wave
#define		playWave			play_wave
#define		stopWave			stop_wave
#define		pauseWave			pause_wave
#define		resumeWave			resume_wave
#define		freeWave			free_wave
#define		initSound			initsound
#define		closeSound			closesound

//type define

typedef struct wave wave;

/*	以下为游戏结构体设计
	x,y为方块所在位置
	color为当前方块的颜色和形状
	nextShape为下一个方块的颜色和形状
	flip为当前方块的旋转状态
	score为游戏得分
	speed为游戏难度
	shape数组保存方块形状信息
	cubes数组保存游戏主矩阵信息 */
typedef struct tetris {
	int x;
	int y;
	char color;
	char nextShape;
	char flip;
	unsigned int score;
	unsigned int speed;
	char shape[N * N + 4];
	char cubes[X * E_Y + 4];
} tetris;

struct _mouse {
	int x, y;
	struct picture *background;
	struct picture *mask;
	struct picture *img;
};

typedef struct rect {
	int x, y;
	int w, h;
} rect;

typedef struct button {
	rect r;
	int state;
} button;

typedef unsigned short uint16;
typedef unsigned long int uint32;


/*	functions 
	由于多文件编译有些许问题,所以将所有函数及变量声明均放入这个头文件
	以达到跨文件函数和变量共享的效果 */

/* paint.c */
extern void initGraph(int mode);
extern void paintBackground();
extern void paintUnit(int x, int y, char color, int state);
extern void paintBox(rect * r, int t, uint32 c);
extern void paintButton(button * b);
extern void refresh();
extern void putChar(int x, int y, char c);
extern void putText(int x, int y, char text[]);

/* mouse.c */
extern int  initMouse(void);
extern void paintMouse(int x, int y);
extern void recMouseBackground(void);
extern void saveMouseBackground(int x, int y);
extern void moveMouse(int x, int y);
extern void __loadds far mouseEvent(int event, int x, int y);
extern void expandMaskToImage(uint16 m[16], byte *p, uint32 color, int width, int height);
extern void buildMouseImage(void);
extern void closeMouse(void);
extern int inButton(int x, int y, button * b);

/* key.c */
extern void interrupt int_9h(void);
extern void initKey();
extern void closeKey();

/* tetris.c */
extern void guide();
extern void initialize();
extern void quit();
extern void handlePause();
extern void handleMove(int direction);
extern void handleDown(int isForce);
extern void handleFlip();
extern void initGame();
extern void closeGame();
extern void levelUp();
extern int isCrash();
extern int isOver();
extern void combine();
extern void rmLine();
extern void switchSound();
extern void refreshScore();
extern void gameover();

/* timer.c */
extern void interrupt newTimer(void);
extern void initTimer();
extern void closeTimer();


/* global variables */
extern volatile unsigned int timeCounter;
extern volatile unsigned int currentTime;
extern volatile int gameState;
extern volatile unsigned int debugFlag;

extern volatile unsigned int blinkingTime;
extern volatile unsigned int lastTime;
extern volatile int isChanging;
extern volatile unsigned int blinkingVar;
extern volatile int soundSwitch;

extern char map[2][X * E_Y];
extern int index;

extern rect mainBox;
extern rect showBox;
extern rect funcBox;
extern tetris * t;

extern FILE * debugFile;

//wave * bgm = NULL;
extern wave * flip;
extern wave * gameOver;
extern wave * removeLine;
extern wave * drop;

extern button playButton;
extern button quitButton;
extern button soundButton;

#endif // !DEF_H_

