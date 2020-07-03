/*
* A billiard game program that can run in Turbo C environment. 
* In Chinese, billiards are called Taiqiu, so Taiqi or TQ is an identifier in the program
*
*/

#include "graphics.h"
#include "math.h"
#include "conio.h"
#include "stdlib.h"
#include "bios.h"
#include "stdio.h"
#include "dos.h"
#define  RIGHT_KEY   19712
#define  LEFT_KEY    19200
#define  UP_KEY      18432
#define  DOWN_KEY    20480                          
/*above keys control the pole's direction*/
#define  ENTER_KEY   7181                           
/*to see the auxliary line for aiming*/
#define  BLANK_KEY   14624                          
/*hit the 0-th ball*/
#define  ESC_KEY     283                            
/*quit game */
#define  PLUS        3389                           
/*+ */
#define  MINUS       3117                           
/*- */
/* in fact  here + is = */
#define  HELP        9064                           
/*help menu display*/
#define  TOM         5236                           
/*choose TOM as your side*/
#define  JIM         9322                           
/*similar to above line*/
#define  PI          3.14159
#define  chang       200                            
/*pole's long, I don't know the IS*/
#define  babing      30                             
/*if you want, you can have a handle for the pole*/
#define  R           8
#define  L           20*sqrt(3)/2                   
/*some const for convenience */
#define  MCXS        0.998                          
/*friction coeficient when moving*/
#define  zero_speed  1                              
/*the smallist speed, when lower than this, don't redraw*/
#define  JIAODU    (ball[0].x-polexy[2])!=0?atan((ball[0].y-polexy[3])/(ball[0].x-polexy[2])): PI/2
#define  QIN          (polexy[0]-polexy[2])!=0?atan((polexy[1]-polexy[3])/(polexy[0]-polexy[2])):PI/2
#define  POLE      polexy[0],polexy[1],polexy[2],polexy[3] 
/*infact it needs to be defined */
struct {
	int color;
	int flag;
	/*ball's condition: outside or inside? */
	int number;
	/*ball's number*/
	float x;
	/*though c can only use integrity number for draw
																		 but we should use float for computation precision*/
	float y;
	float vx;
	float vy;
}
ball[16];
/*balls' characteristic quantities*/
struct {
	int x;
	int y;
}
xy[16];
/*coordinates for balls(1-14) to randomly choosing*/
int triangle[8];
/*triangle frame for putting balls for game*/
float linemz[4];
/*to abtain the coordinates of the aim line*/
float polexy[4]= {
	60,300,60+chang,300
}
;
/*initial coordinates for the pole*/
float power=5;
/*initial power to hit the ball*/
/*too big number will make floodfill ineffective*/
/*but I have tried overcome this problem */
int size,person;
/*size of a copied image,  person discripts which player are playing*/
struct {
	char name[3];
	int id;
	int x;
	int y;
	int color;
	/*apart from solo game, it represents the color of the ball one hits*/
	int hit;
	/*how many balls have been  in holes*/
	int win;
	/*win (1) or loss(-1), unknown (0)*/
}
player[3]= { {
		"TOM",1,10,200,  RED,0,0
	}
	, {
		"JIM",2,570,200, BLUE,0,0
	}
	, {
		"DIY",3,290,50,  YELLOW,0,0
	}
}
;
/*player's characteristic quantities*/
void *image1,*image2;
/*pointer for reserved images*/
float imagexyp[4],imagexym[4];
/*corner coordinates for the images*/
float  circlexy[6][2]= { {
		60,110
	}
	, {
		548,344
	}
	, {
		548,110
	}
	, {
		60,344
	}
	, {
		304,110
	}
	, {
		304,344
	}
}
;
/*holes of the table*/
float ball_x_old[16], ball_y_old[16];
/*primative coordinates of a ball before it moves*/
/*************************************************************/
void coordinate() {
	xy[0].x=140;
	xy[0].y=227;
	/*white ball's position at beginning by IS*/
	xy[1].x=50+381;
	xy[1].y=100+127;
	xy[2].x=xy[1].x+L;
	xy[2].y=xy[1].y+10;
	xy[3].x=xy[1].x+L;
	xy[3].y=xy[1].y-10;
	xy[4].x=xy[3].x+L;
	xy[4].y=xy[3].y-10;
	xy[15].x=xy[4].x;
	xy[15].y=xy[4].y+20;
	xy[5].x=xy[15].x;
	xy[5].y=xy[15].y+20;
	/*black ball's position at beginning*/
	xy[6].x=xy[5].x+L;
	xy[6].y=xy[5].y+10;
	xy[7].x=xy[6].x;
	xy[7].y=xy[6].y-20;
	xy[8].x=xy[7].x;
	xy[8].y=xy[7].y-20;
	xy[9].x=xy[8].x;
	xy[9].y=xy[8].y-20;
	xy[10].x=xy[9].x+L;
	xy[10].y=xy[9].y-10;
	xy[11].x=xy[10].x;
	xy[11].y=xy[10].y+20;
	xy[12].x=xy[11].x;
	xy[12].y=xy[11].y+20;
	xy[13].x=xy[12].x;
	xy[13].y=xy[12].y+20;
	xy[14].x=xy[13].x;
	xy[14].y=xy[13].y+20;
	triangle[0]=405;
	triangle[1]=227;
	triangle[2]=515;
	triangle[3]=227+110/sqrt(3);
	triangle[4]=515;
	triangle[5]=227-110/sqrt(3);
	triangle[6]=405;
	triangle[7]=227;
	/*triangle's coordinates*/
}
/*give the initial coordinates and the triangle*/
/**************************************************************/
void enviro() {
	int driver, mode;
	driver=DETECT;
	registerbgidriver(EGAVGA_driver);
	initgraph(&driver,&mode,"");
	clearviewport();
	setviewport(0,0,600,400,1);
	setfillstyle(LTBKSLASH_FILL,RED);
	bar(0,0,600,400);
	setfillstyle(SOLID_FILL,CYAN);
	bar(5,40,595,395);
	setfillstyle(SOLID_FILL,BLUE);
	bar(5,5,595,35);
	outtextxy(20,20,"[ESC]-QUIT   [H]-HELP");
	outtextxy(400,20,"Made by Cheng Yunhua");
	rectangle(50,45,170, 65);
	outtextxy(10,227,"TOM");
	outtextxy(570,227,"JIM");
	outtextxy(290,80,"DIY");
	settextstyle(0,0,3);
	setcolor(RED);
	outtextxy(200,10,"C TAIQIU");
	randomize();
}
/*give the enviroment  for the game*/
/******************************************************************/
void drawhole() {
	int i;
	setfillstyle(XHATCH_FILL,RED);
	setcolor(BLACK);
	for (i=0;i<6;i++)
	 pieslice(circlexy[i][0],circlexy[i][1], 0, 360, 10);
	/*pieslice is a good alternative when floodfill is ineffective*/
	/*but sometimes it doesn't display well,infact it also use */
	/*floodfill function as sub-routine */
}
/* draw the holes in the table*/
/*****************************************************************/
void  drawtable() {
	setbkcolor(BLACK);
	setcolor(BLACK);
	setfillstyle(SOLID_FILL,RED);
	bar(40,90,568,364);
	/*table outter dimension */
	setfillstyle(SOLID_FILL,GREEN);
	bar(50,100,558,354);
	/*table inner dimension */
	drawhole();
}
/*draw the table*/
/******************************************************************/
int *suijishu(int n) {
	static int series[20];
	/*one should alter the array 's dimesion to fit the requirement*/
	int number,flag,i,j;
	for (i=1;i<n+1;i++) {
		number=random(n)+1;
		flag=0;
		for (j=0;j<i;j++)
				if(number==series[j]) {
			flag=1;
			break;
		}
		if(flag==1) {
			i--;
			continue;
		}
		series[i]=number;
	}
	return series;
}
/*produce random number series for putting the ball randomly*/
/*here I formulate a good funtion to generate randomly arranged */
/*series int numbers from 0 to n*/
/***************************************************************/
void drawpole(int color1, int color2) {
	setcolor(color1);
	setlinestyle(0,0,3);
	line(POLE);
	setcolor(color2);
	/*line(polexy[2]-(polexy[2]-polexy[0]>0?1:-1)*10*fabs(cos(QIN)),
		  polexy[3]-(polexy[3]-polexy[1]>0?1:-1)*10*fabs(sin(QIN)),polexy[2],polexy[3]);*/
	/*show a red front point for the pole if you like it*/
}
/*draw the pole after every motion*/
/**************************************************************/
void drawmz() {
	setcolor(BLACK);
	setlinestyle(3,0,1);
	line(linemz[0], linemz[1], linemz[2], linemz[3]);
}
/*draw the aim auxilary line*/
/*************************************************************/
void drawball(int i, int flag) {
	int  color;
	char  *id;
	sprintf(id,"%d",ball[i].number);
	if(flag==0)   color=GREEN; else color=ball[i].color;
	setcolor(color);
	settextstyle(0,HORIZ_DIR,0);
	setlinestyle(0,0,1);
	setfillstyle(SOLID_FILL, color);
	if(flag==1) {
		circle(ball[i].x, ball[i].y,R);
		floodfill(ball[i].x, ball[i].y, color);
		setcolor(WHITE);
		outtextxy(ball[i].x-2, ball[i].y-2, id);
	}
	/*draw the balls*/ else {
		circle(ball_x_old[i], ball_y_old[i],R);
		floodfill(ball_x_old[i], ball_y_old[i], color);
	}
	/*erase the balls*/
}
/*draw the 16 balls after every motion*/
/****************************************************************/
void lidu(int i) {
	setfillstyle(SOLID_FILL,CYAN);
	bar(60,50,60+10*power,60);
	/*erase the power label*/
	if(i==-1)  power--;
	if(i==1 )  power++;
	if(power>=10)  power=10;
	if(power<=1)  power=1;
	setfillstyle(SOLID_FILL, YELLOW);
	bar(60,50,60+10*power,60);
	/*re-draw the power label*/
}
/*control the power of the pole */
/**************************************************************/
void  putball() {
	int i=0,*p;
	for (;i<16;i++) {
		ball[i].color=(i==0?WHITE:(i==15?BLACK:(i<8?RED:BLUE)));
		ball[i].flag=1;
		ball[i].number=(i<8?i:(i<15?i-7:8));
		ball[i].vx=ball[i].vy=0;
	}
	/*decide the color,flag,number,and initial velocity*/
	coordinate();
	p=suijishu(14);
	ball[0].x=xy[0].x;
	ball[0].y=xy[0].y;
	ball[15].x=xy[15].x;
	ball[15].y=xy[15].y;
	for (i=1;i<=14;i++) {
		ball[i].x=xy[*(p+i)].x;
		ball[i].y=xy[*(p+i)].y;
	}
	/*randomly arrange the balls*/
	for (i=0; i<16; i++)  drawball(i, 1);
	setcolor(BLACK);
	setlinestyle(0,0,3);
	drawpoly(4, triangle);
	/*draw the triangle*/
	drawpole(BLACK,RED);
}
/*draw the initial condtions of the 16 ball  and the pole for a game*/
/*******************************************************************/
void copypole() {
	imagexyp[0]=(polexy[0]<polexy[2]?polexy[0]:polexy[2]);
	imagexyp[2]=(polexy[0]>polexy[2]?polexy[0]:polexy[2]);
	imagexyp[1]=(polexy[1]<polexy[3]?polexy[1]:polexy[3]);
	imagexyp[3]=(polexy[1]>polexy[3]?polexy[1]:polexy[3]);
	/*remember the getimage and putimage can     */
	/*only deal with image which is smaller than */
	/*64k, which is a rather smaller number      */
	/*one should assure the left-upper coorner   */
	/*coordinates  are rightly chosen            */
	/*line has dimesion, one must consider that  */
	imagexyp[0]=(imagexyp[0]<=2)?2:((imagexyp[0]>=598)?598:imagexyp[0]);
	imagexyp[1]=(imagexyp[1]<=2)?2:((imagexyp[1]>=398)?398:imagexyp[1]);
	imagexyp[2]=(imagexyp[2]<=2)?2:((imagexyp[2]>=598)?598:imagexyp[2]);
	imagexyp[3]=(imagexyp[3]<=2)?2:((imagexyp[3]>=398)?398:imagexyp[3]);
	size=imagesize(imagexyp[0]-2,imagexyp[1]-2,imagexyp[2]+2,imagexyp[3]+2);
	image1=(void *)malloc(size);
	getimage(imagexyp[0]-2,imagexyp[1]-2,imagexyp[2]+2,imagexyp[3]+2,image1);
}
/*copy the pole's background before draw it*/
/*******************************************************************/
void copymz() {
	imagexym[0]=(linemz[0]<linemz[2]?linemz[0]:linemz[2]);
	imagexym[2]=(linemz[0]>linemz[2]?linemz[0]:linemz[2]);
	imagexym[1]=(linemz[1]<linemz[3]?linemz[1]:linemz[3]);
	imagexym[3]=(linemz[1]>linemz[3]?linemz[1]:linemz[3]);
	imagexym[0]=(imagexym[0]<=2)?2:((imagexym[0]>=598)?598:imagexym[0]);
	imagexym[1]=(imagexym[1]<=2)?2:((imagexym[1]>=398)?398:imagexym[1]);
	imagexym[2]=(imagexym[2]<=2)?2:((imagexym[2]>=598)?598:imagexym[2]);
	imagexym[3]=(imagexym[3]<=2)?2:((imagexym[3]>=398)?398:imagexym[3]);
	size=imagesize(imagexym[0]-2,imagexym[1]-2,imagexym[2]+2,imagexym[3]+2);
	image2=(void *)malloc(size);
	getimage(imagexym[0]-2,imagexym[1]-2,imagexym[2]+2,imagexym[3]+2,image2);
}
/*copy the aim-line's background before draw it*/
/****************************************************************/
void coverpole() {
	putimage(imagexyp[0]-2,imagexyp[1]-2,image1,0);
	free(image1);
}
/*erase the pole before move it to another position*/
/****************************************************************/
void covermz() {
	putimage(imagexym[0]-2,imagexym[1]-2,image2,0);
	free(image2);
}
/*similar to above function, in fact they should be one funtion!!*/
/****************************************************************/
int hitball() {
	float v=power;
	do {
		coverpole();
		if(pow(polexy[2]-ball[0].x,2.)+pow(polexy[3]-ball[0].y,2.)<=100)
					return  0;
		/*only hit white ball*/
		polexy[2]=polexy[2]+(ball[0].x-polexy[0]>0?1:-1)*v*fabs(cos(JIAODU));
		polexy[3]=polexy[3]+(ball[0].y-polexy[1]>0?1:-1)*v*fabs(sin(JIAODU));
		polexy[0]=polexy[0]+(ball[0].x-polexy[0]>0?1:-1)*v*fabs(cos(JIAODU));
		polexy[1]=polexy[1]+(ball[0].y-polexy[1]>0?1:-1)*v*fabs(sin(JIAODU));
		copypole();
		drawpole(BLACK,RED);
	}
	while(1);
}
/*hit 0-th ball*/
/********************************************************************/
void help( ) {
	void *image;
	int size;
	size=imagesize(126,49,380,381);
	image=(void *)malloc(size);
	getimage(126,49,380,381,image);
	setcolor(WHITE);
	setlinestyle(0,0,2);
	setfillstyle(SOLID_FILL,WHITE);
	bar(127,50,379,380);
	setfillstyle(SOLID_FILL,BLUE);
	bar(131,54,375,376);
	line(137,340,369,340);
	line(140,90,260,90);
	line(140,370,369,370);
	setcolor(YELLOW);
	settextstyle(0,HORIZ_DIR,1);
	/*remember only font type 0's dimention is invariable */
	outtextxy(150,80,"HELP CONTENT");
	/*any others are relatively changed for your number */
	settextstyle(0,HORIZ_DIR,0);
	outtextxy(140,110,"Do it Youself.......Any key");
	outtextxy(140,140,"Take Jim Side.............J");
	outtextxy(140,170,"Take Tom Side.............T");
	outtextxy(140,200,"Alter Power...........-   =");
	outtextxy(140,230,"Alter Pole....Arrow(+Shift)");
	outtextxy(140,260,"Aim Line..........Enter Key");
	outtextxy(140,290,"Hit Ball..........Blank Key");
	outtextxy(140,320,"Quit Game...........ESC Key");
	setcolor(CYAN);
	outtextxy(140,350,"Made By Cheng Yunhua(2006/5)");
	if(bioskey(0)) {
		putimage(126,49,image,0);
		free(image);
	}
}
/*help system fot the game*/
/*****************************************************************/
int alterpole() {
	int i=0,j,key;
	for (;;)
	 if(bioskey(1)!=0) {
		key=bioskey(2);
		j=1+4*((key & 0x02)||(key & 0x01));
		switch(bioskey(0)) {
			case  HELP:             help();
			i=-1;
			break;
			case  RIGHT_KEY:        polexy[2]=polexy[2]+j;
			break;
			case  LEFT_KEY:         polexy[2]=polexy[2]-j;
			break;
			case  UP_KEY :          polexy[3]=polexy[3]-j;
			break;
			case  DOWN_KEY:         polexy[3]=polexy[3]+j;
			break;
			case  ENTER_KEY:        i=1;
			break;
			case  BLANK_KEY:        i=2;
			break;
			case  PLUS:             lidu(1);
			i=-1;
			break;
			case  MINUS:            lidu(-1);
			i=-1;
			break;
			case  ESC_KEY :         clearviewport();
			exit(0);
			default:  ;
		}
		if(i==-1) {
			i=0;
			continue;
		}
		if(i==1) {
			linemz[0]=ball[0].x+(polexy[2]-polexy[0]>0?1:-1)*400*fabs(cos(QIN));
			linemz[1]=ball[0].y+(polexy[3]-polexy[1]>0?1:-1)*400*fabs(sin(QIN));
			linemz[2]=ball[0].x;
			linemz[3]=ball[0].y;
			copymz();
			drawmz();
			delay(100000);
			covermz();
			i=0;
			continue;
		} else  if(i==2)  return i;
		polexy[0]=polexy[2]+(-ball[0].x+polexy[2]>0?1:-1)*chang*fabs(cos(JIAODU));
		polexy[1]=polexy[3]+(-ball[0].y+polexy[3]>0?1:-1)*chang*fabs(sin(JIAODU));
		coverpole();
		copypole();
		drawpole(BLACK, RED);
	}
}
/*alter the pole,power, to see the help etc.*/
/*******************************************************************/
void kaiqiu() {
	int key,i=0;
	lidu(0);
	setcolor(RED);
	settextstyle(0,0,1);
	outtextxy(200,60,"PRESS ANY KEY TO START");
	if(bioskey(0)!=0) {
		setcolor(CYAN);
		outtextxy(200,60,"PRESS ANY KEY TO START");
		start:	  while(!kbhit()) {
			setcolor(RED);
			outtextxy(200,60,"Select Your Side,  Press H for help");
			setcolor(CYAN);
			outtextxy(200,60,"Select Your Side,  Press H for help");
			delay(100);
		}
		if((key=bioskey(0))!=0) {
			settextstyle(0,HORIZ_DIR,3);
			switch(key) {
				case  HELP:     help();
				i=1;
				break;
				case  ESC_KEY:  clearviewport();
				exit(0);
				case  TOM:      person=player[0].id;
				break;
				/*TOM plays blue side*/
				case  JIM:	    person=player[1].id;
				break;
				/*JIM plays red side */
				default:        person=player[2].id;
				/*DO IT YOURSELF*/
			}
			if(i==1) {
				i=0;
				goto start;
			}
			setcolor(player[person-1].color);
			outtextxy(player[person-1].x, player[person-1].y,"\002");
		}
	}
	setcolor(GREEN);
	setlinestyle(0,0,3);
	drawpoly(4,triangle);
	drawpole(GREEN,GREEN);
}
/*start the game*/
/********************************************************************/
void play() {
	polexy[0]=polexy[2]+(-ball[0].x+polexy[2]>0?1:-1)*chang*fabs(cos(JIAODU));
	polexy[1]=polexy[3]+(-ball[0].y+polexy[3]>0?1:-1)*chang*fabs(sin(JIAODU));
	copypole();
	drawpole(BLACK,RED);
	alterpole();
	hitball();
	ball[0].vx=power*(ball[0].x-polexy[2]>0?1:-1)*fabs(cos(QIN));
	ball[0].vy=power*(ball[0].y-polexy[3]>0?1:-1)*fabs(sin(QIN));
}
/*hit the white ball for the first time at the beginning of a game*/
/*****************************************************************/
void collision(int i, int j) {
	float   vi_p,  vi_c, vj_p, vj_c, vxd_x,vxd_y, vxd_p,rxd, xxd, yxd;
	float    s,c;
	s=(ball[i].x-ball[j].x)!=0?atan((ball[i].y-ball[j].y)/(ball[i].x-ball[j].x)):PI/2;
	if(ball[i].x<ball[j].x)  c=PI; else                     c=0;
	s=s+c;
	vxd_x=ball[i].vx-ball[j].vx;
	vxd_y=ball[i].vy-ball[j].vy;
	vxd_p=vxd_x*cos(s)+vxd_y*sin(s);
	if(vxd_p<0) {
		vi_p=ball[i].vx*cos(s)+ball[i].vy*sin(s);
		vi_c=ball[i].vx*sin(-s)+ball[i].vy*cos(s);
		vj_p=ball[j].vx*cos(s)+ball[j].vy*sin(s);
		vj_c=ball[j].vx*sin(-s)+ball[j].vy*cos(s);
		ball[i].vx=vj_p*cos(s)+vi_c*sin(-s);
		ball[i].vy=vj_p*sin(s)+vi_c*cos(s);
		ball[j].vx=vi_p*cos(s)+vj_c*sin(-s);
		ball[j].vy=vi_p*sin(s)+vj_c*cos(s);
	}
	rxd=2*(R+2);
	xxd=rxd*cos(s);
	yxd=rxd*sin(s);
	ball[i].x=xxd+ball[j].x;
	ball[i].y=yxd+ball[j].y;
}
/*when two balls relative velocity and translation are oppsite
 they stand a chance to collide each other*/
/****************************************************************/
void baiqiuhuifang() {
	int i;
	setfillstyle(SOLID_FILL,CYAN);
	delay(100000);
	bar(ball[0].x-10, ball[0].y-10,ball[0].x+10,ball[0].y+10);
	ball[0].x=140;
	ball[0].y=227;
	ball[0].vx=0;
	ball[0].vy=0;
	ball[0].flag=1;
	for (i=1;i<16;i++)
			 if(ball[i].flag==1)
				if(pow(ball[i].x-ball[0].x,2)+pow(ball[i].y-ball[0].y,2)<=400) {
		ball[0].x++;
		i=1;
		continue;
	}
	drawball(0,1);
}
/*when white ball is in a hole, to deal with it*/
/***************************************************************/
int evolve() {
	int i, j, go=1,flag=1, hit=0;
	for (;go==1;) {
		go=0;
		for (i=0;i<16;i++) {
			if(ball[i].flag==0)   continue;
			ball_x_old[i]=ball[i].x;
			ball_y_old[i]=ball[i].y;
			for (j=0; j<16;j++)
						 if(j!=i&&ball[j].flag==1)
							if(pow(ball[i].x-ball[j].x, 2.)+pow(ball[i].y-ball[j].y,2.)<4*(R+1)*(R+1))
								collision(i,j);
			ball[i].x+=ball[i].vx;
			ball[i].y+=ball[i].vy;
			if(ball[i].x<=60) {
				ball[i].x=60;
				ball[i].vx=-ball[i].vx;
			}
			if(ball[i].x>=548) {
				ball[i].x=548;
				ball[i].vx=-ball[i].vx;
			}
			if(ball[i].y<=110) {
				ball[i].y=110;
				ball[i].vy=-ball[i].vy;
			}
			if(ball[i].y>=344) {
				ball[i].y=344;
				ball[i].vy=-ball[i].vy;
			}
			for (j=0;j<6;j++)
				if(pow(ball[i].x-circlexy[j][0],2.)+pow(ball[i].y-circlexy[j][1],2.)<=30) {
				ball[i].flag=0;
				drawball(i,0);
				drawhole();
				ball[i].x=60+30*i;
				ball[i].y=380;
				drawball(i,1);
				if(person==1) {
					if((i>7)||(i==0))        flag=0;
				} else if(person==2) {
					if((i<8)||(i==15))       flag=0;
				} else if(person==3) {
					flag=2;
				}
				hit++;
				break;
			}
			/*it is very easy for balls get into the holes,why? */
			if(ball[i].flag==1)   if((fabs(ball_x_old[i]-ball[i].x)>0)||(fabs(ball_y_old[i]-ball[i].y)>0)) {
				drawball(i, 0);
				drawhole();
			}
			ball[i].vx*=MCXS;
			ball[i].vy*=MCXS;
			if(fabs(ball[i].vx)<zero_speed&&fabs(ball[i].vy)<zero_speed) {
				ball[i].vx=0;
				ball[i].vy=0;
			}
			if(ball[i].flag==1)
						if((fabs(ball_x_old[i]-ball[i].x)>0)||(fabs(ball_y_old[i]-ball[i].y)>0))
						  drawball(i,1);
		}
		for (i=0;i<16; i++)
				 if(ball[i].flag==1) if ((fabs(ball[i].vx)>=zero_speed)||(fabs(ball[i].vy)>=zero_speed)) {
			go=1;
			break;
		}
	}
	if(ball[0].flag==0)   baiqiuhuifang();
	if((hit==0)&&(person!=3))  flag=0; else if(person==3)         flag=2;
	return flag;
}
/*all the balls get new velocity and coordinates*/
/**************************************************************/
void main() {
	char *result;
	int  flag,i, match=1;
	enviro();
	drawtable();
	putball();
	kaiqiu();
	while(1) {
		play();
		flag=evolve();
		if(match==0)  flag=1;
		setcolor(CYAN);
		settextstyle(0,HORIZ_DIR,3);
		outtextxy(player[person-1].x, player[person-1].y, "\002");
		if(flag!=2) {
			player[person-1].hit=0;
			for (i=(person-1)*7+1;i<=person*7;i++)
								if(ball[i].flag==0)  player[person-1].hit++;
		} else {
			player[person-1].hit=0;
			for (i=1;i<=14;i++) if(ball[i].flag==0) player[person-1].hit++;
		}
		if(player[(person==2?1:2)-1].win==-1) {
			if(player[person-1].hit==7)    player[person-1].win=1;
		} else  if(ball[15].flag==0) {
			if( player[person-1].hit<7*fabs(person-1) )
										  player[person-1].win=-1; else   player[person-1].win=1;
		}
		/* printf("%s->hit: %d  win: %d", player[person-1].name, player[person-1].hit,
	  player[person-1].win); */
		if(player[person-1].win!=0) {
			settextstyle(1,HORIZ_DIR,1);
			setcolor(BROWN);
			if(player[person-1].win==-1) {
				sprintf(result, "%s has lost.",player[person-1].name);
				outtextxy(330,70,result);
				if(person==3) {
					bioskey(0);
					goto end;
				} else {
					match=0;
					flag=0;
				}
			} else if(player[person-1].win==1) {
				sprintf(result,"%s has won!!", player[person-1].name);
				outtextxy(330,70,result);
				bioskey(0);
				goto end;
			}
		}
		if(flag==0)       person=(person==2?1:2); else if(flag==2)  person=3;
		setcolor(player[person-1].color);
		settextstyle(0,HORIZ_DIR,3);
		outtextxy(player[person-1].x,player[person-1].y,"\002");
	}
	end: clearviewport();
}
