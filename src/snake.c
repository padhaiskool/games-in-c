#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77

int length;
int bend_no;
int len;
char key;
void record();
void load();
int life;
void Delay(long double);
void Move();
void Food();
int Score();
void Print();
void gotoxy(int x, int y);
void GotoXY(int x,int y);
void Bend();
void Boarder();
void Down();
void Left();
void Up();
void Right();
void ExitGame();
int Scoreonly();

struct coordinate
{
    int x;
    int y;
    int direction;
};

typedef struct coordinate coordinate;

coordinate head, bend[500],food,body[30];

int snake()
{
    system("color 30");

    char key;

    Print();



    return 0;


}

void Move()
{
    int a,i;

    do
    {

        Food();
        fflush(stdin);

        len=0;

        for(i=0; i<30; i++)

        {

            body[i].x=0;

            body[i].y=0;

            if(i==length)

                break;

        }

        Delay(length);

        Boarder();

        if(head.direction==RIGHT)

            Right();

        else if(head.direction==LEFT)

            Left();

        else if(head.direction==DOWN)

            Down();

        else if(head.direction==UP)

            Up();

        ExitGame();

    }
    while(!kbhit());

    a=getch();

    if(a==27)

    {

        system("cls");

        exit(0);

    }
    key=getch();

    if((key==RIGHT&&head.direction!=LEFT&&head.direction!=RIGHT)||(key==LEFT&&head.direction!=RIGHT&&head.direction!=LEFT)||(key==UP&&head.direction!=DOWN&&head.direction!=UP)||(key==DOWN&&head.direction!=UP&&head.direction!=DOWN))

    {

        bend_no++;

        bend[bend_no]=head;

        head.direction=key;

        if(key==UP)

            head.y--;

        if(key==DOWN)

            head.y++;

        if(key==RIGHT)

            head.x++;

        if(key==LEFT)

            head.x--;

        Move();

    }

    else if(key==27)

    {

        system("cls");

        exit(0);

    }

    else

    {

        printf("\a");

        Move();

    }
}

void gotoxy(int x, int y)
{

    COORD coord;

    coord.X = x;

    coord.Y = y;

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

}
void GotoXY(int x, int y)
{
    HANDLE a;
    COORD b;
    fflush(stdout);
    b.X = x;
    b.Y = y;
    a = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(a,b);
}
void load()
{
    system("color 80");
    int row,col,r,c,q;
    gotoxy(36,14);

    printf("LOADING GAME...");
    gotoxy(30,15);
    for(r=1; r<=20; r++)
    {
        for(q=0; q<=100000000; q++); //to display the character slowly
        printf("%c",177);
    }
    getch();
}
void Down()
{

    int i;
    for(i=0; i<=(head.y-bend[bend_no].y)&&len<length; i++)
    {
        GotoXY(head.x,head.y-i);
        {
            if(len==0){
                printf("\033[0;31m");
                printf("v");
        }
            else{
                printf("\033[0;31m");
                printf("=");
            }
        }
        body[len].x=head.x;
        body[len].y=head.y-i;
        len++;
    }
    Bend();
    if(!kbhit())
        head.y++;
}
void Delay(long double k)
{
    Score();
    long double i;
    for(i=0; i<=(10000000); i++);
}
void ExitGame()
{
    int i,check=0;
    for(i=4; i<length; i++) //starts with 4 because it needs minimum 4 element to touch its own body
    {
        if(body[0].x==body[i].x&&body[0].y==body[i].y)
        {
            check++;    //check's value increases as the coordinates of head is equal to any other body coordinate
        }
        if(i==length||check!=0)
            break;
    }
    if(head.x<=10||head.x>=70||head.y<=10||head.y>=30||check!=0)
    {
        life--;
        if(life>=0)
        {
            head.x=25;
            head.y=20;
            bend_no=0;
            head.direction=RIGHT;
            Move();
        }
        else
        {
            system("cls");
            printf("All lives completed\nBetter Luck Next Time!!!\nPress any key to quit the game\n");
            record();
            exit(0);
        }
    }
}
void Food()
{

    if(head.x==food.x&&head.y==food.y)
    {
        length++;
        time_t a;
        a=time(0);
        srand(a);
        food.x=rand()%70;
        if(food.x<=10)
            food.x+=11;
        food.y=rand()%30;
        if(food.y<=10)

            food.y+=11;
    }
    else if(food.x==0)/*to create food for the first time coz global variable are initialized with 0*/
    {
        food.x=rand()%70;
        if(food.x<=10)
            food.x+=11;
        food.y=rand()%30;
        if(food.y<=10)
            food.y+=11;
    }

}
void Left()
{
    int i;
    for(i=0; i<=(bend[bend_no].x-head.x)&&len<length; i++)
    {
        GotoXY((head.x+i),head.y);
        {
            if(len==0)
                {printf("\033[0;31m");
                printf("<");
            printf("\033[0m");}
            else
            {
            printf("\033[0;31m");
                printf("=");
            }
        }
        body[len].x=head.x+i;
        body[len].y=head.y;
        len++;
    }
    Bend();
    if(!kbhit())
        head.x--;

}
void Right()
{
    int i;
    for(i=0; i<=(head.x-bend[bend_no].x)&&len<length; i++)
    {
        //GotoXY((head.x-i),head.y);
        body[len].x=head.x-i;
        body[len].y=head.y;
        GotoXY(body[len].x,body[len].y);
        {
            if(len==0)
            {printf("\033[0;31m");
                printf(">");
            }
            else
            {printf("\033[0;31m");
                printf("=");}
        }
        /*body[len].x=head.x-i;
        body[len].y=head.y;*/
        len++;
    }
    Bend();
    if(!kbhit())
        head.x++;
}
void Bend()
{
    int i,j,diff;
    for(i=bend_no; i>=0&&len<length; i--)
    {
        if(bend[i].x==bend[i-1].x)
        {
            diff=bend[i].y-bend[i-1].y;
            if(diff<0)
                for(j=1; j<=(-diff); j++)
                {
                    body[len].x=bend[i].x;
                    body[len].y=bend[i].y+j;
                    GotoXY(body[len].x,body[len].y);
                    printf("\033[0;31m");
                    printf("*");
                    printf("\033[0m");
                    len++;
                    if(len==length)
                        break;
                }
            else if(diff>0)
                for(j=1; j<=diff; j++)
                {

                    body[len].x=bend[i].x;
                    body[len].y=bend[i].y-j;
                    GotoXY(body[len].x,body[len].y);
                    printf("\033[0;31m");
                    printf("*");
                    printf("\033[0m");
                    len++;
                    if(len==length)
                        break;
                }
        }
        else if(bend[i].y==bend[i-1].y)
        {
            diff=bend[i].x-bend[i-1].x;
            if(diff<0)
                for(j=1; j<=(-diff)&&len<length; j++)
                {
                    /*GotoXY((bend[i].x+j),bend[i].y);
                    printf("*");*/
                    body[len].x=bend[i].x+j;
                    body[len].y=bend[i].y;
                    GotoXY(body[len].x,body[len].y);
                    printf("\033[0;31m");
                    printf("*");
                    printf("\033[0m");
                    len++;
                    if(len==length)
                        break;
                }
            else if(diff>0)
                for(j=1; j<=diff&&len<length; j++)
                {
                    /*GotoXY((bend[i].x-j),bend[i].y);
                    printf("*");*/
                    body[len].x=bend[i].x-j;
                    body[len].y=bend[i].y;
                    GotoXY(body[len].x,body[len].y);
                    printf("\033[0;31m");
                    printf("*");
                    printf("\033[0m");
                    len++;
                    if(len==length)
                        break;
                }
        }
    }
}
void Boarder()
{
    system("cls");
    system("color 02");
    int i;
    GotoXY(food.x,food.y);   /*displaying food*/

    printf("X");

    for(i=10; i<71; i++)
    {
        GotoXY(i,10);
        printf("||");
        GotoXY(i,30);
        printf("||");
    }
    for(i=10; i<31; i++)
    {
        GotoXY(10,i);
        printf("||");
        GotoXY(70,i);
        printf("||");
    }
}
void Print()
{
    int choice;

    printf("\t\t\t\tWELCOME TO SNAKE GAME \n\n\t\t\t(press any key to continue)\n");

    printf("1. START GAME\n");
    printf("2. RULES\n");
    printf("3. SCORES\n");
    printf("4. QUIT\n");
    printf("\nEnter your choice: \n");
    scanf("%d",&choice);
    do
    {
        switch (choice)
        {
            case 1:
                printf("\n\nPress any key to play game...");
                getch();
                system("cls");

    load();

    length=5;

    head.x=25;

    head.y=20;

    head.direction=RIGHT;

    Boarder();

    Food(); //to generate food coordinates initially

    life=1; //number of extra lives

    bend[0]=head;

    Move();   //initialing initial bend coordinate


                break;

            case 2:
                rules();
                break;

            case 3:
                record();
                break;

            case 4:
                system("cls");
                printf("Thanks for playing!");
                exit(0);
                break;

            default:
               printf("Invalid choice");
               break;

        }
    } while(choice!=-1);



}
/*
void record()
{
    char plname[20],nplname[20],cha,c,score[32];
    int i,j,px;
    FILE *info;

    system("cls");
    printf("Enter your name\n");

    scanf("%[^\n]",plname);

    snprintf(score, 32, "%s.txt", plname);
    info=fopen("record.txt","a+");
    getch();



    for(j=0; plname[j]!='\0'; j++) //to convert the first letter after space to capital
    {
        nplname[0]=toupper(plname[0]);
        if(plname[j-1]==' ')
        {
            nplname[j]=toupper(plname[j]);
            nplname[j-1]=plname[j-1];
        }
        else nplname[j]=plname[j];
    }
    nplname[j]='\0';

    fprintf(info,"Player Name :%s\n",nplname);

    time_t mytime;
    mytime = time(NULL);
    fprintf(info,"Played Date:%s",ctime(&mytime));

    fprintf(info,"Score:%d\n",px=Scoreonly());//call score to display score

    for(i=0; i<=50; i++)
        fprintf(info,"%c",'_');
    fprintf(info,"\n");
    fclose(info);
    printf("\033[0;31m");
    printf("Wanna see past records press 'y'\n");
    printf("\033[0m");
    cha=getch();
    system("cls");
    if(cha=='y')
    {
        info=fopen("record.txt","r");
        do
        {
            putchar(c=getc(info));
        }
        while(c!=EOF);
    }
    fclose(info);
    getch();
    system("cls");
    main();
}
*/
void record()
{
    char plname[20],nplname[20],cha,c,score[32];

    char buffer[256];
    int line,n,m;

    int i,j,px;
    system("cls");
    printf("Enter your name\n");
    scanf("%s",plname);

    FILE *info;
    snprintf(score, 32, "Records/%s.txt", plname);
    info=fopen(score,"a+");

    getch();



    //************************

    for(j=0; plname[j]!='\0'; j++) //to convert the first letter after space to capital
    {
        nplname[0]=toupper(plname[0]);
        if(plname[j-1]==' ')
        {
            nplname[j]=toupper(plname[j]);
            nplname[j-1]=plname[j-1];
        }
        else nplname[j]=plname[j];
    }
    nplname[j]='\0';


    fprintf(info,"Player Name :%s\n",nplname);
    fprintf(info,"SNAKE GAME\n");

    time_t mytime;
    mytime = time(NULL);
    fprintf(info,"Played Date:%s",ctime(&mytime));

    fprintf(info,"Score:%d\n",px=Scoreonly());//call score to display score

    for(i=0; i<=50; i++)
        fprintf(info,"%c",'_');
    fprintf(info,"\n");
    fclose(info);
    printf("\033[0;31m");
    printf("Wanna see past records press 'y'\n");
    printf("\033[0m");
    cha=getch();
    system("cls");
    if(cha=='y')
    {
        info=fopen(score,"r");
        do
        {
            putchar(c=getc(info));
        }
        while(c!=EOF);
    }

    fclose(info);
    getch();
    system("cls");
    main();
}
int Score()
{

    int score;
    GotoXY(20,8);
    score=length-5;
    printf("\033[0;33m");
    printf("SCORE : %d",(length-5));
    score=length-5;
    GotoXY(50,8);
    printf("Life : %d",life);
    printf("\033[0m");
    return score;
}
int Scoreonly()
{
    int score=Score();
    system("cls");
    return score;
}
void Up()
{
    int i;
    for(i=0; i<=(bend[bend_no].y-head.y)&&len<length; i++)
    {
        GotoXY(head.x,head.y+i);
        {
            if(len==0)
            {printf("\033[0;31m");
                printf("^");}
            else
                {printf("\033[0;31m");
                printf("=");}
        }
        body[len].x=head.x;
        body[len].y=head.y+i;
        len++;
    }
    Bend();
    if(!kbhit())
        head.y--;
}
