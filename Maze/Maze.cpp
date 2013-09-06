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
	int ord;          /* ͨ������·���ϵ����  */
	PosType seat;    /*  ͨ�������Թ��еġ�����λ�á�  */
	int di;           /*  �Ӵ�ͨ����������һ��ͨ����ġ����� */
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
    return 1;     // �����ǰλ���ǿ���ͨ��������1
  else return 0;  // �����������0
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


/* �Թ�����  */
/* �ж��Ƿ����һ���ӿ��ڵ���β��·�� */
int mazePath(MazeType &maze, PosType start, PosType end)
{
	SqStack *s = (SqStack *)malloc(sizeof(SqStack));
	initStack(s);
	PosType curpos = start;  // �趨"��ǰλ��"Ϊ"���λ��"
	ElemType e;
    int curstep = 1;     // ̽����һ��
  do {
    if (pass(maze,curpos)) {  // ��ǰλ�ÿ�ͨ��������δ���ߵ�����ͨ����
      footPrint(maze,curpos); // �����㼣
      e.di =1;
      e.ord = curstep;
      e.seat= curpos;
      push(s,e);              // ����·��
      if (curpos.r == end.r && curpos.c==end.c)
        return 0;        // �����յ㣨���ڣ�
      curpos = nextPos(curpos, 1);        // ��һλ���ǵ�ǰλ�õĶ���
      curstep++;                          // ̽����һ��
    } else {  // ��ǰλ�ò���ͨ��
      if (!isEmpty(s)) {
        pop(s,&e);
        while (e.di==4 && !isEmpty(s)) {
          markPrint(maze,e.seat);
          pop(s,&e);    // ���²���ͨ���ı�ǣ����˻�һ��
        } // while
        if (e.di<4) {
          e.di++;
          push(s, e);  // ����һ������̽��
          curpos = nextPos(e.seat, e.di); // ��ǰλ����Ϊ�·�������ڿ�
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
