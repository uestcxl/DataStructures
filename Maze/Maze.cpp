#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STACK_INIT_SIZE 100
#define INCREMENT 10

/*  typedef int ElemType;  */


typedef struct{
    int r;
    int c;
}PosType;

typedef struct{
	int ord;          /* 通道块在路径上的序号  */
	PosType seat;    /*  通道块在迷宫中的“坐标位置”  */
	int di;           /*  从此通道块走向下一个通道块的“方向” */
}ElemType;

typedef struct{
    int arr[10][10];
}MazeType;


typedef struct SqStack
{
	ElemType *base;
	ElemType *top;
	int size;
}SqStack;

int initStack(SqStack *s)
{
	s->base = (ElemType *)malloc(STACK_INIT_SIZE*sizeof(ElemType) );
	if(!s->base)
		return -1;
	s->top = s->base;
	s->size = STACK_INIT_SIZE;
	return 0;
}

int getTop(SqStack s,ElemType *e)
{
	if(s.base!=s.top)
		*e = *(s.top-1);
	return -1;
}

int push(SqStack *s, ElemType e)
{
    if(s->top - s->base >= s->size)
    {
         s->base = (ElemType *)realloc(s->base, (s->size+INCREMENT)*sizeof(ElemType));
         if(!s->base)
            return -1;
         s->top = s->base+s->size;
         s->size += INCREMENT;
    }

    *s->top++ = e;
    return 0;
}

int pop(SqStack *s,ElemType *e)
{
    if(s->top == s->base)
        return -1;
    *e = *(--s->top);
    return 0;
}

int isEmpty(SqStack *s)
{
    if(s->base == s->top)
        return 1;
    else
        return 0;
}

int clearStack(SqStack *s)
{
	ElemType e;
	if(!s) return -1;
	if(s->base == s->top) return 0;
	while(!isEmpty(s))
	{
		pop(s,&e);
	}
	return 0;
}

int pass(MazeType MyMaze, PosType CurPos);
void footPrint(MazeType &MyMaze, PosType CurPos);
void markPrint(MazeType &MyMaze, PosType CurPos);
PosType nextPos(PosType CurPos, int Dir);


int pass( MazeType MyMaze,PosType CurPos) {
  if (MyMaze.arr[CurPos.r][CurPos.c]==' ')
    return 1;     // 如果当前位置是可以通过，返回1
  else return 0;  // 其它情况返回0
}
void footPrint(MazeType &MyMaze,PosType CurPos) {
  MyMaze.arr[CurPos.r][CurPos.c]='*';
}
void markPrint(MazeType &MyMaze,PosType CurPos) {
  MyMaze.arr[CurPos.r][CurPos.c]='!';
}

PosType nextPos(PosType CurPos, int Dir) {
  PosType ReturnPos;
  switch (Dir) {
    case 1:
        ReturnPos.r=CurPos.r;
        ReturnPos.c=CurPos.c+1;
        break;
    case 2:
        ReturnPos.r=CurPos.r+1;
        ReturnPos.c=CurPos.c;
        break;
    case 3:
        ReturnPos.r=CurPos.r;
        ReturnPos.c=CurPos.c-1;
        break;
    case 4:
        ReturnPos.r=CurPos.r-1;
        ReturnPos.c=CurPos.c;
        break;
  }
  return ReturnPos;
}


/* 迷宫函数  */
/* 判断是否存在一条从开口到结尾的路径 */
int mazePath(MazeType &maze, PosType start, PosType end)
{
	SqStack *s = (SqStack *)malloc(sizeof(SqStack));
	initStack(s);
	PosType curpos = start;  // 设定"当前位置"为"入口位置"
	ElemType e;
    int curstep = 1;     // 探索第一步
  do {
    if (pass(maze,curpos)) {  // 当前位置可通过，即是未曾走到过的通道块
      footPrint(maze,curpos); // 留下足迹
      e.di =1;
      e.ord = curstep;
      e.seat= curpos;
      push(s,e);              // 加入路径
      if (curpos.r == end.r && curpos.c==end.c)
        return 0;        // 到达终点（出口）
      curpos = nextPos(curpos, 1);        // 下一位置是当前位置的东邻
      curstep++;                          // 探索下一步
    } else {  // 当前位置不能通过
      if (!isEmpty(s)) {
        pop(s,&e);
        while (e.di==4 && !isEmpty(s)) {
          markPrint(maze,e.seat);
          pop(s,&e);    // 留下不能通过的标记，并退回一步
        } // while
        if (e.di<4) {
          e.di++;
          push(s, e);  // 换下一个方向探索
          curpos = nextPos(e.seat, e.di); // 当前位置设为新方向的相邻块
        } // if
      } // if
    } // else
  } while (!isEmpty(s) );
  return -1;
} // MazePath



int main()
{
    //printf("Hello world!");
	getchar();
    return 0;
}
