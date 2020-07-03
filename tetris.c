/*
 * FileName: tetris.c
 * Tetris is a Tetris game program that can run in Turbo C environment. 
 * In Chinese, Tetris is called fangkuai. Therefore, fangkuai or FK are used as identifiers in the program
 * 
 */
 
/*alter the main function*/
#define  DIM  20       
/*every bar's dimension*/
#define  NUM  20       
/*number of bars on a row */
#define  STY  23       
/*number of sorts of fangkuai*/
#define  BOX 4         
/*number of boxes from one fangkuai*/
#define  SPEED        1000000
#define  N_of_Color      15
#define  N_of_Fillstyle  9
#define  RIGHT_KEY   19712
#define  LEFT_KEY    19200
#define  UP_KEY      18432  
/* anti clockwise translation*/
#define  DOWN_KEY    20480  
/* clockwise translation */
#define  ENTER_KEY   7181   
/* get down completely */
#define  BLANK_KEY    14624
#define  ESC_KEY     283    
/* quit the game */
#define  NEW         -2     
/*return when creating a new fangkuai*/
#define  UP          -1        
/*when do anti-clockwise turn, use it*/
#define  OK          1         
/*if action succeed executing ,return it*/
#define  FAILURE     0     
/* if the action is refused, return it*/
#define  DOWN        1     
/*do clockwise turn ,use it*/
#define  FALL        2        
/*fall*/
#define  RIGHT       3      
/* move toward right*/
#define  LEFT        4       
/* move toward left*/
#define  ZHUAN       5     
/*turn*/
#include "graphics.h"
#include "math.h"
#include "conio.h"
#include "stdlib.h"
#include "bios.h"
#include "stdio.h"
 int x1=0, x2=600, y1=0, y2=400, speed=SPEED;
int screen[NUM+6][NUM+6];
int rand1,rand2=-1,color1,color2=-1,style1,style2=-1,*p1,*p2=NULL;
FILE  *fp;
static int x[NUM];
static fillmode[9]= {
	SOLID_FILL,
	 LINE_FILL,
	 LTSLASH_FILL,
	 SLASH_FILL,
	 LTBKSLASH_FILL,
	 HATCH_FILL,
	 XHATCH_FILL,
	 CLOSE_DOT_FILL,
	 INTERLEAVE_FILL,
}
;
static int mat[STY][BOX][BOX]= { { {
			0,1,0,0
		}
		, {
			0,1,0,0
		}
		, {
			0,1,1,0
		}
		, {
			0,0,0,0
		}
	}
	, { {
			0,1,1,1
		}
		, {
			0,1,0,0
		}
		, {
			0,0,0,0
		}
		, {
			0,0,0,0
		}
	}
	, { {
			0,1,1,0
		}
		, {
			0,0,1,0
		}
		, {
			0,0,1,0
		}
		, {
			0,0,0,0
		}
	}
	, { {
			0,0,0,1
		}
		, {
			0,1,1,1
		}
		, {
			0,0,0,0
		}
		, {
			0,0,0,0
		}
	}
	, { {
			0,0,1,0
		}
		, {
			0,0,1,0
		}
		, {
			0,1,1,0
		}
		, {
			0,0,0,0
		}
	}
	, { {
			0,1,0,0
		}
		, {
			0,1,1,1
		}
		, {
			0,0,0,0
		}
		, {
			0,0,0,0
		}
	}
	, { {
			0,1,1,0
		}
		, {
			0,1,0,0
		}
		, {
			0,1,0,0
		}
		, {
			0,0,0,0
		}
	}
	, { {
			0,1,1,1
		}
		, {
			0,0,0,1
		}
		, {
			0,0,0,0
		}
		, {
			0,0,0,0
		}
	}
	, { {
			0,1,0,0
		}
		, {
			0,1,1,0
		}
		, {
			0,1,0,0
		}
		, {
			0,0,0,0
		}
	}
	, { {
			0,1,1,1
		}
		, {
			0,0,1,0
		}
		, {
			0,0,0,0
		}
		, {
			0,0,0,0
		}
	}
	, { {
			0,0,1,0
		}
		, {
			0,1,1,0
		}
		, {
			0,0,1,0
		}
		, {
			0,0,0,0
		}
	}
	, { {
			0,0,1,0
		}
		, {
			0,1,1,1
		}
		, {
			0,0,0,0
		}
		, {
			0,0,0,0
		}
	}
	, { {
			0,1,1,1
		}
		, {
			0,1,1,0
		}
		, {
			0,0,0,0
		}
		, {
			0,0,0,0
		}
	}
	, { {
			0,1,1,0
		}
		, {
			0,1,1,0
		}
		, {
			0,0,1,0
		}
		, {
			0,0,0,0
		}
	}
	, { {
			0,0,1,1
		}
		, {
			0,1,1,1
		}
		, {
			0,0,0,0
		}
		, {
			0,0,0,0
		}
	}
	, { {
			0,0,1,0
		}
		, {
			0,0,1,1
		}
		, {
			0,0,1,1
		}
		, {
			0,0,0,0
		}
	}
	, { {
			0,0,0,1
		}
		, {
			0,0,1,1
		}
		, {
			0,0,1,1
		}
		, {
			0,0,0,0
		}
	}
	, { {
			0,0,0,0
		}
		, {
			0,1,1,0
		}
		, {
			0,1,1,1
		}
		, {
			0,0,0,0
		}
	}
	, { {
			0,1,1,0
		}
		, {
			0,1,1,0
		}
		, {
			0,1,0,0
		}
		, {
			0,0,0,0
		}
	}
	, { {
			0,1,1,1
		}
		, {
			0,0,1,1
		}
		, {
			0,0,0,0
		}
		, {
			0,0,0,0
		}
	}
	, { {
			0,1,0,0
		}
		, {
			0,1,0,0
		}
		, {
			0,1,0,0
		}
		, {
			0,1,0,0
		}
	}
	, { {
			1,1,1,1
		}
		, {
			0,0,0,0
		}
		, {
			0,0,0,0
		}
		, {
			0,0,0,0
		}
	}
	, { {
			0,1,1,0
		}
		, {
			0,1,1,0
		}
		, {
			0,0,0,0
		}
		, {
			0,0,0,0
		}
	}
}
;
/*Draw the background for the game*/
void enviro() {
	/*using Quanju variables*/
	int driver, mode;
	driver=DETECT;
	registerbgidriver(EGAVGA_driver);
	initgraph(&driver,&mode,"");
	clearviewport();
	setviewport(x1,y1,x2,y2,1);
	setbkcolor(BLUE);
	setcolor(YELLOW);
	randomize();
}
void infor () {
	setcolor(LIGHTGREEN);
	settextstyle(0,HORIZ_DIR,2);
	outtextxy(460, 50, "NEXT");
	settextstyle(0,HORIZ_DIR,1);
	outtextxy(410,210,"Your Score is");
	outtextxy(430,380,"Cheng Yunhua 2006");
}
void frame() {
	/*using Quanju variables*/
	setfillstyle(SOLID_FILL,BROWN);
	bar(401,1,599,399);
	setfillstyle(SOLID_FILL,YELLOW);
	rectangle(518,198,582,222);
	setfillstyle(SOLID_FILL,CYAN);
	bar(401,1,599,190);
	line(400,190,600,190);
	setcolor(YELLOW);
	rectangle(x1,y1,x2,y2);
	setfillstyle(SOLID_FILL, DARKGRAY);
	bar(401,230,599,370);
	outtextxy(410,240, "HINTS");
	setcolor(WHITE);
	settextstyle(2,HORIZ_DIR, 4);
	outtextxy(420,250, "ESC: quit the game anytime");
	outtextxy(420,265, "BLANK:arrive at the bottom");
	outtextxy(420,280,"UP: turn it anti-clockwise");
	outtextxy(420,295,"DOWN: turn it clockwise");
	outtextxy(420,310,"RIGHT:move towards right");
	outtextxy(420,325,"LEFT: move towards left");
	outtextxy(420,340,"ENTER:drop in normal speed");
	line(x1+400,y1,x1+400,y2);
}
/*make selection for different levels*/
int select() {
	enviro();
	frame();
	infor ();
	setfillstyle(SOLID_FILL, GREEN);
	bar(35,125,365,305);
	setfillstyle(SOLID_FILL, DARKGRAY);
	bar(40,130,360,300);
	settextstyle(0,HORIZ_DIR, 2);
	outtextxy(70,150,"EASY--------[1]");
	outtextxy(70,190,"NORMAL------[2]");
	outtextxy(70,230,"HARDER------[3]");
	outtextxy(70,270,"HARDEST-----[4]");
	settextstyle(0,HORIZ_DIR,1);
	setcolor(RED);
	outtextxy(180,350,"Input A Number to Select");
	outtextxy(180,370,"Press Enter For Exercise");
	switch(bioskey(0)) {
		case  561               :   return 1;
		case  818               :   return 2;
		case  1075              :   return 3;
		case  1332              :   return 4;
		case  ENTER_KEY         :   return 5;
		case  ESC_KEY           :   return 6;
		default                 :   ;
	}
	return FAILURE;
}
/*Draw a fangkuai*/
void drawfk(int x0, int y0,int rand,int style, int color, int flag) {
	int i,j;
	setfillstyle(style, color);
	for (i=0;i<BOX;i++)
		for (j=0;j<BOX;j++)
		 if(mat[rand][i][j]==1) {
		if(flag==1) setcolor(BLUE); else    setcolor(color);
		bar(x0+j*20+1,y0+i*20+1,x0+(j+1)*20-1,y0+(i+1)*20-1);
		if(flag==1) setcolor(BLUE); else    setcolor(YELLOW);
		rectangle(x0+j*20+1,y0+i*20+1,x0+(j+1)*20-1,y0+(i+1)*20-1);
	} else continue;
	setcolor(YELLOW);
	/* frame(); */
}
/*change the screen matrix after every act*/
int chascr(int x0, int y0,int rand,int temp) {
	int i,j,k,m,old_rand;
	k=(y0+60)/20;
	m=(x0+60)/20;
	switch(temp) {
		case  FAILURE:return  FAILURE;
		case  FALL:   for (i=k;i<k+BOX;i++)
							 for (j=m;j<m+BOX;j++)
							 if(mat[rand][i-k][j-m]==1) screen[i-1][j]=0; else continue;
		break;
		case  RIGHT:  for (i=k;i<k+BOX;i++)
							 for (j=m;j<m+BOX;j++)
							 if(mat[rand][i-k][j-m]==1) screen[i][j-1]=0; else continue;
		break;
		case  LEFT:   for (i=k;i<k+BOX;i++)
							 for (j=m;j<m+BOX;j++)
							 if(mat[rand][i-k][j-m]==1) screen[i][j+1]=0; else continue;
		break;
		case  UP:     old_rand=change(rand,DOWN);
		for (i=k;i<k+BOX;i++)
							 for (j=m;j<m+BOX;j++)
							 if(mat[old_rand][i-k][j-m]==1) screen[i][j]=0; else continue;
		break;
		case DOWN:    old_rand=change(rand,UP);
		for (i=k;i<k+BOX;i++)
							 for (j=m;j<m+BOX;j++)
							 if(mat[old_rand][i-k][j-m]==1) screen[i][j]=0; else continue;
		break;
		case  NEW:     ;
		/*when first draw a fangkuai, it also needs rewrite the screen matrix*/
		default: ;
	}
	for (i=k;i<k+BOX;i++)
	        for (j=m;j<m+BOX;j++)
				if(mat[rand][i-k][j-m]==1)
					screen[i][j]=1; else continue;
	return OK;
}
/*produce the random numbers,(random[i] produces number from 0~i-1)*/
int *initial(int  y0, int x[NUM], int  styles, int  colors, int fillstyles ) {
	int conditions[5], co,st;
	*conditions=y0;
	*(conditions+1)=((y0==460)?100:x[random(17)]);
	st=random(7);
	if(st<5)        *(conditions+2)=(4*st)+random(4); else if(st==5)  *(conditions+2)=(4*st)+random(2); else if(st==6)  *(conditions+2)=styles-1;
	*(conditions+3)=
	      (((co=random(colors+1))!=BLUE)&&(co!=BLACK))?co:(co+2);
	*(conditions+4)=(fillmode[random(fillstyles+1)]);
	return  conditions;
}
/*decide the action is effective or not*/
int action_decide(int  *x, int *y, int rand,int act) {
	int  i,j,temp,i0, j0;
	j0=(*x+60)/20;
	i0=(*y+60)/20;
	switch(act) {
		case FALL :
				for (i=0;i<BOX;i++)
				  for (j=0;j<BOX;j++) {
			if(mat[rand][i][j]!=0)
						  if((*y+20*i)>=380)  return FAILURE;
		}
		for (i=1;i<BOX;i++)
				  for (j=0;j<BOX;j++) {
			if(screen[i0+i][j0+j]==mat[rand][i][j])
					  temp=mat[rand][i][j]; else       temp=screen[i0+i][j0+j]+mat[rand][i-1][j];
			if(temp>1) return FAILURE;
		}
		for (j=0;j<BOX;j++) {
			temp=mat[rand][3][j]+screen[i0+4][j0+j];
			if(temp>1) return FAILURE;
		}
		return OK;
		case RIGHT :
				for (i=0;i<BOX;i++)
				  for (j=0;j<BOX;j++) {
			if(mat[rand][i][j]!=0)
					  if((*x+20*j)>=380)  return FAILURE;
		}
		for (i=0;i<BOX;i++)
					for (j=1;j<BOX;j++) {
			if(screen[i0+i][j0+j]==mat[rand][i][j])
					   temp=mat[rand][i][j]; else       temp=screen[i0+i][j0+j]+mat[rand][i][j-1];
			if(temp>1) return FAILURE;
		}
		for (i=0;i<BOX;i++) {
			temp=mat[rand][i][3]+screen[i0+i][j0+4];
			if(temp>1) return FAILURE;
		}
		return OK;
		case LEFT :
				  for (i=0;i<BOX;i++)
					 for (j=0;j<BOX;j++) {
			if(mat[rand][i][j]!=0)
						  if((*x+20*j)<=0)  return FAILURE;
		}
		for (i=0;i<BOX;i++)
					 for (j=0;j<BOX-1;j++) {
			if(screen[i0+i][j0+j]==mat[rand][i][j])
						 temp=mat[rand][i][j]; else       temp=screen[i0+i][j0+j]+mat[rand][i][j+1];
			if(temp>1) return FAILURE;
		}
		for (i=0;i<BOX;i++) {
			temp=mat[rand][i][0]+screen[i0+i][j0-1];
			/*j0-1 has no chance to be -1 since if j0==0, it has returned to main function*/
			if(temp>1) return FAILURE;
		}
		return OK;
		case ZHUAN:  if(rand==22)    return OK; else if(rand<20) {
			for (i=0;i<BOX-1;i++) {
				for (j=1;j<BOX;j++)
										  if(((mat[rand][i][j]-screen[i0+i][j0+j])!=0)||((*x+80)>400)||((*x+20)<0))
											return FAILURE;
			}
			return OK;
		}
		for (i=0;i<BOX;i++) {
			for (j=0;j<BOX;j++)
									if(((mat[rand][i][j]-screen[i0+i][j0+j])!=0)||((*x+80)>400)||((*x+20)<0))
									  return FAILURE;
		}
		return OK;
		default: return   FAILURE;
	}
}
/* change the fangkuai's to another direciton*/
int  change(int rand, int flag) {
	int a,rand_new;
	a=rand/4;
	rand_new=rand+flag;
	if(rand==22) rand_new=22;
	if(flag==DOWN) {
		if(rand==21) rand_new=20; else if((rand_new>=(a+1)*4)||(rand_new<=a*4))
										 rand_new=rand_new-4*flag;
	}
	if(flag==UP) {
		if(rand==20) rand_new=21; else if((rand_new>(a+1)*4)||(rand_new<a*4))
										 rand_new=rand_new-4*flag;
	}
	return rand_new;
}
/* single action funtion*/
int  action(int  *x, int *y, int *rand,int style,
			  int color, int act, int flag) {
	int i,j,i0,j0;
	j0=(*x+60)/20;
	i0=(*y+60)/20;
	if(action_decide(x, y, *rand, act)!=1)   return  FAILURE;
	drawfk(*x,*y,*rand,EMPTY_FILL,color,1);
	/*erase the previous one*/
	if(act==FALL) *y=(*y)+20; else if(act==RIGHT) *x=(*x)+20; else if(act==LEFT) *x=(*x)-20; else if(act==ZHUAN) *rand=change(*rand, flag);
	/*when only change the direction,  *x and *y are kept */
	drawfk(*x,*y,*rand,style,color,0);
	/*show the present fangkuai*/
	delay(speed);
	/*speed is an overall variable*/
	if(act==ZHUAN) return flag; else           return  act;
}
/*check the existing full rows and delete it*/
int check(int color,int style) {
	int i,j,k,value,happen=0;
	for (i=NUM+2;i>=3;i--) {
		value=0;
		for (j=3;j<=NUM+2;j++) {
			if(screen[i][j]!=1) break;
			value=value+1;
		}
		if(value==20) {
			happen++;
			for (k=i;k>=3;k--)
							for (j=3;j<=NUM+2;j++)
							  screen[k][j]=screen[k-1][j];
		}
	}
	if(happen==0) return 0;
	setfillstyle(EMPTY_FILL, BLUE);
	bar(1,1,399,399);
	setfillstyle(style, color);
	for (i=3;i<=NUM+2;i++)
			for (j=3;j<=NUM+2;j++)
			  if(screen[i][j]==1) {
		bar(-60+j*20+1,-60+i*20+1,-60+(j+1)*20-1,-60+(i+1)*20-1);
		rectangle(-60+j*20+1,-60+i*20+1,-60+(j+1)*20-1,-60+(i+1)*20-1);
	} else continue;
	return happen;
	/* contribution to player's mark */
}
/*exam if a fangkuai has reach the bottom, and give score, or quit game */
int exam(int *x0, int *y0, float *score, int rand, int color, int style) {
	int a,j;
	float score_old;
	char marks[5];
	a=action_decide(x0,y0,rand,FALL);
	if(a==FAILURE) {
		*score=(*score)+0.1+5*check(color1, style1);
		/*give scores*/
		setfillstyle(SOLID_FILL,RED);
		bar(520,200,580,220);
		sprintf(marks,"%5.1f",*score);
		settextstyle(3,HORIZ_DIR,2);
		setcolor(YELLOW);
		outtextxy(530, 200, marks);
		if(*score>=100) {
			setfillstyle(SOLID_FILL,BROWN);
			bar(401,230,599,370);
			outtextxy(420,250,"You have Won!");
			outtextxy(430,300,"try harder level");
			getch();
			clearviewport();
			exit(0);
		}
		for (j=3;j<=NUM+2;j++)  
		/* if there are fangkuai in 1st row, quit or not*/
		if(screen[3][j]!=0) {
			setfillstyle(SOLID_FILL,BROWN);
			bar(401,230,599,370);
			outtextxy(440,250,"You have lost!");
			settextstyle(0, HORIZ_DIR,5);
			outtextxy(100,200, "LOSE");
			settextstyle(3,HORIZ_DIR, 2);
			while(!kbhit()) {
				bar(470,300,530,330);
				outtextxy(475,300,"TRY");
				delay(speed*10);
				bar(460,300,530,330);
				outtextxy(470,300,"AGAIN");
				delay(10*speed);
			}
			clearviewport();
			exit(0);
		}
	}
	return   a;
}
/*when bioskey(1)!=0, main funtion will transfer to this funtion*/
int do_action(int score, int choice, int ch, int *level, int *x0, int *y0, int *rand, int style, int color) {
	int act_return, utimate_n=(choice!=5)?(40/choice):20;
	float score_old;
	if(*level>utimate_n)   return FAILURE;
	while((ch!=0)&&(*level<=utimate_n)) {
		switch(ch) {
			case  RIGHT_KEY    : if(action_decide(x0, y0, *rand,FALL)==1) {
				act_return=action(x0,y0,rand,style,color,RIGHT,0);
				chascr(*x0,*y0,*rand,act_return);
			}
			break;
			case  LEFT_KEY     : if(action_decide(x0,y0,*rand, FALL)==1) {
				act_return=action(x0,y0,rand,style,color,LEFT,0);
				chascr(*x0,*y0,*rand,act_return);
			}
			break;
			case  UP_KEY       : if(action_decide(x0,y0,*rand,FALL)==1) {
				act_return=action(x0,y0,rand,style,color,ZHUAN,UP);
				chascr(*x0,*y0,*rand,act_return);
				(*level)++;
			}
			break;
			case  DOWN_KEY  : if(action_decide(x0,y0,*rand,FALL)==1) {
				act_return=action(x0,y0,rand,style,color,ZHUAN,DOWN);
				chascr(*x0,*y0,*rand,act_return);
				(*level)++;
			}
			break;
			case  ENTER_KEY  :  return  FAILURE;
			/* use return value to control change speed's value or not !*/
			case  BLANK_KEY   :  return  OK;
			case  ESC_KEY      : clearviewport();
			exit(0);
			default            : ;
		}
		/*switch ends*/
		if(choice>=3) {
			if(bioskey(1)!=0)	ch=bioskey(0); else return FAILURE;
		}
		/*exercise (bigger speed) and harder,hardest*/
		if(choice<=2) {
			ch=bioskey(0);
			utimate_n=10;
		}
		/*easy and normal*/
		/*different bioskey function makes different!!*/
	}
	return  FAILURE;
}
/*the main function*/
int main() {
	int act_return, i,j,x0,y0;
	float score=0.;
	int level,choice;
	char *str;
	for (i=0;i<NUM;i++)
		 x[i]=i*DIM;
	/*initial the screen matrix*/
	for (i=0;i<NUM+6;i++)
		 for (j=0;j<NUM+6;j++)  screen[i][j]=0;
	for (;;) {
		choice=select();
		if(choice!=0) {
			if(choice<6) {
				if(choice<5) sprintf(str, "the %d-th level", choice); else {
					str="do exercise first";
					speed=100*SPEED;
				}
				settextstyle(0,HORIZ_DIR,1);
				setcolor(RED);
				outtextxy(440,20, str);
				setfillstyle(SOLID_FILL, BLUE);
				bar(1,1,399,399);
				break;
			} else if(choice==6) {
				clearviewport();
				exit(0);
			}
		}
	}
	while(1) {
		level=0;
		y0=-60;
		/*let the fangkuai start dropping from outside the window*/
		act_return=NEW;
		p1=initial(y0, x, STY, N_of_Color, N_of_Fillstyle);
		x0=*(p1+1);
		if(p2==NULL) {
			rand1=*(p1+2);
			color1=*(p1+3);
			style1=*(p1+4);
		} else {
			rand1=rand2;
			color1=color2;
			style1=style2;
		}
		p2=initial(460, x, STY, N_of_Color, N_of_Fillstyle);
		rand2=*(p2+2);
		color2=*(p2+3);
		style2=*(p2+4);
		drawfk(460,100,rand2,style2,color2,0);
		drawfk(x0,y0,rand1,style1,color1,0);
		chascr(x0,y0,rand1,act_return);
		for (;;) {
			if(bioskey(1)!=0)
				 act_return=do_action(score, choice, bioskey(0), &level, &x0, &y0, &rand1, style1, color1);
			if(act_return==OK)   speed=100;
			act_return=action(&x0,&y0,&rand1,style1,color1,FALL,0);
			chascr(x0,y0,rand1,act_return);
			if(exam(&x0, &y0, &score, rand1, color1, style1)==0)   break;
		}
		/*for  ends */
		if(choice==5) speed=SPEED*100; else           speed=SPEED;
		setfillstyle(SOLID_FILL, CYAN);
		bar(460,100,540,180);
	}
	/*while ends */
}
/* main ends */
