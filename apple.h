#ifndef BADAPPLE_H
#define BADAPPLE_H

void badapple();

int getTotFrames(char *dir);
char *saveFrame(int i, char *dir);
char **saveFrames(char *dir, int totFrames);
void play(char **framse, int totFrames);
void progressBar(int corrente, int tot, int r, int frames);

#endif
