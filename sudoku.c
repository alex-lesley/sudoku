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

void strikeout (char sud[9][9][10], int str, int col) {
    
    int i, j;
    char num=sud[str][col][0];
    //printf("запущена strikeout: поле %d, %d, значение %d \n", str, col, num);
    //printf("вычеркивание в строке %d \n", str);
    for (i=0; i<9; i++) {
        sud[str][i][num]=0;
    }
    //printf("вычеркивание в столбце %d \n", col);
    for (j=0; j<9; j++) {
        sud[j][col][num]=0;
    }
    //printf("вычеркивание в квадрате %d, %d \n", (int)str/3, (int)col/3);
    for (i=((int)str/3)*3; i<((int)str/3)*3+3; i++){
        for (j=((int)col/3)*3; j<((int)col/3)*3+3; j++){
            sud[i][j][num]=0;
        }
    }
}

struct field findempty(char sud[9][9][10], struct field startfield) {
    //printf("запущена findempty с поля %d, %d \n", startfield.i, startfield.j);
    int i, j;
    struct field newfield;
    newfield.i=-1;
    newfield.j=-1;
    for (j=startfield.j; j<9; j++) {
        if (!sud[startfield.i][j][0]) {
            newfield.i=startfield.i;
            newfield.j=j;
            //printf("найдено пустое поле в исходной строке %d, %d \n", newfield.i, newfield.j);
            return newfield;
        }
    }
    for (i=startfield.i+1; i<9; i++) {
        for (j=0; j<9; j++) {
            if (!sud[i][j][0]) {
                newfield.i=i;
                newfield.j=j;
                //printf("найдено пустое поле в другой строке %d, %d \n", newfield.i, newfield.j);
                return newfield;
            }
        }
    }
    //printf("не найдено пустого поля, возвращает %d, %d \n", newfield.i, newfield.j);
    return newfield;
}

char findnum(char sud[9][9][10], int i, int j) {
    int k, num=0;
    for (k=1; k<10; k++) {
        if (sud[i][j][k]) {
            num=k;
            sud[i][j][k]=0;
            return num;
        }
    }
}

void sol(char sud[9][9][10], struct field currentfield) {

    char newsud[9][9][10], tempsud[9][9][10];
    struct field newfield;
    char num;

    //printf("запущена sol с поля %d, %d \n", currentfield.i, currentfield.j);
    //printf("получен массив \n");
    //output(sud);
    //getchar();
    
    copy(sud, newsud);
    
    do {
        newsud[currentfield.i][currentfield.j][0]=findnum(newsud, currentfield.i, currentfield.j);
        if (newsud[currentfield.i][currentfield.j][0]) {
            //printf("подставленное значение %d \n", newsud[currentfield.i][currentfield.j][0]);
            copy(newsud, tempsud);
            strikeout(tempsud, currentfield.i, currentfield.j);
            newfield=findempty(tempsud, currentfield);
            if (newfield.i+1) {
                sol(tempsud, newfield);
            } else {
                printf("решение \n");
                output(tempsud);
                //getchar();
            }
        }
    } while(newsud[currentfield.i][currentfield.j][0]);
    //printf("воврат из sol, нет подстановок для поля %d, %d \n", currentfield.i, currentfield.j);
    return;
}

int main() {

    struct field currentfield, nullfield;
    nullfield.i=0;
    nullfield.j=0;
    
    int i,j,k;
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

//printf("разбиение строк:\n");

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

//printf("изначальное вычеркивание:\n");

for (i=0; i<9; i++) {
    for (j=0; j<9; j++) {
        if (sud[i][j][0]) {
            strikeout(sud, i, j);
        }
    }
}

//printf("поиск пустого поля:\n");
time_t t0 = time(0);

currentfield = findempty(sud, nullfield);

if (currentfield.i+1) {
    //printf("начальное поле входа %d, %d \n", currentfield.i, currentfield.j);
    sol(sud, currentfield);
}


/* some long calculation */
time_t t1 = time(0);
double time_in_seconds = difftime(t1, t0);
printf("время %f", time_in_seconds);

}