//badapple.c - Simone Tmm (https://youtu.be/75HNLw9doeI)
//##################################################################################################################
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#ifdef _WIN32
    #include <windows.h>
    #define sleepMs(x) Sleep(x)
#else
    #include <unistd.h>
    #define sleepMs(x) usleep(x * 1000)
#endif

#define PROJECTNAME "台北風光正，北科學子強， 科技創新樂，大道至真良。"
#define DIRECTORY "frame"
#define PREFISSO "/BA"
#define FILETOT "/numberOfFrames.txt"
#define LEN 68
#define INIZIO 0
#define WAIT 23
#define LARGHEZZA 80
#define DEBUG 1
#define FPS 30

int getTotFrames(char *dir);
char *saveFrame(int i, char *dir);
char **saveFrames(char *dir, int totFrames);
void play(char **framse, int totFrames);
void progressBar(int corrente, int tot, int r, int frames);

void badapple()
{
    int totFrames;
    char **frames;
    totFrames=getTotFrames(DIRECTORY);

    // printf("%s\n", PROJECTNAME);
    // system("PAUSE");

    if(totFrames==-1)
        return;

    frames=saveFrames(DIRECTORY, totFrames);

    if(frames==NULL)
		return;

    // printf("(PLAY) --> ");
    // system("PAUSE");

    play(frames, totFrames);

    return;
}

void play(char **frames, int totFrames)
{
    int i, j;

    for(i=INIZIO;i<totFrames;i++)
    {
        #if DEBUG
        char framesCount[100];
        sprintf(framesCount, "(frame: %d/%d) \n", i+1, totFrames);
        printf(PROJECTNAME);
        printf("\n");
        int x=LARGHEZZA-strlen(PROJECTNAME)-strlen(framesCount);
        for(j=0;j<=x;j++)
            printf(" ");
        printf("%s", framesCount);
        printf("%s", frames[i]);
        progressBar(i, totFrames, 0, 0);
        sleepMs(WAIT);
        #else
        printf("%s\n", frames[i]);
        sleepMs(WAIT);
            #endif
    }

}

void progressBar(int corrente, int tot, int r, int frames)
{
    corrente++;
    int cost, x;

    int i;
    float p = (float)((float)corrente/tot)*100;

    if(r==0)
    {
        cost=0;
        x=(corrente*(LEN-cost))/tot;

        printf("[");
        for(i=0;i<=x;i++)
            printf("#");
        for(i=0;i<LEN-x;i++)
            printf("-");
        printf("](%.2f%%)\n", p);
    }
    else if(r==1 && frames==1)
    {
        cost=25;
        x=(corrente*(LEN-cost))/tot;

        printf("saving frames: %d/%d ", corrente, tot);
        printf("[");
        for(i=0;i<=x;i++)
            printf("#");
        for(i=0;i<LEN-cost-x;i++)
            printf("-");
        printf("] (%.1f%%)\r", p);
    }
}

char **saveFrames(char *dir, int totFrames)
{
    int i;
    char **frames;
    frames=calloc(totFrames, sizeof(char*));

    for(i=INIZIO;i<totFrames;i++)
    {
        frames[i]=saveFrame(i, DIRECTORY);
        #if DEBUG
        progressBar(i, totFrames, 1, 1);
        #endif // DEBUG
    }
    printf("\n");

    return frames;
}

char *saveFrame(int i, char *dir)
{
    i++;
    char fileName[200], suffix[10];
    strcpy(fileName, dir);
    strcat(fileName, PREFISSO);
    sprintf(suffix, "%d.txt", i);
    strcat(fileName, suffix);

    FILE *f = fopen(fileName, "rb");
    fseek(f, 0, SEEK_END);
    long fsize = ftell(f);
    fseek(f, 0, SEEK_SET);

    char *string = malloc(fsize + 1);
    fread(string, 1, fsize, f);
    fclose(f);

    string[fsize] = '\0';

    return string;
}

int getTotFrames(char *dir)
{
    char fileName[200];
    strcpy(fileName, dir);
    strcat(fileName, FILETOT);
    int tot=-1;

    FILE *fin=fopen(fileName, "r");

    if(fin==NULL)
        return tot;

    fscanf(fin, "%d", &tot);
    fclose(fin);

    return tot;
}
//##################################################################################################################