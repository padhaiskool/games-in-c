#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

#define WORDS 10
#define WORDLEN 40
#define CHANCE 6
void record_hang();

bool srand_called = false;

int i_rnd(int i)
{
    if (!srand_called)
    {
        srand(time(NULL) << 10);
        srand_called = true;
    }
    return rand() % i;
}
void printBody(int mistakes, char* body)
{
    printf("\tMistakes :%d\n", mistakes);
    switch(mistakes)
    {
        case 1: body[1] = ')';
                body[0] = '(';
                break;
        case 2: body[2] = '/';
                break;
        case 3: body[3] = '|';
                break;
        case 4: body[4] = '\\';
                break;
        case 5: body[5] = '/';
                break;
        case 6: body[6] = '\\';
                break;
        default: break;
    }
    printf("\033[0;31m");
    printf("\t _________\n"
        "\t|         |\n"
        "\t|        %c %c\n"
        "\t|        %c%c%c\n"
        "\t|        %c %c\n"
        "\t|             \n"
        "\t|             ", body[0], body[1], body[2],
        body[3], body[4], body[5], body[6]);
}

void printWord(char* guess, int len)
{
    printf("\t");
    for (int i = 0; i < len; ++i)
    {
        printf("%c ", guess[i]);
    }
    printf("\n\n");
}

int hangman()
{
    char name[50];
    int choice;
    //printf("Enter your name: ");
    //gets(name);

    //Rules of the Game
    printf("\n\t Be aware you can be hanged!!.");
    printf("\n\n\t Rules : ");
    printf("\n\t - Maximum 6 mistakes are allowed.");
    printf("\n\t - All alphabet are in lower case.");
    printf("\n\t Syntax : Alphabet");
    printf("\n\t Example : a \n\n");

    //choosing a category
    printf("\n\tSelect a Category:\n");
    printf("\t1. Popular Websites\n");
    printf("\t2. Movies\n");
    printf("\t3. Musical Instruments\n");
    printf("\t4. Animals\n");
    printf("\t5. Disney/Pixar Characters\n");
    printf("\n\tEnter your choice: ");
    scanf("%d", &choice);

    char *word, *hint;
    int id = i_rnd(WORDS); //generating a random integer
    switch (choice)
    {
        case 1: {
                char values[WORDS][WORDLEN] = {"google","github","linkedin", "instagram","gmail", "facebook", "youtube","wikipedia","amazon", "twitter"};
                char hints[WORDS][100] = {"Has the Answers to all your Questions!",
                "Commonly used to host Open-Source Projects",
                "A Professional Networking Platform",
                "Social Media Platform",
                "Email Service",
                "Social Media Platform",
                "Like, Share and Subscribe!",
                "Biggest Encyclopedia",
                "Largest Marketplace online",
                "Larry - The Bird"};
                word = values[id];
                hint = hints[id];
            break;
        }
        case 2:{
                char values[WORDS][WORDLEN] = {"aladdin","bambi","grease", "titanic","jumanji", "frozen", "spiderman","moonlight","godzilla", "interstellar"};
                char hints[WORDS][100] = {"The One with the Magical Flying Carpet",
                "The Fawn, The Rabbit and The Skunk",
                "Popular Musical of the 1970s",
                "The One with the Heart of the Ocean",
                "The One with the Jungle Board Game",
                "Adaptation of the Ice Queen",
                "The one with a Radioactive arachnid",
                "Won 3 categories in the 2017 Academy Awards out of 8 nominations",
                "The King of Monsters",
                "The One with the Wormhole and the Survival of Humanity"};
                word = values[id];
                hint = hints[id];
            break;
        }
        case 3:
        {
            char values[WORDS][WORDLEN] = {"guitar", "piano", "sitar", "tabla", "harp", "trumpet", "accordion","bagpipe","flute", "cello"};
            char hints[WORDS][100] = {"The One with six strings",
            "The One with 88 keys",
            "Amit Khusrow is credited with its invention",
            "Indian Percussion Instrument",
            "A 47 stringed instrument",
            "A Brass Instrument played in Classical and Jazz music",
            "Invented by Friedrich Buschmann",
            "Played on St.Andrew's Day in Scotland",
            "Woodwind instrument that can be made of metal as well. Essential component of Classical Music.",
            "The second-largest bowed string instrument"};
            word = values[id];
            hint = hints[id];
            break;
        }
        case 4:
        {
            char values[WORDS][WORDLEN] = {"comet", "eclipse", "pluto", "nebula", "constellation", "whale", "porcupine","penguin","eagle", "ostrich"};
            char hints[WORDS][100] = {
            "Herbivores Animals having a single horn",
            "To laugh like a ______",
            "A striped animal",
            "An animal whose name rhymes with drama and belongs to the Camel Family ",
            "King of the Jungle",
            "Largest Mammal on Earth",
            "Covered in Quills",
            "A Bird that can live on both land and in water ",
            "A Predatory Bird, known for its eyesight" ,
            "Largest Flightless bird"};
            word = values[id];
            hint = hints[id];
            break;
        }
        case 5:
        {
            char values[WORDS][WORDLEN] = {"figaro", "simba", "flounder", "mushu", "woody", "dug", "dumbo","abu","merida", "tinkerbell"};
            char hints[WORDS][100] = {"Geppetto's pet in Pinocchio",
            "Son of Mufasa and Sarabi",
            "Ariel's best friend",
            "Fast-talking Chinese Dragon",
            "Pull-string Cowboy",
            "Overweight Golden Retriever who belongs to Charles Muntz. ",
            "The Flying Elephant",
            "Aladdin's pet monkey",
            "Princess of DunBroch",
            "Fairy in Pixie Hollow"};
            word = values[id];
            hint = hints[id];
            break;
        }
    default:
        break;
    }

    char *body = malloc(CHANCE+1);
    int len = strlen(word);

    char *guessed = malloc(len);
    char falseWord[CHANCE];

    memset(body, ' ', CHANCE+1);
    memset(guessed, '_', len);

    char guess;
    bool found;
    char* win;

    int mistakes = 0;
    setvbuf(stdin, NULL, _IONBF, 0);

    do
    {
        found = false;
        printf("\n\n");
        printf("\tHint: %s\n", hint);
        printBody(mistakes, body);
        printf("\n\n");
        printf("\tFalse Letters : ");
        if(mistakes == 0)
        {
            printf("None\n");
        }
        for (int i = 0; i < mistakes; ++i)
        {
            printf("%c", falseWord[i]);
        }
        printf("\n\n");
        printWord(guessed, len);
        printf("\033[0;30m");
        printf("\tGive me a alphabet in lower case : ");
        do
        {
            scanf("%c", &guess);
        }while (getchar() != '\n' );
        for (int i = 0; i < len; ++i)
        {
            if(word[i] == guess)
            {
                found = true;
                guessed[i] = guess;
            }
        }
        if(!found)
        {
            falseWord[mistakes] = guess;
            mistakes += 1;
        }
        win = strchr(guessed, '_'); //returns pointer to first occurence of '_'
    }while(mistakes < CHANCE && win != NULL);

    if(win == NULL)
    {
        char a[5]="WIN";
        printf("\n");
        printWord(guessed, len);
        printf("\n\tCongrats! You have won : %s\n\n", word);
        record_hang(a);
    }
    else
    {
        char a[5]="LOST";
        printf("\n");
        printBody(mistakes, body);
        printf("\n\n\tBetter try next time. Word was %s\n\n", word);
        record_hang(a);
    }
    free(body);
    free(guessed);
    return EXIT_SUCCESS;
}

void record_hang(char a[5])
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
    fprintf(info,"Hangman GAME\n");

    time_t mytime;
    mytime = time(NULL);
    fprintf(info,"Played Date:%s",ctime(&mytime));
    fprintf(info,"You %s!\n",a);

    //fprintf(info,"Score:%d\n",px=Scoreonly());//call score to display score

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
        system("cls");
        printf("\033[0;31m");
        printf("*********PLAYER HISTORY*********");
        printf("\n_________________________________\n");
        info =fopen(score,"r");
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
