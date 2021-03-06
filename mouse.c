#include "def.h"

struct _mouse mouse;

/* 为了美观自定义了鼠标形状 */
uint16 screenMask[] =
{
	/*16 words of screen mask */
	0x3FFF, /*0011 1111 1111 1111*/
	0x1FFF, /*0001 1111 1111 1111*/
	0x0FFF, /*0000 1111 1111 1111*/
	0x07FF, /*0000 0111 1111 1111*/
	0x03FF, /*0000 0011 1111 1111*/
	0x01FF, /*0000 0001 1111 1111*/
	0x00FF, /*0000 0000 1111 1111*/
	0x007F, /*0000 0000 0111 1111*/
	0x003F, /*0000 0000 0011 1111*/
	0x001F, /*0000 0000 0001 1111*/
	0x000F, /*0000 0000 0000 1111*/
	0x0007, /*0000 0000 0000 0111*/
	0x07FF, /*0000 0111 1111 1111*/
	0x0FFF, /*0000 1111 1111 1111*/
	0x1FFF, /*0001 1111 1111 1111*/
	0x3FFF	/*0011 1111 1111 1111*/
};

uint16 cursorMask[] =
{
	/*  words of screen mask */
	0x0000, /*0000 0000 0000 0000*/
	0x4000, /*0100 0000 0000 0000*/
	0x6000, /*0110 0000 0000 0000*/
	0x7000, /*0111 0000 0000 0000*/
	0x7800, /*0111 1000 0000 0000*/
	0x7C00, /*0111 1100 0000 0000*/
	0x7E00, /*0111 1110 0000 0000*/
	0x7F00, /*0111 1111 0000 0000*/
	0x7F80, /*0111 1111 1000 0000*/
	0x7FC0, /*0111 1111 1100 0000*/
	0x7FE0, /*0111 1111 1110 0000*/
	0x7800, /*0111 1000 0000 0000*/
	0x7000, /*0111 0000 0000 0000*/
	0x6000, /*0110 0000 0000 0000*/
	0x4000, /*0100 0000 0000 0000*/
	0x0000	/*0000 0000 0000 0000*/
};

void (far *oldMouseEvent)(int event, int x, int y);

void __loadds far mouseEvent(int event, int x, int y) {

#pragma aux mouseEvent parm [EAX] [ECX] [EDX];
	static left_button_hold_down = 0;
	if (event & MOUSE_MOVE) {
		if (left_button_hold_down) {
			recMouseBackground();
			saveMouseBackground(x, y);
		}
		moveMouse(x, y);
	}
	else if (event & MOUSE_RIGHT_UP) {
		//gameState = GAME_QUIT;
	}
	else if (event & MOUSE_LEFT_DOWN) {
		left_button_hold_down = 1;

		/* 以下为鼠标单击按钮事件处理 */
		if (inButton(x, y, &quitButton)) {
			gameState = GAME_QUIT;
		}
		if (inButton(x, y, &playButton)) {
			if (playButton.state == BUTTON_UP) {
				playButton.state = BUTTON_DOWN;
			}
			else {
				playButton.state = BUTTON_UP;
			}
			handlePause();
			paintButton(&playButton);
		}
		if (inButton(x, y, &soundButton)) {
			switchSound();
		}
	}
	else if (event & MOUSE_LEFT_UP) {
		left_button_hold_down = 0;
	}
	else if (event & MOUSE_RIGHT_DOWN) {
	}
}

void expandMaskToImage(uint16 m[16], byte *p, uint32 color, int width, int height) {
	int i, j;
	byte * d = p;
	for (i = 0; i<height; i++) {
		for (j = 0; j<width; j++) {
			d = p + (i * width + j) * SCREEN_BPP;
			/* 以下改动部分目的为将8位屏幕鼠标移植至32位屏幕 */
			if (m[i] & 1 << (width - 1 - j)) {
				*d = (unsigned char)(color % 0x100);
				*(d + 1) = (unsigned char)((color / 0x100) % 0x100);
				*(d + 2) = (unsigned char)(color / 0x10000);
				*(d + 3) = (unsigned char)0x00;
			}
			else {
				*d = (unsigned char)0x00;
				*(d + 1) = (unsigned char)0x00;
				*(d + 2) = (unsigned char)0x00;
				*(d + 3) = (unsigned char)0x00;
			}
		}
	}
}

void buildMouseImage(void) {
	mouse.background = malloc(imagesize(0, 0, MOUSE_SIZE - 1, MOUSE_SIZE - 1));
	mouse.mask = malloc(imagesize(0, 0, MOUSE_SIZE - 1, MOUSE_SIZE - 1));
	mouse.img = malloc(imagesize(0, 0, MOUSE_SIZE - 1, MOUSE_SIZE - 1));
	mouse.mask->picwidth = mouse.mask->picheight = MOUSE_SIZE;
	mouse.img->picwidth = mouse.img->picheight = MOUSE_SIZE;
	mouse.mask->bpp = mouse.mask->bpp = mouse.background->bpp = SCREEN_BPP;
	expandMaskToImage(screenMask, &mouse.mask->buffer, __WHITE, MOUSE_SIZE, MOUSE_SIZE);
	expandMaskToImage(cursorMask, &mouse.img->buffer, __WHITE, MOUSE_SIZE, MOUSE_SIZE);
}

void saveMouseBackground(int x, int y) {
	getimage(x, y, x + MOUSE_SIZE - 1, y + MOUSE_SIZE - 1, mouse.background);
	mouse.x = x;
	mouse.y = y;
}

void paintMouse(int x, int y) {
	putimage(x, y, mouse.mask, AND_PUT);
	putimage(x, y, mouse.img, OR_PUT);
}

void recMouseBackground(void) {
	putimage(mouse.x, mouse.y, mouse.background, COPY_PUT);
}

void moveMouse(int x, int y) {
	recMouseBackground();
	saveMouseBackground(x, y);
	paintMouse(x, y);
}

int initMouse(void) {
	int x = 0, y = 0;
	union REGS r;
	struct SREGS sr;

	r.w.ax = 0;      /* check mouse driver */
	int86(0x33, &r, &r);
	if (r.w.ax != 0xFFFF)
		return 0;

	r.w.ax = 0x0007; /* set horizontal range */
	r.w.cx = 0;
	r.w.dx = _width - 1;
	int86(0x33, &r, &r);
	r.w.ax = 0x0008; /* set vertical range */
	r.w.cx = 0;
	r.w.dx = _height - 1;
	int86(0x33, &r, &r);

	r.w.ax = 0x0004; /* position cursor */
	r.w.cx = x;
	r.w.dx = y;
	int86(0x33, &r, &r);

	r.w.ax = 2;      /* hide cursor */
	int86(0x33, &r, &r);

	r.w.ax = 0x0014; /* install mouse event handler */
	r.w.cx = MOUSE_MOVE | MOUSE_LEFT_DOWN | MOUSE_LEFT_UP | MOUSE_RIGHT_DOWN | MOUSE_RIGHT_UP; /* monitor these events */
	r.x.edx = FP_OFF(mouseEvent);
	memset(&sr, 0, sizeof(sr));
	sr.es = FP_SEG(mouseEvent);
	int86x(0x33, &r, &r, &sr);
	oldMouseEvent = MK_FP(sr.es, r.x.edx);

	buildMouseImage();
	saveMouseBackground(x, y);
	moveMouse(x, y);

	return 1;
}

void closeMouse(void) {
	union REGS r;
	struct SREGS sr;
	r.w.ax = 0x0014; /* install mouse event handler */
	r.w.cx = 0;      // DO NOT monitor any events!!!
	r.x.edx = FP_OFF(oldMouseEvent);
	memset(&sr, 0, sizeof(sr));
	sr.es = FP_SEG(oldMouseEvent);
	int86x(0x33, &r, &r, &sr);
	free(mouse.background);
	free(mouse.mask);
	free(mouse.img);
}

/* 判断点(x,y)是否在button范围内 */
int inButton(int x, int y, button * b) {
	rect * a = &b->r;
	return (x >= a->x && (x <= a->x + a->w) && y >= a->y && (y <= a->y + a->h));
}
