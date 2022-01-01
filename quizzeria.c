#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

struct Question
{
    char question[128], option1[128], option2[128], option3[128], option4[128], hint[128];
    char answer;
}question;


int score = 0;
int lives = 3;
int catchoice = 0;
int done[25];
char CATEGORIES[4][16] = {"Anime", "Cinema","Geography", "History"};
char name[30];
char scorepath[32];

void welcome();
void startGame();
void showCategory(int category);
struct Question selectQuestion(int category);
int isDone(int number);
void gameOver();
void loadHighScores(char name);
void insertHighScores(char *plname);
void rules();

int quiz()
{
    for(int i = 0; i < 25; i++)
    {
        done[i] = 0;
    }
    system("cls");
    printf("\033[0;31m");
    printf("\nENTER YOUR NAME: ");
	scanf("%s", &name);
    snprintf(scorepath, 32, "Records/%s.txt", name);
    welcome();
    return 0;
}


void welcome()
{
    int choice = 0;
    lives = 3;
    score = 0;
    system("cls");
    printf("\nWELCOME TO QUIZERIA %s\n",name);
    printf("\n********Main Menu*********\n");
    printf("1. START GAME\n");
    printf("2. RULES/HELP\n");
    printf("3. QUIT\n");
    printf("\nEnter your choice: \n");
    scanf("%d",&choice);
    do
    {
        switch (choice)
        {
            case 1:
                startGame();
                break;

            case 2:
                rules();
                break;

            case 3:
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

//Shows category menu to choose from.
void startGame()
{
    system("cls");
    printf("\n**********CATEGORIES********\n");
    printf("1. %s\n",CATEGORIES[0]);
    printf("2. %s\n",CATEGORIES[1]);
    printf("3. %s\n",CATEGORIES[2]);
    printf("4. %s\n",CATEGORIES[3]);
    printf("\nEnter your choice\n");
    scanf("%d",&catchoice);
    showCategory(catchoice);
}

//Selects a question randomly and reads the data
struct Question selectQuestion(int category)
{
    struct Question question;
    srand(time(NULL));

    int number;
    do
    {
        number = (rand() % 25) + 1;
    } while(!isDone(number));

    //creating file path from category and random number
    char path[32];
    snprintf(path, 32, "questions/%d/%d.txt", category, number);

    //reading from file
    FILE *fp;
    fp = fopen (path,"r");
    if (fp!=NULL)
    {
        fgets(question.question, 128, fp);
        fgets(question.option1, 128, fp);
        fgets(question.option2, 128, fp);
        fgets(question.option3, 128, fp);
        fgets(question.option4, 128, fp);
        fscanf(fp, "%c", &question.answer);

        fclose(fp);
    }
    return question;
}

//Checks whether this question is done or not for question number
int isDone(int number)
{
    int i;
    for(i = 0; done[i] != 0; i++)
    {
        if(done[i] == number)
            return 0;
    }
    done[i] = number;
    return 1;
}

//Shows questions from the selected category.
void showCategory(int category)
{
    do
    {
        //Loop breaks after 3 wrong answers
        struct Question question = selectQuestion(category);
        char choice;
        char answer;

        system("cls");
        printf("\n%s",CATEGORIES[category-1]);
        printf("\nScore : %d", score);
        printf("\nLives left: %d",lives);
        printf("\n_________________________________\n");
        printf("\n");
        fflush(stdin);
        printf(question.question);
        printf("\n");
        printf(question.option1);
        //printf("\n");
        printf(question.option2);
        //printf("\n");
        printf(question.option3);
        //printf("\n");
        printf(question.option4);
        //printf("%c",question.answer);
        printf("\n\nEnter your answer\n");
        scanf("%c",&choice);
        //choice = getch();
        choice = toupper(choice);
        if(choice == question.answer)
        {
            score +=  2;
            printf("\nCorrect Answer!!");
            continue;
        }
        else
        {
             //score -= 2;
            lives -=1;
            printf("\nWrong Answer!! You lose a life");
            printf("\nLives left: %d",lives);
            if(lives<=0)
            {
                gameOver();
            }
            continue;
        }

    } while(1);
}

//gameOver
void gameOver()
{
    system("cls");

    // struct HighScore tempHS;
    // strcpy(tempHS.name, name);
    // tempHS.score = score;

    printf("\nGame Over!!\nYou're out of lives\n");
    printf("\nPlayer name: %s\nScore: %d", name, score);
    insertHighScores(name);
    printf("\nPress any key to Play Again...");
    getch();
    welcome();
    main();
}

//Shows the rules of the game.
void rules()
{
    system("cls");
    printf("\n\n*********RULES*******");
    printf("\n_________________________________\n");
    printf("\nPress any key to continue... ");
    getch();
    welcome();
    main();
}

void insertHighScores(char *plname)
{
    int i,j;
    char cha,c;

    FILE *fp;
    fp = fopen (scorepath,"a+");
    //fprintf(fp,"Player Name :%s\n",hs.name);
    //for date and time

    fprintf(fp,"Player Name :%s\n",plname);
    fprintf(fp,"QUIZ GAME\n");

    time_t mytime;
    mytime = time(NULL);
    fprintf(fp,"Played Date:%s",ctime(&mytime));
    fprintf(fp,"Topic: %s\n",CATEGORIES[catchoice-1]);
    fprintf(fp,"Score: %d\n",score);

    for(i=0; i<=50; i++)
        fprintf(fp,"%c",'_');
    fprintf(fp,"\n");

    fclose(fp);

    printf("\033[0;31m");
    printf("\nWanna see your past records? Press 'y'\n\n");
    printf("\033[0m");
    getchar();
    scanf("%c",&cha);

    if(cha=='y')
    {
        system("cls");
        printf("\033[0;31m");
        printf("*********PLAYER HISTORY*********");
        printf("\n_________________________________\n");
        fp =fopen(scorepath,"r");
        do
        {
            putchar(c=getc(fp));
        }
        while(c!=EOF);
    }
    fclose(fp);
    getch();
    system("cls");
    main();

}

