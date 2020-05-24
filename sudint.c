#include "stdio.h"
#include "stdlib.h"
#include "time.h"

struct field {
    int i;
    int j;
};

void output (char sud[9][9][10]) {
    int i, j;
    for (i=0; i<9; i++) {
        for (j=0; j<9; j++) {
             printf("%d ", sud[i][j][0]);
        }
        printf("\n");
    }
}

void copy (char source[9][9][10], char target[9][9][10]) {
    int i, j, k;
    for (i=0; i<9; i++) {
        for (j=0; j<9; j++) {
            for (k=0; k<10; k++) {
                target[i][j][k]=source[i][j][k];
            }
        }
    }    
}

void strikeout (char sud[9][9][10], int str, int col) { // вычеркивание возможных вариантов после заполнения клетки
    
    int i, j;
    char num=sud[str][col][0];
    for (i=0; i<9; i++) {
        sud[str][i][num]=0;
    }
    for (j=0; j<9; j++) {
        sud[j][col][num]=0;
    }
    for (i=((int)str/3)*3; i<((int)str/3)*3+3; i++){
        for (j=((int)col/3)*3; j<((int)col/3)*3+3; j++){
            sud[i][j][num]=0;
        }
    }
}

struct field findempty(char sud[9][9][10], struct field startfield) {
    int i, j;
    struct field newfield;
    newfield.i=-1;
    newfield.j=-1;
    for (j=startfield.j; j<9; j++) {
        if (!sud[startfield.i][j][0]) {
            newfield.i=startfield.i;
            newfield.j=j;
            return newfield;
        }
    }
    for (i=startfield.i+1; i<9; i++) {
        for (j=0; j<9; j++) {
            if (!sud[i][j][0]) {
                newfield.i=i;
                newfield.j=j;
                return newfield;
            }
        }
    }
    return newfield;
}

char findnum(char sud[9][9][10], int i, int j, int counters[10]) {
    int k, num=0;
    for (k=1; k<10; k++) {
        if (sud[i][j][k]) {
            num=k;
            sud[i][j][k]=0;
            counters[6]++;
            return num;
        }
    }
}

char oneleft(char sud[9][9][10], int counters[10]) { // поиск клетки с одним числом
    int i, j, k;
    char count=0;
    char insnum=0;
    for (i=0; i<9; i++) {
        for (j=0; j<9; j++) {
            if (!sud[i][j][0]) {
                for (k=1; k<10; k++) {
                    if (sud[i][j][k]) {
                        count++;
                        insnum=k;
                    } 
                }
                if (!(count-1)) {
                    sud[i][j][0]=insnum;
                    strikeout (sud, i, j);
                    counters[1]++;
                    return 1;
                }
                count=0;
            }    

        }
    }
    return 0;
}

char oneinstr(char sud[9][9][10], int counters[10]) { // поиск строки с единственным вхождением числа

    int i, j, k;
    int count=0, col=0;

    for (j=0; j<9; j++) {
        for (k=1;k<10; k++) {
            for (i=0; i<9; i++) {
                if (!sud[i][j][0] & sud[i][j][k]) {
                    count++;
                    col=i;
                }
            }
            if (count==1) {
                sud[col][j][0]=k;
                strikeout (sud, col, j);
                counters[2]++;
                return 1;
            }
            count=0;
        }
    }
    return 0;
}

char oneincol(char sud[9][9][10], int counters[10]) { // поиск столюца с единственным вхождением числа

    int i, j, k;
    int count=0, str=1;
    
    for (i=0; i<9; i++) {
        for (k=1;k<10; k++) {
            for (j=0; j<9; j++) {
                if (!sud[i][j][0] & sud[i][j][k]) {
                    count++;
                    str=j;
                }
            }
            if (count==1) {
                sud[i][str][0]=k;
                strikeout (sud, i, str);
                counters[3]++;
                return 1;
                
            }
            count=0;
        }
    }
    return 0;
}

char oneinsqr(char sud[9][9][10], int counters[10]) { // поиск квадрата с единственным вхождением числа

    int i, j, k, is, js;
    int count=0, str=0, col=0;
    
    for (is=0; is<3; is++) {
        for (js=0; js<3; js++) {
            for (k=1; k<10; k++) {
                for (i=is*3; i<is*3+3; i++) {
                    for (j=js*3; j<js*3+3; j++) {
                        if (!sud[i][j][0] & sud[i][j][k]) {
                             count++;
                             str=i;
                             col=j;
                        }
                    }
                }
                if (count==1) {
                    sud[str][col][0]=k;
                    strikeout (sud, str, col);
                    counters[4]++;
                    return 1;
                }
                count=0;
            }
        }

    }
    return 0;
}


void sol(char sud[9][9][10], struct field currentfield, int counters[10]) {

    char newsud[9][9][10], tempsud[9][9][10];
    struct field newfield, nullfield;
    nullfield.i=0;
    nullfield.j=0;
    char num, flag=0;

    counters[5]++;

    copy(sud, newsud);

    do {
        flag=oneleft(newsud, counters);
        if (!flag) {
            flag=oneincol(newsud, counters);
        }
        if (!flag) {
            flag=oneinstr(newsud, counters);
        }
        if (!flag) {
            flag=oneinsqr(newsud, counters);
        }
    } while (flag);

    currentfield=findempty(newsud, nullfield);
    if (!(currentfield.i+1)) {
        counters[0]++;
        printf("решение номер %d\n", counters[0]);
        output(newsud);
        return;
    } 


    do {
        newsud[currentfield.i][currentfield.j][0]=findnum(newsud, currentfield.i, currentfield.j, counters);
        if (newsud[currentfield.i][currentfield.j][0]) {
            copy(newsud, tempsud);
            strikeout(tempsud, currentfield.i, currentfield.j);
            newfield=findempty(tempsud, currentfield);
            if (newfield.i+1) {
                sol(tempsud, newfield, counters);
            } else {
                counters[0]++;
                printf("решение номер %d\n", counters[0]);
                output(tempsud);
            }
        }
    } while(newsud[currentfield.i][currentfield.j][0]);
    return;
}

int main() {

    struct field currentfield, nullfield;
    nullfield.i=0;
    nullfield.j=0;
    
    int i,j,k;
    int counters[10]={0,0,0,0,0,0,0,0,0,0};

    char sud[9][9][10];
    for (i=0; i<9; i++) {
       for (j=0; j<9; j++) {
          sud[i][j][0]=0;
          for (k=1; k<10; k++) {
            sud[i][j][k]=1;
          }  
        }
    }


char str0[10]={0,0,0,0,0,0,0,0,0,0};
char str1[10]={1,0,0,0,0,0,0,0,0,0};
char str2[10]={0,0,0,0,0,0,0,0,0,0};
char str3[10]={0,0,0,0,0,0,0,0,0,0};
char str4[10]={0,0,0,0,0,0,0,0,0,0};
char str5[10]={0,0,0,0,0,0,0,0,0,0};
char str6[10]={0,0,0,0,0,0,0,0,0,0};
char str7[10]={0,0,0,0,0,0,0,0,0,0};
char str8[10]={0,0,0,0,0,0,0,0,0,0};

printf("ввод судоку:\n");

scanf("%s", str0);
scanf("%s", &str1);
scanf("%s", &str2);
scanf("%s", &str3);
scanf("%s", &str4);
scanf("%s", &str5);
scanf("%s", &str6);
scanf("%s", &str7);
scanf("%s", &str8);

for (i=0; i<9; i++) {
    sud[0][i][0]=str0[i]-'0';
    sud[1][i][0]=str1[i]-'0';
    sud[2][i][0]=str2[i]-'0';
    sud[3][i][0]=str3[i]-'0';
    sud[4][i][0]=str4[i]-'0';
    sud[5][i][0]=str5[i]-'0';
    sud[6][i][0]=str6[i]-'0';
    sud[7][i][0]=str7[i]-'0';
    sud[8][i][0]=str8[i]-'0';
}

for (i=0; i<9; i++) {
    for (j=0; j<9; j++) {
        if (sud[i][j][0]) {
            strikeout(sud, i, j);
        }
    }
}


time_t t0 = time(0);

currentfield = findempty(sud, nullfield);

if (currentfield.i+1) {
    sol(sud, currentfield, counters);
}


time_t t1 = time(0);
double time_in_seconds = difftime(t1, t0);
printf("время %f\n", time_in_seconds);
printf("%d решений\n", counters[0]);
printf("oneleft сработала %d раз\n", counters[1]);
printf("oneinstr сработала %d раз\n", counters[2]);
printf("oneincol сработала %d раз\n", counters[3]);
printf("oneinsqr сработала %d раз\n", counters[4]);
printf("sol вызвана %d раз\n", counters[5]);
printf("findnum вызвана %d раз\n", counters[6]);

}