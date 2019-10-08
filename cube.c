#include <stdio.h> 
#include <windows.h>
#include <conio.h>  
#include <time.h>

#define FrameX 13
#define FrameY 3
#define Frame_Height 20
#define Frame_Width 18

int i,j,temp,temp1,temp2;
int a[80][80] ={0};
int b[4];

struct Tetris
{
    int x;
    int y;
    int flag;
    int next;
    int speed;
    int numeber;
    int score;
    int level;
};
HANDLE hOut;

int color(int c);                     //控制台文字颜�?
void gotoxy(int x,int y);            //光标移动到指定位�?
void DrwaGameframe();                //绘制游戏边框
void Flag(struct Tetris *);          //随机产生方块类型序号
void MakeTetris(struct Tetris *);    //制作方块
void PrintTetris(struct Tetris *);   //打印方块
void CleanTetris(struct Tetris *);   //清楚方块痕迹
int  ifMove(struct Tetris *);        //判断是否能移动，return 1 能移�? 否则不能
void Del_Fullline(struct Tetris *);    //判断是否满行，并删除满行方块
void Gameplay();                     //游戏玩法
void regulation();                   //游戏规则
void explation();                    //按件说明
void welcome();                      //欢迎界面
void Replay(struct Tetris *) ;          //重新开始游�?
void title();                        //标题
void flower();                       //装饰
void close();                        //关闭游戏 

int main() {
    title();
    welcome();
    return 0;
}


int color(int c){
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),c);   //console文字颜色
  return 0;
}




void gotoxy(int x,int y)
{
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
}
void title(){
    color(15);
    gotoxy(24,3);
    printf("�����ϵ�֮����˹����");
    color(11);
    gotoxy(18,5);
    printf("������������������������������������");
    gotoxy(18,6);
    printf("������������������������������������");
    gotoxy(18,7);
    printf("������������������������������������");
}
void welcome(){
    int i;
    int j=1;
    int n;
    color(14);
    for(i=9;i<=20;i++)
    {
        for(j=15;j<=60;j++)
        {
            gotoxy(j,i);
            if(i == 9 || i == 20)
            {
                printf("_");
            }
            else if(j == 15 || j == 59)
            {
                printf("|");
            }

        }
    }
    color(12);
    gotoxy(25,12);
    printf("1.��ʼ");
    gotoxy(40,12);
    printf("2.����");
    gotoxy(25,17);
    printf("3.����");
    gotoxy(40,17);
    printf("4.�˳�");

    gotoxy(21,22);
    printf("��ѡ��[1 2 3 4]: [ ]\b\b");
    scanf("%d",&n);
    switch (n)
    {
    case 1:
        system("cls");
        DrwaGameframe();
        Gameplay();
        break;
    case 2:
        break;
    case 3:
        break;
    case 4:
        exit(0);
        break;
    } 
}


void DrwaGameframe()
{
    gotoxy(FrameX+Frame_Width-7,FrameY-2);
    color(12);
    printf("�ػ�����˹�������");

    color(12);
    gotoxy(FrameX,FrameY);
    printf("��");
    gotoxy(FrameX+2*Frame_Width-2,FrameY);
    printf("��");
    gotoxy(FrameX,FrameY+Frame_Height);
    printf("��");
    gotoxy(FrameX+2*Frame_Width-2,FrameY+Frame_Height);
    printf("��");
    for(i =2;i< 2*Frame_Width-2;i+=2)                  //�Ϻ��
    {
        gotoxy(FrameX+i,FrameY);
        printf("��");
    }
    for(i = 2;i<2*Frame_Width-2;i+=2)                //�º��
    {
        gotoxy(FrameX+i,FrameY+Frame_Height);
        printf("��");
        a[FrameX+i][FrameY+Frame_Height] = 2;
    }
    for(i = 1;i<Frame_Height;i++)                    //������
    {
        gotoxy(FrameX,FrameY+i);
        printf("��");
        a[FrameX][FrameY+i] =2;
    }
    
    for(i = 1;i < Frame_Height;i++)                  //��������
    {
        gotoxy(FrameX+2*Frame_Width-2,FrameY+i);
        printf("��");
        a[FrameX+2*Frame_Width-2][FrameY+i] = 2;
    }

    color(2);
    gotoxy(FrameX+2*Frame_Width+3,FrameY+7);
    printf("-------------��һ��");
    gotoxy(FrameX+2*Frame_Width+3,FrameY+13);
    printf("-------------");

    color(14);
    gotoxy(FrameX+2*Frame_Width+3,FrameY+17);
    printf("�ϣ���ת");
    gotoxy(FrameX+2*Frame_Width+3,FrameY+19);
    printf("�ո�:��ͣ��Ϸ");
    gotoxy(FrameX+2*Frame_Width+3,FrameY+15);
    printf("Esc���˳���Ϸ");

}

void MakeTetris(struct Tetris *tetris)
{
    a[tetris->x][tetris->y]= b[0];
    
    switch (tetris->flag)
        {
    case 1:
        {
              color(10);                                 //--
              a[tetris->x][tetris->y-1] = b[1];          //.-
              a[tetris->x+2][tetris->y-1] =b[2];
              a[tetris->x+2][tetris->y]= b[3];
              break;
        }
    case 2 :                                              //-
        {                                                //.
            color(13);                                    //-
            a[tetris->x][tetris->y-2]= b[1];              //-
            a[tetris->x][tetris->y-1]= b[2];
            a[tetris->x][tetris->y+1]= b[3];
            break;
        }
    case 3:                                               //-.--
        {
            color(13);
            a[tetris->x-2][tetris->y]= b[1];
            a[tetris->x+2][tetris->y]= b[2];
            a[tetris->x+4][tetris->y]= b[3];
            break;
        }   
    case 4:                                               //-.-
       {                                                  // -
            color(5);
            a[tetris->x-2][tetris->y]= b[1];
            a[tetris->x+2][tetris->y]= b[2];
            a[tetris->x][tetris->y+1]= b[3];
            break;
        }   
    case 5:                                               // -
       {                                                  //-.
            color(5);                                     // -
            a[tetris->x][tetris->y-1]= b[1];              
            a[tetris->x-2][tetris->y]= b[2];
            a[tetris->x][tetris->y+1]= b[3];
            break;
        }   
    case 6:                                               // -
       {                                                  //-.-
            color(5);
            a[tetris->x-2][tetris->y]= b[1];
            a[tetris->x][tetris->y-1]= b[2];
            a[tetris->x+2][tetris->y]= b[3];
            break;
        }   
    case 7:                                               //-
       {                                                  //.-
            color(5);                                     //-
            a[tetris->x][tetris->y-1]= b[1];              
            a[tetris->x+2][tetris->y]= b[2];
            a[tetris->x][tetris->y+1]= b[3];
            break;
       }
    case 8:                                               //--
       {                                                  // .-
            color(7);                                     
            a[tetris->x-2][tetris->y-1]= b[1];              
            a[tetris->x][tetris->y-1]= b[2];
            a[tetris->x+2][tetris->y]= b[3];
            break;
       }
    case 9:                                               // -
       {                                                  //.-
            color(7);                                     //-
            a[tetris->x+2][tetris->y-1]= b[1];              
            a[tetris->x+2][tetris->y]= b[2];
            a[tetris->x][tetris->y+1]= b[3];
            break;
       }
    case 10:                                              // --
       {                                                  //-.
            color(7);                                    
            a[tetris->x-2][tetris->y]= b[1];              
            a[tetris->x][tetris->y-1]= b[2];
            a[tetris->x+2][tetris->y-1]= b[3];
            break;
       }
    
    case 11:                                              //-
       {                                                  //.-
            color(7);                                     // -
            a[tetris->x][tetris->y-1]= b[1];              
            a[tetris->x+2][tetris->y]= b[2];
            a[tetris->x+2][tetris->y+1]= b[3];
            break;
       }
    case 12:                                              // --
       {                                                  //  .
            color(8);                                     //  -
            a[tetris->x-2][tetris->y-1]= b[1];              
            a[tetris->x][tetris->y-1]= b[2];
            a[tetris->x][tetris->y+1]= b[3];
            break;
       }
    case 13:                                              //   -
       {                                                  // -.-
            color(8);                                     //  
            a[tetris->x-2][tetris->y]= b[1];              
            a[tetris->x+2][tetris->y]= b[2];
            a[tetris->x+2][tetris->y-1]= b[3];
            break;
       }
    case 14:                                              // -
       {                                                  // .
            color(8);                                     // --
            a[tetris->x][tetris->y-1]= b[1];              
            a[tetris->x][tetris->y+1]= b[2];
            a[tetris->x+2][tetris->y+1]= b[3];
            break;
       }
    case 15:                                              // 
       {                                                  // -.-
            color(8);                                     // -
            a[tetris->x-2][tetris->y]= b[1];              
            a[tetris->x+2][tetris->y]= b[2];
            a[tetris->x-2][tetris->y+1]= b[3];
            break;
       }
    case 16:                                              // --
       {                                                  // .
            color(9);                                     // -
            a[tetris->x][tetris->y-1]= b[1];              
            a[tetris->x+2][tetris->y-1]= b[2];
            a[tetris->x][tetris->y+1]= b[3];
            break;
       }
    case 17:                                              //   
       {                                                  // -.-
            color(9);                                     //   -
            a[tetris->x-2][tetris->y]= b[1];              
            a[tetris->x+2][tetris->y]= b[2];
            a[tetris->x+2][tetris->y+1]= b[3];
            break;
       }
    case 18:                                              //  -
       {                                                  //  .
            color(9);                                     // --
            a[tetris->x][tetris->y-1]= b[1];              
            a[tetris->x][tetris->y+1]= b[2];
            a[tetris->x-2][tetris->y+1]= b[3];
            break;
       }
    case 19:                                              // -
       {                                                  // -.-
            color(9);                                     
            a[tetris->x-2][tetris->y-1]= b[1];              
            a[tetris->x-2][tetris->y]= b[2];
            a[tetris->x+2][tetris->y]= b[3];
            break;
       }
    }
}
void PrintTetris(struct Tetris *tetris)
{
        for(i=0;i<4;i++)
        {
            b[i]=1;
        }
       MakeTetris(tetris);
        for(i=tetris->x-2;i<=tetris->x+4;i+=2)
        {
            for(j = tetris->y-2;j <= tetris->y+1;j++)
            {
                if(a[i][j] == 1 && j>FrameY)
                {
                    gotoxy(i,j);
                    printf("��");
                }
            }
        }
        gotoxy(FrameX+2*Frame_Width+3,FrameY+1);
        color(4);
        printf("level: ");
        color(12);
        printf("%d",tetris->level);
        gotoxy(FrameX+2*Frame_Width+3,FrameY+3);
        printf("score: ");
        color(12);
        printf("%d",tetris->score);

        color(4);
        gotoxy(FrameX+2*Frame_Width+3,FrameY+5);
        printf("speed: ");
        color(12);
        printf("%dms",tetris->speed);    
}
int ifMove(struct Tetris *tetris)
{
    
    if(a[tetris->x][tetris->y] !=0 ){
        return 0;
    }
     else if(tetris->flag == 1  && (a[tetris->x][tetris->y-1] == 0 && a[tetris->x+2][tetris->y-1]== 0 && a[tetris->x+2][tetris->y]== 0)
     ||(tetris->flag == 2  && (a[tetris->x][tetris->y-2] == 0 && a[tetris->x][tetris->y-1] == 0 && a[tetris->x][tetris->y+1]== 0))
        ||(tetris->flag == 3  && (a[tetris->x-2][tetris->y]== 0 && a[tetris->x+2][tetris->y]== 0 && a[tetris->x+4][tetris->y]== 0))
        ||(tetris->flag == 4  && (a[tetris->x-2][tetris->y]== 0 && a[tetris->x+2][tetris->y]== 0 && a[tetris->x][tetris->y+1]== 0))
        ||(tetris->flag == 5  && (a[tetris->x][tetris->y-1]== 0 && a[tetris->x-2][tetris->y]== 0 && a[tetris->x][tetris->y+1]== 0))
        ||(tetris->flag == 6  && (a[tetris->x-2][tetris->y]== 0 && a[tetris->x][tetris->y-1]== 0 && a[tetris->x+2][tetris->y]== 0))
        ||(tetris->flag == 7  && (a[tetris->x][tetris->y-1]== 0 && a[tetris->x+2][tetris->y]== 0 && a[tetris->x][tetris->y+1]== 0))
        ||(tetris->flag == 8  && (a[tetris->x-2][tetris->y-1]== 0 && a[tetris->x][tetris->y-1]== 0 && a[tetris->x+2][tetris->y]== 0))
        ||(tetris->flag == 9  && (a[tetris->x+2][tetris->y-1]== 0 && a[tetris->x+2][tetris->y]== 0 && a[tetris->x][tetris->y+1]== 0))
        ||(tetris->flag == 10 && (a[tetris->x-2][tetris->y]== 0 && a[tetris->x][tetris->y-1]== 0 && a[tetris->x+2][tetris->y-1]== 0))
        ||(tetris->flag == 11 && (a[tetris->x][tetris->y-1]== 0 && a[tetris->x+2][tetris->y]== 0 && a[tetris->x+2][tetris->y+1]== 0))
        ||(tetris->flag == 12 && (a[tetris->x-2][tetris->y-1]== 0 && a[tetris->x][tetris->y-1]== 0 && a[tetris->x][tetris->y+1]== 0))
        ||(tetris->flag == 13 && (a[tetris->x-2][tetris->y]== 0 && a[tetris->x+2][tetris->y]== 0 && a[tetris->x+2][tetris->y-1]== 0))
        ||(tetris->flag == 14 && (a[tetris->x][tetris->y-1]== 0 && a[tetris->x][tetris->y+1]== 0 && a[tetris->x+2][tetris->y+1]== 0))
        ||(tetris->flag == 15 && (a[tetris->x-2][tetris->y]== 0 && a[tetris->x+2][tetris->y]== 0 && a[tetris->x+2][tetris->y+1]== 0))
        ||(tetris->flag == 16 && (a[tetris->x][tetris->y-1]== 0 && a[tetris->x+2][tetris->y-1]== 0 && a[tetris->x][tetris->y+1]== 0)) 
        ||(tetris->flag == 17 && (a[tetris->x-2][tetris->y]== 0 && a[tetris->x+2][tetris->y]== 0 && a[tetris->x+2][tetris->y+1]== 0))
        ||(tetris->flag == 18 && (a[tetris->x][tetris->y-1]== 0 && a[tetris->x][tetris->y+1]== 0 && a[tetris->x-2][tetris->y+1]== 0))
        ||(tetris->flag == 19 && (a[tetris->x-2][tetris->y-1]== 0 && a[tetris->x-2][tetris->y]== 0 && a[tetris->x+2][tetris->y]== 0)))
    {
       return 1;
    }
    return 0;
}
void CleanTetris(struct Tetris *tetris){
    for(i=0;i<4;i++)
    {
        b[i] = 0;
    }
        MakeTetris(tetris);
        for(i=tetris->x-2;i<=tetris->x+4;i+=2)
        {
            for(j = tetris->y-2;j<=tetris->y+1;j++)
            {
                if(a[i][j] == 0 && j>FrameY)
                {
                    gotoxy(i,j);
                    printf("  ");
                }
            }
        }        
    }

void Del_Fullline(struct Tetris *tetris){
    int k,del_row = 0;
    for(j = FrameX+Frame_Height-1;j>=FrameY+1;j--){
        k=0;
        for(i = FrameX+2;i<FrameX+2*Frame_Width-2;i+=2){
            if(a[i][j]==1){
                k++;
                if(k==Frame_Width-2){
                    for(k=FrameX;k<FrameX+2*Frame_Width-2;k+=2){
                        a[k][j]=0;
                        gotoxy(k,j);
                        printf("  ");
                    }
                    for(k = j -1 ;k>FrameY;k--){
                        for(i = FrameX +2 ;i<FrameX+2*Frame_Width-2;i+=2){
                            if(a[i][k]==1){
                                a[i][k] == 0;
                                gotoxy(i,k);
                                printf("  ");
                                a[i][k+1] == 1;
                                gotoxy(i,k+1);
                                printf("��");

                            }
                        }
                    }
                    j++;
                    del_row++;
                }
            }
        }
    }
    tetris->score+= 100*del_row;
    if(del_row>0 &&(tetris->score%1000 == 0 || tetris->score/1000>tetris->level-1)){
        tetris->speed -=20;
        tetris->level++;
    }
}
void Flag(struct Tetris *tetris){
    tetris->numeber++;
    srand(time(NULL));
    if(tetris->numeber == 1)
    {
        tetris->flag = rand()%19+1;
    }
    tetris->next = rand()%19+1;
}
void Gameplay()
{
    int n;
    struct Tetris t,*tetris= &t;
    char ch;
    tetris->numeber = 0;
    tetris->speed = 300;
    tetris->score = 0;
    tetris->level =1 ;
    while(1)
    {
        Flag(tetris);
        temp = tetris->flag;
        tetris->x = FrameX+ 2*Frame_Width+6;
        tetris->y = FrameY+10;
        tetris->flag =tetris->next;
        PrintTetris(tetris);
        tetris->x = FrameX+Frame_Width;
        tetris->y = FrameY-1;
        tetris->flag = temp; 
        //�������� 
        while(1)
        {
            label:PrintTetris(tetris);
            Sleep(tetris->speed);
            CleanTetris(tetris);
            temp1=tetris->x;
            temp2=tetris->flag;
            if(kbhit())
            {
                ch=getch();
                if(ch==75)
                {
                    tetris->x-=2;
                }
                if(ch==77)
                {
                    tetris->x+=2;
                }
                if(ch==80)
                {
                    if(ifMove(tetris)!=0)
                    {
                        tetris->y+=2;
                    }
                    if(ifMove(tetris)==0)
                    {
                        tetris->y=FrameY+Frame_Height-2;
                    }
                }
                if(ch==72)
                {
                    if(tetris->flag>=2 && tetris->flag<=3)
                    {
                        tetris->flag++;
                        tetris->flag%=2;
                        tetris->flag+=2;
                    }
                    if(tetris->flag>=4 && tetris->flag<=7)
                    {
                        tetris->flag++;
                        tetris->flag%=4;
                        tetris->flag+=4;
                     }
                    if(tetris->flag>=8 && tetris->flag<=11)
                    {
                        tetris->flag++;
                        tetris->flag%=4;
                        tetris->flag+=8;
                    }
                    if(tetris->flag>=12 && tetris->flag<=15)
                    {
                        tetris->flag++;
                        tetris->flag%=4;
                        tetris->flag+=12;
                    }
                    if(tetris->flag>=16 && tetris->flag<=19)
                    {
                        tetris->flag++;
                        tetris->flag%=4;
                        tetris->flag+=16;
                    }
                }
            if(ch == 32)
            {
                PrintTetris(tetris);
                while(1){
                    if(kbhit()){
                        ch=getch();
                        if(ch == 32){
                            goto label;
                        }
                    }
                }
            }
            if(ch == 27){
                system("cls");
                memset(a,0,6400*sizeof(int));
                welcome();
            }
            if(ifMove(tetris) == 0){
                tetris->x = temp1;
                tetris->flag= temp2;
            }
            else {
                goto label;
            }
        }
        tetris->y++;
        if(ifMove(tetris)== 0){
            tetris->y--;
            PrintTetris(tetris);
            Del_Fullline(tetris);
            break;
        }
    }
  
    for(i=tetris->y-2;i< tetris->y+2;i++)
    {
        if(i==FrameY){
            system("cls");
            gotoxy(29,7);
            printf("   \n");
            color(12);
            printf("�������ٽ�������!");
            gotoxy(17,18);
            color(14);
            printf("����һ��---------------1");
            gotoxy(44,18);
            printf("����");
            int n;
            gotoxy(32,20);
            printf("��ѡ��1/2����");
            color(11);
            scanf("%d",&n);
            switch(n)
            {
                case 1:
                    system("cls");
                    Replay(tetris);   //���¿�ʼ��Ϸ 
                    break;
                case 2:
                    exit(0);
                    break;
            }
        }
    }
    tetris->flag = tetris->next;
    tetris->x = FrameX+2*Frame_Width+6;
    tetris->y = FrameX + 10;
    CleanTetris(tetris);
    }
}

void Replay(struct Tetris *tetris)
{
    system("cls");
    memset(a,0,6400*sizeof(int));
    DrwaGameframe();
    Gameplay();
}