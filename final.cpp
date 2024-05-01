#include<graphics.h>
#include<iostream>
#include<stdlib.h>
#include<conio.h>
#include<stdio.h>
#include<time.h>
#pragma GCC diagnostic ignored "-Wwrite-strings"
using namespace std;
int ppos[53][2],wincount=0,seed=0;
int win[4]={0,0,0,0};
int safepos[8]={1,9,14,22,27,35,40,48};
int ipos[4][8]={65,125,335,65,395,335,125,395,65,65,395,65,335,395,65,395,
                125,65,335,125,335,335,125,335,125,125,395,125,395,395,65,335,};
int grid[58][8]={
                65,125,335,65,395,335,125,395,50,200,260,50,410,260,200,410,
				80,200,260,80,380,260,200,380,110,200,260,110,350,260,200,350,
				140,200,260,140,320,260,200,320,170,200,260,170,290,260,200,290,
				200,170,290,200,260,290,170,260,200,140,320,20,260,320,140,260,
				200,110,350,200,260,350,110,260,200,80,380,200,260,380,80,260,
				200,50,410,200,260,410,50,260,200,20,440,200,260,440,20,260,
				230,20,440,20,230,440,20,230,260,20,440,260,200,440,20,200,
				260,50,410,260,200,410,50,200,260,80,380,260,200,320,140,200,
				260,110,350,260,200,350,110,200,260,140,320,260,200,320,140,200,
				260,170,290,260,200,290,170,200,290,200,260,290,170,260,200,170,
				320,200,260,320,140,260,200,140,350,200,260,350,110,260,200,110,
				380,200,260,380,80,260,200,80,410,200,260,410,50,260,200,50,
				440,200,260,440,20,260,200,20,440,230,320,440,20,230,230,20,
				440,260,200,440,20,200,260,20,410,260,200,410,50,200,260,50,
				380,260,200,380,80,200,260,80,350,260,200,410,50,200,260,50,
				320,260,200,320,140,200,260,140,290,260,200,290,170,200,260,170,
				260,290,170,260,200,170,290,200,260,320,140,260,200,140,320,200,
				260,350,110,260,200,110,350,200,260,380,80,260,200,80,380,200,
			    260,410,50,260,200,50,410,200,260,440,20,260,200,20,440,200,
				230,440,20,230,230,20,440,230,200,440,20,200,260,20,440,260,
				200,410,50,200,260,50,410,260,200,380,80,200,260,80,380,260,
				200,350,110,200,260,110,350,260,200,320,140,200,260,140,320,260,
				200,290,170,200,260,170,290,260,170,260,200,170,290,200,260,290,
				140,260,200,140,320,200,260,320,110,260,200,110,350,200,260,350,
				80,260,200,80,380,200,260,380,50,260,200,50,410,200,260,410,
				20,260,200,20,440,200,260,440,20,230,230,20,440,230,230,440,
				50,230,230,50,410,230,230,410,80,230,230,80,380,230,230,380,
				110,230,230,110,350,230,230,350,140,230,230,140,320,230,230,320,
				170,230,230,170,290,230,230,290,210,230,230,200,260,230,230,260
				};  
int st1a[]={200,67,189,87,211,87},st1b[]={189,73,200,93,211,73};
int st2a[]={380,187,369,207,391,207},st2b[]={369,193,380,213,391,193};
int st3a[]={260,367,249,387,271,387},st3b[]={249,373,260,393,271,373};
int st4a[]={80,247,69,267,91,267},st4b[]={69,253,80,273,91,253};
class player{
	int colour[4],key,code,dice[4],dnum,tnum,com_mod,random;
	int calpos(int,int);
	int decide(int);
	int dscore(int);
	int movecheck(int,int);
	void roll();
	void dice_create(int);
	void killcheck(int);
	int stchk(int);
	void pawn(int);
	void typewinner();
public:
	char name[20],cho[5],tname[20];
	int gpos[4],result;
	void turn();
	void move(int,int);
	void pinit(int a,int b,int c,int d,int y,char pname[],int ai)
	{
		gpos[0]=gpos[1]=gpos[2]=gpos[3]=dnum=tnum=0;
		colour[0]=a;colour[1]=b;colour[2]=c;colour[3]=d;
		key=y;result=0;com_mod=ai;code=key/2;strcpy(name,pname);
		strcat(tname,name);strcat(tname,"s Turn");
	}
};
player green,yellow,blue,red;
int player::stchk(int d)
{
	for(int k=0;k<8;k++)
	{
		int dis=d-safepos[k];
	  if(dis==0)
	     return(1);
	else if(dis<0)	
	     return(0); 	
	}
	return(0);
}
int player ::dscore(int d)
{
	if(d>=1 && d<=6)
	 return(2);
else	if(d>=7 && d<=12)
	 return(1);
	else
	 return(0);
}
int player::calpos(int position,int pcode)
{
	switch(pcode)
	{
		case 0:return(position-1);
		case 1:return((position+12)%52);
		case 2:return((position+25)%52);
		case 3:return((position+38)%52);
	}
 return(0);	
} 
void gotoxy(short x ,short y)
{
	COORD pos={x,y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
}		       
void  intro(){
	char name[20],ch;
	HANDLE h=GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h,16);
	gotoxy(21,3);cout<<"__________________";
	gotoxy(22,4);cout<<"Welcome to LUDU";
	gotoxy(21,5);cout<<"******************";
	SetConsoleTextAttribute(h,10);
	gotoxy(10,7);cout<<"GREEN PLAYER";
	gotoxy(15,8);cout<<"Enter Name:";cin>>name;
	gotoxy(15,9);cout<<"Computer Y Player N:";cin>>ch;
	if(toupper(ch)=='Y')
	       green.pinit(2,14,9,4,0,name,1);
	   else
	       green.pinit(2,14,9,4,0,name,0); 
	SetConsoleTextAttribute(h,6);
	gotoxy(10,11);cout<<"YELLOW PLAYER";
	gotoxy(15,12);cout<<"Enter Name :";cin>>name;
	gotoxy(15,13);cout<<"Computer Y Player N:";cin>>ch;
	if(toupper(ch)=='Y')
	       yellow.pinit(14,9,4,2,2,name,1);
	   else
	       yellow.pinit(14,9,4,2,2,name,0);
	SetConsoleTextAttribute(h,9);       
    gotoxy(10,15);cout<<"BLUE PLAYER";
	gotoxy(15,16);cout<<"Enter Name :";cin>>name;
	gotoxy(15,17);cout<<"Computer Y Player N:";cin>>ch;
	if(toupper(ch)=='Y')
	       blue.pinit(9,4,2,14,4,name,1);
	   else
	       blue.pinit(9,4,2,14,4,name,0);
	SetConsoleTextAttribute(h,12);       
    gotoxy(10,19);cout<<"RED PLAYER";
	gotoxy(15,20);cout<<"Enter Name :";cin>>name;
	gotoxy(15,21);cout<<"Computer Y Player N:";cin>>ch;
	if(toupper(ch)=='Y')
	       red.pinit(4,2,14,9,6,name,1);
	   else
	       red.pinit(4,2,14,9,6,name,0);	              
}
void quit()
{   
    HANDLE h=GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h,3);
	cleardevice();
	system("cls");
	gotoxy(20,11);cout<<"******************\n";
	gotoxy(20,12);cout<<"      Thanks";
	gotoxy(20,13);cout<<"******************\n";
	delay(2000);
	SetConsoleTextAttribute(h,4);
	gotoxy(20,14);cout<<"Created by a group\n";
	SetConsoleTextAttribute(h,13);
	gotoxy(8,16);cout<<"ANAS";
	SetConsoleTextAttribute(h,15);
	gotoxy(48,16);cout<<"KHADIJA";
	SetConsoleTextAttribute(h,9);
	gotoxy(48,18);cout<<"RANJANDAR";
	SetConsoleTextAttribute(h,2);
	gotoxy(8,18);cout<<"AHSAN"<<endl;
	delay(2000);
	exit(0);
}
void drawstar()
{
	setcolor(2);setfillstyle(1,2);fillpoly(3,st1a);fillpoly(3,st1b);
	setcolor(14);setfillstyle(1,14);fillpoly(3,st2a);fillpoly(3,st2b);
	setcolor(9);setfillstyle(1,9);fillpoly(3,st3a);fillpoly(3,st3b);
	setcolor(4);setfillstyle(1,4);fillpoly(3,st4a);fillpoly(3,st4b);
}
void board()
{
	char str[100]={" LUDO "};
	setcolor(2);settextstyle(1,0,2);
	outtextxy(115,455,str);
	strcpy(str,"");
	setcolor(14);settextstyle(2,0,5);
	outtextxy(420,465,str);
	int ar1[]={185,185,230,230,185,275};
	int ar2[]={185,185,230,230,275,185};
	int ar3[]={275,185,230,230,275,275};
	setcolor(15);
	setfillstyle(1,2);bar3d(35,185,65,245,0,0);bar3d(65,215,185,245,0,0);
	setfillstyle(1,14);bar3d(215,35,275,65,0,0);bar3d(215,65,245,185,0,0);
	setfillstyle(1,4);bar3d(215,275,245,395,0,0);bar3d(185,395,245,425,0,0);
	setfillstyle(1,9);bar3d(275,215,395,245,0,0);bar3d(395,215,425,275,0,0);
	for(int i=5;i<=455;i+=30)
	{
		line(5,i,455,i);line(i,5,i,455);
	}
	setfillstyle(1,2);bar3d(5,5,185,185,0,0);
	setfillstyle(1,15);bar3d(35,35,155,155,0,0);
	setcolor(2);
	setlinestyle(1,1,3);
	circle(65,65,14);circle(65,125,14);
	circle(125,65,14);circle(125,125,14);
	setlinestyle(0,0,1);setcolor(15);
	setfillstyle(1,14);bar3d(275,5,455,185,0,0);
	setfillstyle(1,15);bar3d(305,35,425,155,0,0);
	setcolor(14);
	setlinestyle(1,1,3);
	circle(335,65,14);circle(395,65,14);
	circle(335,125,14);circle(395,125,14);
	setlinestyle(0,0,1);setcolor(15);
	setfillstyle(1,4);bar3d(5,275,185,455,0,0);
	setfillstyle(1,15);bar3d(35,305,155,425,0,0);
	setcolor(4);
	setlinestyle(1,1,3);
	circle(65,335,14);circle(65,395,14);
	circle(125,335,14);circle(125,395,14);
	setlinestyle(0,0,1);setcolor(15);
	setfillstyle(1,9);bar3d(275,275,455,455,0,0);
	setfillstyle(1,15);bar3d(305,305,425,425,0,0);

	setcolor(9);
	setlinestyle(1,1,3);
	circle(335,335,14);circle(335,395,14);
	circle(395,335,14);circle(395,395,14);
	setlinestyle(0,0,1);setcolor(15);
	setfillstyle(1,4);bar3d(185,185,275,275,0,0);
	setfillstyle(1,2);fillpoly(3,ar1);
	setfillstyle(1,14);fillpoly(3,ar2);
	setfillstyle(1,9);fillpoly(3,ar3);
	drawstar();
    setcolor(6);setfillstyle(1,0);
    bar3d(460,5,635,275,0,0);
    bar3d(460,280,635,375,0,0);
    bar3d(460,380,635,455,0,0);
    bar3d(520,92,540,112,0,0);
    bar3d(540,92,560,112,0,0);
    bar3d(560,92,580,112,0,0);
    settextstyle(4,0,2);
    outtextxy(467,285,"Winner:");
    outtextxy(465,305,"2nd  :");
    outtextxy(465,345,"Loser:");
    settextstyle(4,0,1);
    outtextxy(465,380,"exist press q");
    getch();
}
void player::typewinner()
{
	result=1;wincount++;win[code]=1;
	setcolor(0);settextstyle(2,0,5);
	switch(wincount)
	{
		case 1:outtextxy(520,285,"name");break;
		case 2:outtextxy(520,305,"name");break;
		case 3:
			{
				outtextxy(520,325,"name");
				for(int i=0;i<4;i++)
				    if(win[i]==0)
				           switch(i)
				           {
				           	   case 0: green.typewinner();
				           	   case 1: yellow.typewinner();
				           	   case 2: blue.typewinner();
				           	   case 3: red.typewinner();
						   }
					break;	   
			}
		case 4:
			{
				outtextxy(520,345,"name");
				getch();quit();
			}
			
	}
}
void player::dice_create(int n)
	{
		setcolor(0);setfillstyle(1,15);
		bar3d(530,50,570,90,0,0);
		switch(n)
		{
			case 1:
			{
				setfillstyle(1,0);
				fillellipse(550,70,4,4);
				break;
			}
			case 2:
				{
					setfillstyle(1,0);
					fillellipse(540,60,4,4);
					fillellipse(560,80,4,4);
					break;
				}
			case 3:
				{
					setfillstyle(1,0);
					fillellipse(540,60,4,4);
					fillellipse(560,80,4,4);
					fillellipse(550,70,4,4);
					break;
				}
			case 4:
				{
					setfillstyle(1,0);
					fillellipse(540,60,4,4);
					fillellipse(540,80,4,4);
					fillellipse(560,60,4,4);
					fillellipse(560,80,4,4);
					break;
				}
			case 5:
				{
					setfillstyle(1,0);
					fillellipse(540,60,4,4);
					fillellipse(540,80,4,4);
					fillellipse(560,60,4,4);
					fillellipse(560,80,4,4);
					fillellipse(550,70,4,4);
					break;
				}
			case 6:
				{
					setfillstyle(1,0);
					fillellipse(540,60,4,4);
					fillellipse(540,70,4,4);
					fillellipse(540,80,4,4);
					fillellipse(560,60,4,4);
					fillellipse(560,70,4,4);
					fillellipse(560,80,4,4);
					break;
				}								
			}
		}
void player::killcheck(int num)
{
	int z=gpos[num],x=calpos(z,code),hitc,hitn;
	if(z<=51 && stchk(z)==0)
	{
		hitc=ppos[x][0];hitn=ppos[x][1];
		ppos[x][0]=code;ppos[x][1]=num;
		if(hitc!=-1)
		{
			switch(hitc)
			{
				case 0:green.move(hitn,-1);break;
				case 1:yellow.move(hitn,-1);break;
				case 2:blue.move(hitn,-1);break;
				case 3:red.move(hitn,-1);break;
			}
			pawn(num);
		}
	}
	
}
int player::movecheck(int d,int num=-1)
{
if(num==-1){
for(int i=0;i<4;i++){
if(gpos[i]==0 && d==6)
return(1);
if(gpos[i]!=0 && (gpos[i]+d)<=57){
int flag1=1;
				for(int l=0;l<4;l++)
				    if(gpos[i]+d==gpos[l] && stchk(gpos[l])!=1)
				           if(gpos[l]!=57)
				                 flag1=0;
			if(flag1)
			return(1);	                 
			}       
		}
	}
	else
	{
		if(gpos[num]==0 && d==6)
		   return(1);
	if(gpos[num]!=0 && (gpos[num]+d)<=57)
	{
		for(int l=0;l<4;l++)
		    if(gpos[num]+d==gpos[l] && stchk(gpos[l]!=1))
		            if(gpos[l]!=57)
					   return(0);
			return(1);		     
		}	   
	}
	return(0);
}
void player::roll()
{
	
	char ch,str[10];
	setcolor(WHITE);setfillstyle(1,6);bar3d(461,113,634,274,0,0);
	setcolor(6);setfillstyle(1,0);
	srand(time(NULL));
	if(dnum==0)
	      for(int i=0;i<3;i++)
	      bar3d(520+20*i,92,540+20*i,112,0,0);
	  settextstyle(2,0,5);outtextxy(480,30,"Hit any key to roll");
	  setcolor(0);    
	if(!com_mod)
	{
		do
		{
		    dice[dnum]=rand()%6+1;
			dice_create(dice[dnum]);delay(25);
		}while(!kbhit());
		ch=getch();		
		if(toupper(ch)=='Q')
		  quit();
	}
	else
	{
	   int stopper=(seed*2)%20+20;
	   for(int i=0;i<stopper;i++)
	   {
	   	  dice[dnum]=rand()%6+1;
	   	  dice_create(dice[dnum]);delay(25);
		}	
	}
	setcolor(6);gcvt(dice[dnum],1,str);
	settextstyle(4,0,1);outtextxy(526+dnum*20,89,str);
	dnum++;seed++;
}
int player::decide(int dic)
{
int score[4]={0,0,0,0},a,b,x,y,dist,max,token;
max=INT_MIN;token=-1;
for(int i=0;i<4;i++){
a=gpos[i];b=a+dic;
x=calpos(a,code);y=calpos(b,code);
if(movecheck(dic,i)==0)   //position on board
score[i]-=100;
if(a==0 && dic==6)
score[i]+=7;
if(a>45 && a<52)
score[i]+=5; 
else if(a>40 && a<52)
score[i]+=3;
else if(a>27)
score[i]+=1;
if(b==57)
score[i]+=2;
if(ppos[y][0]!=-1 && ppos[y][0]!=code && a<51)  //attack
score[i]+=10;
if((a<51 && b>51)|| stchk(b)==1)  //future position
score[i]+=3;
if(movecheck(dic,i)==1 && b<52){
for(int j=1;j<13;j++ )  //look enemy behaind
{
if((y-j)>=0)
if(ppos[y-j][0]!=-1 && ppos[y-j][0]!=code)
score[i]-=dscore(j);
else{
int ind=(52+y-j);
if(ppos[ind][0]!=-1 && ppos[ind][0]!=code)
score[i]-=dscore(j);    }            
}
for(int j=1;j<13;j++)   //look enemy infront
{
if((y+j)<=51)
if(ppos[y+j][0]!=-1 && ppos[y+j][0]!=code)
score[i]+=dscore(j);
else{
int ind=(y+j-52);
if(ppos[ind][0]!=-1 && ppos[ind][0]!=code)
score[i]+=dscore(j);
								}
			                }
			
						}
						if(a>51 || stchk(a)==1)  //curent position
						     score[i]-=4;
						if(movecheck(dic,i)==1 && a<52)
						{
							for(int j=1; j<13;j++)  //look enemy behind
							{
								if((x-j)>=0)
								           if(ppos[x-j][0]!=-1 && ppos[x-j][0]!=code)
								           score[i]+=dscore(j);
								        else
										{
											int ind=(52+x-j);
											                if(ppos[ind][0]!=-1 && ppos[ind][0]!=code)
											                score[i]+=dscore(j);
										   }   
						            	}
									}
									if(score[i]>max)
									{
										token=i;max=score[i];
									}	 		    		   	       
	                              }
gotoxy(68,9);cout<<token+1;
return(token);
}
void player::turn()
{
	int n=0,x,y,hitc,flag=0;dnum=0;
	setcolor(15);setfillstyle(1,0);bar3d(461,6,634,35,0,0);
	setcolor(colour[0]);settextstyle(3,0,2);outtextxy(475,5,"Player");
	for(int j=0;j<4;j++)
	    pawn(j);
	do
	{
		roll();
		      if(dnum==3 && dice[2]==6)
		      {
		      	settextstyle(2,0,5);setcolor(6);
		      	outtextxy(463,115,"sorry");
		      	outtextxy(465,128,"3 sixes cencel");
		      	dnum=0;delay(1000);
			  }
			  
		}while(dice[dnum-1]==6 || dnum==0);
		for(int j=0;j<dnum;j++)
		{
			flag=0;setcolor(0);setfillstyle(1,0);
			bar3d(461,113,634,274,0,0);
			setcolor(15);rectangle(521+20*j,93,539+20*j,111);
			settextstyle(2,0,5);setcolor(6);
			if(movecheck(dice[j])==1)                           //computer mode
			{
				do{
					settextstyle(1,0,1);setcolor(6);
					outtextxy(463,112,"select pice");
					outtextxy(465,125,"to move :");
					if(com_mod)
					n=decide(dice[j]);
					else
					{
						gotoxy(68,9);
						cout<<"\b";
						cho[0]=getche();n=atoi(cho);	
						cout<<"\b"<<cho[0];n--;
					}
					if(n>=0 && n<4 && gpos[n]==0 && dice[j]==6)
					{
						outtextxy(465,180,"pice move");
						move(n,1);flag=1;
					}
					else if(n>=0 && n<4 && movecheck(dice[j],n)==1)
					{
						y=gpos[n];x=calpos(y,code);
						ppos[x][0]=ppos[x][1]=-1;
						move(n,dice[j]);flag=1;
						settextstyle(1,0,1);setcolor(6);
						outtextxy(465,180,"pice moved");
						killcheck(n);delay(500);
					}
					else
					{
					settextstyle(1,0,1);setcolor(6);
					outtextxy(465,150,"sorry,you cannot");
					outtextxy(465,165,"move that pice");
					outtextxy(465,200,"try onother pice");
					delay(1000);setcolor(0);setfillstyle(1,0);
					bar3d(461,113,634,274,0,0);	
					}
				}while(flag!=1);
			}
			else 
			{
				settextstyle(1,0,1);setcolor(6);
				outtextxy(465,120,"No pice to move ");
				outtextxy(465,140,"You have to skip");
				outtextxy(465,155,"this throw");
				delay(1000);setcolor(0);setfillstyle(1,0);
				bar3d(461,113,634,274,0,0);
			}
			setcolor(15);
	    	line(521+20*j,93,539+20*j,111);
			line(539+20*j,93,521+20*j,111);
		  }
		  int sum=gpos[0]+gpos[1]+gpos[2]+gpos[3];
		  if(sum==228)
		  typewinner();
		  if(sum!=228 && tnum>0)
		  {
		  	setcolor(0);setfillstyle(1,0);
		  	bar3d(461,113,634,274,0,0);settextstyle(2,0,5);
		  	setcolor(6);outtextxy(465,120,"You get extra turn");
		  	tnum--;delay(1000);turn();
			}  
		}
void player::pawn(int k){
if(gpos[k]!=0 && gpos[k]!=57){
setcolor(0);setfillstyle(1,colour[0]);
fillellipse(grid[gpos[k]][key],grid[gpos[k]][key+1],10,10);
	}
}
void player::move(int k,int n){
if(n==-1){
setcolor(0);setfillstyle(1,0);
fillellipse(grid[gpos[k]][key],grid[gpos[k]][key+1],10,10);
setfillstyle(1,colour[0]);
fillellipse(ipos[k][key],ipos[k][key+1],10,10);
return;
}
for(int i=gpos[k];i<=gpos[k]+n;i++){
setcolor(0);
if(i!=0){
setcolor(0);setfillstyle(1,colour[0]);
fillellipse(grid[i][key],grid[i][key+1],10,10);
}
if(i==0){
setfillstyle(1,colour[0]);
fillellipse(ipos[k][key],ipos[k][key+1],10,10);
}
if(i==1){
setcolor(15);setfillstyle(1,15);
fillellipse(ipos[k][key],ipos[k][key+1],10,10);
}
if(i==2){
setcolor(colour[0]);setfillstyle(1,colour[0]);
fillellipse(grid[1][key],grid[1][key+1],10,10);
}
if(i==15){
setcolor(colour[1]);setfillstyle(1,colour[1]);
fillellipse(grid[14][key],grid[14][key+1],10,10);
}
else if(i==28)
		{
setcolor(colour[2]);setfillstyle(1,colour[2]);
fillellipse(grid[27][key],grid[27][key+1],10,10);
}
else if(i==41){
setcolor(colour[3]);setfillstyle(1,colour[3]);
fillellipse(grid[40][key],grid[40][key+1],10,10);
}
else if(i>52){
setcolor(colour[0]);setfillstyle(1,colour[0]);
fillellipse(grid[i-1][key],grid[i-1][key+1],10,10);
}
else{
setfillstyle(1,0);
fillellipse(grid[i-1][key],grid[i-1][key+1],10,10);	
}
}
gpos[k]+=n;drawstar();setcolor(0);
if(gpos[k]==57)
for(int j=0;j<4;j++){
		green.pawn(j);
		red.pawn(j);
		yellow.pawn(j);
		blue.pawn(j);
	}									  
	}		                                  
void game(){
	for(int i=0;i<52;i++){
		
    for(int j=0;j<2;j++)
	ppos[i][j]=-1;
	for(int i=0;i<4;i++)
	{
		
		green.move(i,green.gpos[i]);
		red.move(i,red.gpos[i]);
		yellow.move(i,yellow.gpos[i]);
blue.move(i,blue.gpos[i]);
}} 		
while((green.result+red.result+yellow.result+blue.result)!=3){		
if(green.result!=1){
green.turn();
}		    
if(yellow.result!=1){
yellow.turn(); 
}		   
if(blue.result!=1){
blue.turn();
}		    
if(red.result!=1){
red.turn();	
}				   
}
}
int main(){
int gdriver= DETECT,gmode;
initgraph(&gdriver,&gmode,"");
intro();                 //116
board();
game();
}

