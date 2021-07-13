#include<stdio.h>
#include<conio.h>
#define LT 218
#define RT 191
#define CROSS 197
#define HL 196
#define VL 179
#define TT 194
#define BT 193
#define LST 195
#define RST 180
#define LB 192
#define RB 217
#define BS 8
#define SPACE 32
#define DIM 10
#define WIDTH 3
#define HEIGHT 1
#include<bios.h>
#define LEFT 19200
#define RIGHT 19712
#define UP 18432
#define DOWN 20480
#define ENTER 7181
#define FLAG  8550
#define ESC 283
#include<stdlib.h>
void drawBox();
void setMines(int mines[DIM][DIM],int tot_mines);
void mines_display(int mines[DIM][DIM]);
void fill_mines_count(int mines[DIM][DIM]);
void zero_filler(int mines[DIM][DIM],int row,int col,int open_close_flag[DIM][DIM]);

int main()
{
  int key,brow,bcol,scr_row,scr_col,min_row,min_col,mines_count=8,row,col;
  int flag_ctr=0,valid_flag=0;
  int mines[DIM][DIM]={0};
  int flag[DIM][DIM]={0};
  int open_close_flag[DIM][DIM]={0};

  clrscr();

  setMines(mines,mines_count);
 // mines_display(mines);
  fill_mines_count(mines);
//  mines_display(mines);
  drawBox();
  bcol = (80 -((DIM*WIDTH)+DIM+1))/2;
  brow = (25-((DIM*HEIGHT)+DIM+1))/2;
  scr_col =bcol+2;
  scr_row=brow+1;
  min_row=0;
  min_col=0;
  gotoxy(scr_col,scr_row);
  do
  {
   while(bioskey(1)==0);
   key = bioskey(0);
   switch(key)
   {
    case LEFT :
		if(min_col-1>=0)
		{
			min_col = min_col-1;
			scr_col = scr_col- (WIDTH+1);
			gotoxy(scr_col,scr_row);
		}
		break;
    case RIGHT :
		if(min_col+1<DIM)
		{
			min_col = min_col+1;
			scr_col = scr_col+ (WIDTH+1);
			gotoxy(scr_col,scr_row);
		}
		break;
    case UP :
		if(min_row-1>=0)
		{
			min_row = min_row-1;
			scr_row = scr_row- (HEIGHT+1);
			gotoxy(scr_col,scr_row);
		}

		break;
    case DOWN :
		if(min_row+1<DIM)
		{
			min_row = min_row+1;
			scr_row = scr_row+ (HEIGHT+1);
			gotoxy(scr_col,scr_row);
		}
		break;
    case ENTER : if(mines[min_row][min_col]==9)
		 {
		  printf("Game Over");
		  key=ESC;
		 }
		 else if(mines[min_row][min_col]==0&&open_close_flag[min_row][min_col]==0)
		 {
		   zero_filler(mines,min_row,min_col,open_close_flag);
		   gotoxy(scr_col,scr_row);
		 }
		 else if(open_close_flag[min_row][min_col]==0)//numbers from 1 to 8
		 {
		  open_close_flag[min_row][min_col]=1;
		  printf("%d",mines[min_row][min_col]);
		  gotoxy(scr_col,scr_row);
		 }
			break;
    case FLAG :
		 if(flag[min_row][min_col]==0 && flag_ctr<mines_count)
		 {
		   flag_ctr++;
		   flag[min_row][min_col]=1;
		   printf("F");
		   gotoxy(scr_col,scr_row);
		   if(mines[min_row][min_col]==9)
		      valid_flag++;
		   if(valid_flag==mines_count)
		    {
		     printf("MINES DEFUSED ... WON !!!!");
		     key=ESC;
		    }
		 }
		 else if(flag[min_row][min_col]==1)

		 {
		   flag_ctr--;
		   flag[min_row][min_col]=0;
		   printf(" ");
		   gotoxy(scr_col,scr_row);
		   if(mines[min_row][min_col]==9)
		      valid_flag--;
		 }
		 break;
   }

  }while(key!=ESC);


  getch();
  return 0;

}
void  zero_filler(int mines[DIM][DIM],int row,int col,int open_close_flag[DIM][DIM])
{
  int bcol,brow,scr_row,scr_col;
  bcol = (80 -((DIM*WIDTH)+DIM+1))/2;
  brow = (25-((DIM*HEIGHT)+DIM+1))/2;
  scr_col =bcol+2;  //setting up base col for screen printing
  scr_row= brow+1;  //setting up base row for screen printing
 if(open_close_flag[row][col]==0)//check for closed
 {
      open_close_flag[row][col]=1;
      gotoxy(scr_col + (col*(WIDTH+1)) , scr_row + ((row)*(HEIGHT+1)));
      printf("%d",mines[row][col]);
    if(row-1 >=0&&mines[row-1][col]!=0 && open_close_flag[row-1][col]==0)//top
    {
      open_close_flag[row-1][col]=1;
      gotoxy(scr_col + (col*(WIDTH+1)) , scr_row + ((row-1)*(HEIGHT+1)));
      printf("%d",mines[row-1][col]);
    }
    else if(row-1 >=0&&mines[row-1][col]==0 &&open_close_flag[row-1][col]==0)
    {
     zero_filler(mines,row-1,col,open_close_flag);
    }
    if(row-1>=0 &&col+1<DIM&&mines[row-1][col+1]!=0&&open_close_flag[row-1][col+1]==0)//right top
    {
      open_close_flag[row-1][col+1]=1;
      gotoxy(scr_col + ((col+1)*(WIDTH+1)) , scr_row + ((row-1)*(HEIGHT+1)));
      printf("%d",mines[row-1][col+1]);
    }
    else if(row-1>=0&&col+1<DIM&&mines[row-1][col+1]==0 &&open_close_flag[row-1][col+1]==0)
    {
     zero_filler(mines,row-1,col+1,open_close_flag);
    }
    if(col+1<DIM && mines[row][col+1]!=0 &&open_close_flag[row][col+1]==0)//right
    {
      open_close_flag[row][col+1]=1;
      gotoxy(scr_col + ((col+1)*(WIDTH+1)) , scr_row + ((row)*(HEIGHT+1)));
      printf("%d",mines[row][col+1]);
    }
   else if(col+1<DIM&&mines[row][col+1]==0 &&open_close_flag[row][col+1]==0)
    {
     zero_filler(mines,row,col+1,open_close_flag);
    }


   if(col+1<DIM && row+1 <DIM&& mines[row+1][col+1]!=0&&open_close_flag[row+1][col+1]==0)//right bottom
    {
      open_close_flag[row+1][col+1]=1;
      gotoxy(scr_col + ((col+1)*(WIDTH+1)) , scr_row + ((row+1)*(HEIGHT+1)));
      printf("%d",mines[row+1][col+1]);
    }
   else if(row+1<DIM&&col+1<DIM&&mines[row+1][col+1]==0 &&open_close_flag[row+1][col+1]==0)
    {
     zero_filler(mines,row+1,col+1,open_close_flag);
    }



   if(row+1<DIM && mines[row+1][col]!=0&&open_close_flag[row+1][col]==0)//bottom
   {
      open_close_flag[row+1][col]=1;
      gotoxy(scr_col + ((col)*(WIDTH+1)) , scr_row + ((row+1)*(HEIGHT+1)));
      printf("%d",mines[row+1][col]);
   }
      else if(row+1<DIM&&mines[row+1][col]==0 &&open_close_flag[row+1][col]==0)
    {
     zero_filler(mines,row+1,col,open_close_flag);
    }


   if(col-1>=0 &&row+1<DIM&&mines[row+1][col-1]!=0&&open_close_flag[row+1][col-1]==0)//left bottom
   {
      open_close_flag[row+1][col-1]=1;
      gotoxy(scr_col + ((col-1)*(WIDTH+1)) , scr_row + ((row+1)*(HEIGHT+1)));
      printf("%d",mines[row+1][col-1]);
   }
   else if(col-1>=0&&row+1<DIM&&mines[row+1][col-1]==0 &&open_close_flag[row+1][col-1]==0)
    {
     zero_filler(mines,row+1,col-1,open_close_flag);
    }
   if(col-1>=0&&mines[row][col-1]!=0&&open_close_flag[row][col-1]==0)//left
   {
      open_close_flag[row][col-1]= 1;
      gotoxy(scr_col + ((col-1)*(WIDTH+1)) , scr_row + ((row)*(HEIGHT+1)));
      printf("%d",mines[row][col-1]);
   }
   else if(col-1>=0&&mines[row][col-1]==0 &&open_close_flag[row][col-1]==0)
    {
     zero_filler(mines,row,col-1,open_close_flag);
    }

   if(col-1>=0 && row-1>=0 && mines[row-1][col-1]!=0&&open_close_flag[row-1][col-1]==0)//left top
   {
      open_close_flag[row-1][col-1]= 1;
      gotoxy(scr_col + ((col-1)*(WIDTH+1)) , scr_row + ((row-1)*(HEIGHT+1)));
      printf("%d",mines[row-1][col-1]);
   }
   else if(row-1>=0&&col-1>=0&&mines[row-1][col-1]==0 &&open_close_flag[row-1][col-1]==0)
    {
     zero_filler(mines,row-1,col-1,open_close_flag);
    }

 }

}
void fill_mines_count(int mines[DIM][DIM])
{
 int row ,col,mine_ctr;

 for(row=0;row<DIM;row++)
 {
  for(col=0;col<DIM;col++)
  {
   if(mines[row][col]==9)
      continue;
   mine_ctr=0;
   if(row-1 >=0 &&mines[row-1][col]==9)//top
    mine_ctr++;
   if(row-1>=0 &&col+1<DIM&&mines[row-1][col+1]==9)//right top
    mine_ctr++;
   if(col+1<DIM && mines[row][col+1]==9)//right
    mine_ctr++;
   if(col+1<DIM && row+1 <DIM&& mines[row+1][col+1]==9)//right bottom
    mine_ctr++;
   if(row+1<DIM && mines[row+1][col]==9)//bottom
    mine_ctr++;
   if(col-1>=0 &&row+1<DIM&&mines[row+1][col-1]==9)//left bottom
    mine_ctr++;
   if(col-1>=0&&mines[row][col-1]==9)//left
    mine_ctr++;
   if(col-1>=0 && row-1>=0 && mines[row-1][col-1]==9)//left top
    mine_ctr++;
   mines[row][col]=mine_ctr;
  }
 }
}

void mines_display(int mines[DIM][DIM])
{
 int row,col;
  printf("\n");
  for(row=0;row<DIM; row++,printf("\n"))
    for(col = 0 ;col< DIM ; col++)
	printf("%d ",mines[row][col]);
}
void setMines(int mines[DIM][DIM],int tot_mines)
{
 int row,col,mine_ctr=0;
 randomize();

    while(mine_ctr<tot_mines)
    {
    row= random(DIM);
    col=random(DIM);
    if(mines[row][col]!=9) //no mine
    {
     mines[row][col]=9;	   //set mine
     mine_ctr++;
     }
   }
}









void drawBox()
{
  int bcol,brow,ctr1,ctr2,ctr3;
    //(GS-US)/2
  bcol = (80 -((DIM*WIDTH)+DIM+1))/2;
  brow = (25-((DIM*HEIGHT)+DIM+1))/2;
  gotoxy(bcol+10,brow-1);
  printf("MINESWEEPER - SREC");
  gotoxy(bcol,brow);
   printf("%c",LT);
   for(ctr2=1;ctr2<= DIM; ctr2++)
   {
    for(ctr1=1;ctr1<=WIDTH;ctr1++)
       printf("%c",HL);
    printf("%c",TT);
   }
   printf("%c%c",BS,RT);
   //end of first line
   for(ctr3=1;ctr3<= DIM; ctr3++)
   {
   gotoxy(bcol,++brow);
   for(ctr2=1;ctr2<= DIM; ctr2++)
   {
    printf("%c",VL);
    for(ctr1=1;ctr1<=WIDTH;ctr1++)
       printf("%c",SPACE);
   }
    printf("%c",VL);
    gotoxy(bcol,++brow);
   printf("%c",LST);
   for(ctr2=1;ctr2<= DIM; ctr2++)
   {
    for(ctr1=1;ctr1<=WIDTH;ctr1++)
       printf("%c",HL);
    printf("%c",CROSS);
   }
   printf("%c%c",BS,RST);
  }
  //mid part
   gotoxy(bcol,brow);
   printf("%c",LB);
   for(ctr2=1;ctr2<= DIM; ctr2++)
   {
    for(ctr1=1;ctr1<=WIDTH;ctr1++)
       printf("%c",HL);
    printf("%c",BT);
   }
   printf("%c%c",BS,RB);
   //end of last line
}