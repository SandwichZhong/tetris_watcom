tetris.exe:
	WCL386 /fe=tetris.exe main.c tetris.c paint.c mouse.c key.c timer.c
#echo finished
#以上为一般makefile命令,去除关联的几个c文件是因为会导致重复编译链接
#原因可能是编译时会写入源代码文件,从而导致死循环...然而还是会结束,只是会重复编译6-8遍左右

code:
	-WCL386 /pc main.c > omain.c
	-WCL386 /pc tetris.c > otetris.c
	-WCL386 /pc timer.c > otimer.c
	-WCL386 /pc paint.c > opaint.c
	-WCL386 /pc mouse.c > omouse.c
	-WCL386 /pc key.c > okey.c
#以上生成各个c文件经预处理(保留注释)后的c代码,方便找预处理问题,比如有时候会有莫名其妙#include指令无效的问题
#比如有一次仅有mouse.c无法正确#include "def.h"

compile:
	-WCL386 main.c
	-WCL386 tetris.c
	-WCL386 timer.c
	-WCL386 paint.c
	-WCL386 mouse.c
	-WCL386 key.c
#以上逐个编译c文件并输出错误信息,方便改错

clean:
	-delete tetris.obj
	-delete paint.obj
	-delete mouse.obj
	-delete timer.obj
	-delete main.obj
	-delete key.obj
	-delete tetris.exe
	-delete omain.c
	-delete otimer.c
	-delete okey.c
	-delete omouse.c
	-delete otetris.c
	-delete opaint.c
#以上为清理makefile产物的命令
#实际上无法正确作用...原因不明...实测控制台手敲成功
