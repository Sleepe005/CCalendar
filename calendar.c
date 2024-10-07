#include <stdio.h>
#include <ncurses.h>
#include <locale.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

// Globals variables
int cursePos = 0;
int maxCursePos = 8;

// Воод 1-ого времени
char strTime1[8];
bool hasStrTime1 = false;

// Ввод 1-ой даты
char strDate1[10];
bool hasStrDate1 = false;

// Ввод второго времени
char strTime2[8];
bool hasStrTime2 = false;

// Ввод второй даты
char strDate2[10];
bool hasStrDate2 = false;

// Ввод кол-ва дней
char addDays[5];
bool hasAddDays = false;

// Ввод времени
char addTime[8];
bool hasAddTime = false;

int startDate[3] = {1,1,1930};

// Function for printing menu
void printMenu(){
    char menu[9][75] = {
        "1. Ввод 1-ого времени",
        "2. Ввод 1-ой даты",
        "3. Ввод 2-ого времени",
        "4. Ввод 2-ой даты",
        "5. Результат (большая дата - меньшая дата)",
        "6. Ввод кол-ва дней",
        "7. Результат (Дата (1) + Кол-во дней (6))",
        "8. Ввод времени",
        "9. Результат (Время (1) + Время (8))"
        };

    for(int i = 0; i < 9; ++i){
        printw("%s", menu[i]);
        if(hasStrTime1 && i == 0){
            printw(": %s", strTime1);
        }
        if(hasStrDate1 && i == 1){
            printw(": %s", strDate1);
        }
        if(hasStrTime2 && i == 2){
            printw(": %s", strTime2);
        }
        if(hasStrDate2 && i == 3){
            printw(": %s", strDate2);
        }
        if(hasAddDays && i == 5){
            printw(": %s", addDays);
        }
        if(hasAddTime && i == 7){
            printw(": %s", addTime);
        }
        if (i == cursePos){
            printw("  %s", "<--");
        }
        printw("\n");
    }
}

// Parse time in string format to array
int *timeStrParser(char strData[8]){ // 23:59:27
    static int valueTime[3] = {0,0,0};
    char substr[4];

    for(int i = 0, j = 0; i < 8, j < 3; i += 3, j++){
        strncpy(substr, strData+i, 2);
        valueTime[j] = atoi(substr);
    }

    return valueTime;
}

// Parse date in string format to array
int *dateStrParser(char strData[10]){ // 01.01.2020
    static int valueData[3] = {0,0,0};
    char substr[4];

    for(int i = 0, j = 0; i < 8, j < 3; i += 3, j++){
        if(j == 2){
            strncpy(substr, strData+i, 4);
        }else{
            strncpy(substr, strData+i, 2);
        }
        valueData[j] = atoi(substr);
    }

    return valueData;
}

// it could have been universal parser but i am stupid :(
// int Parser(char strData[10]){
//     static int resValues[3] = {0,0,0};
//     char substr[4] = "";
//     for(int i = 0, j = 0; i < strlen(strData), j < 3; i++){
//         if(isdigit(strData[i])){
//             strcpy(substr, strData[i]);
//         }else{
//             resValues[j] = atoi(substr);
//             strcpy(substr, "");
//             j++;
//         }
//     }
// }

// Get value from data arrya
// int GetYear(char strData[10]);
// int GetMonth(char strData[10]);
// int GetDay(char strData[10]);

bool visokosYear(int year){
    // int *date = dateStrParser(strDate);
    // int year =date[0];
    
    bool res;

    if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0){
        res = true;
    }
    else{
        res = false;
    }

    return res;
}

int valDayInMonth(int year, int month){
    // int *date = dateStrParser(strDate);
    bool vis = visokosYear(year);
    // int month = date[1];

    int res;

    if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)
    {
        res = 31;
    }
    else{
        if (month == 2){
            if (vis){
                res = 29;
            }
            else{
                res = 28;
            }
        }
        else{
            res = 30;
        }
    }

    return res;
}

int totalDays(char strData[10]){
    int totalDays = 0;
    int *date = dateStrParser(strData);

    for(int i = startDate[2]; i < date[2]; ++i){
        if(visokosYear(i)){
            totalDays += 366;
        }else{
            totalDays += 365;
        }
    }

    for(int i = 1; i < date[1]; ++i){
        totalDays += valDayInMonth(date[2], i);
    }

    totalDays += date[0] - 1;

    return totalDays;
}

void doSomething(int doing){
    switch (doing)
    {
    case 0:
        clear();
        printw("Введите первое время: ");
        scanw("%s", &strTime1);
        // TODO: Ввод
        hasStrTime1 = true;
        break;
    
    case 1:
        clear();
        printw("Введите первую дату время: ");
        scanw("%s", &strDate1);
        // TODO: Ввод
        hasStrDate1 = true;
        break;
    
    case 2:
        clear();
        printw("Введите второе время: ");
        scanw("%s", &strTime2);
        // TODO: Ввод
        hasStrTime2 = true;
        break;
    
    case 3:
        clear();
        printw("Введите вторую дату: ");
        scanw("%s", &strDate2);
        // TODO: Ввод
        hasStrDate2 = true;
        break;

    case 5:
        clear();
        printw("Введите кол-во дней: ");
        scanw("%s", &addDays);
        // TODO: Ввод
        hasAddDays = true;
        break;
    
    case 7:
        clear();
        printw("Введите время: ");
        scanw("%s", &addTime);
        // TODO: Ввод
        hasAddTime = true;
        break;

    default:
        break;
    }
}

int main(){
    setlocale(LC_ALL, "");
    initscr();

    int key;

    while(true){
        printMenu();

        key = getch();
        if(key == 27){
            key = getch();
            if(key == 91){
                key = getch();
                if(key == 65){
                    cursePos--;
                    if(cursePos < 0){
                        cursePos = maxCursePos;
                    }
                }
                if(key == 66){
                    cursePos++;
                    if(cursePos > maxCursePos){
                        cursePos = 0;
                    }
                }
            }
            if (key == 27){
                clear();
                printw("Всё");
                getch();
                break;
            }
        }else if(key == 10){
            doSomething(cursePos);
        }else if(key == 49){
            cursePos = 0;
            doSomething(cursePos);
            // int *testData = timeStrParser(strTime1);
        }else if(key == 50){
            cursePos = 1;
            doSomething(cursePos);
        }else if(key == 51){
            cursePos = 2;
            doSomething(cursePos);
        }else if(key == 52){
            cursePos = 3;
            doSomething(cursePos);
        }else if(key == 53){
            cursePos = 4;
        }else if(key == 54){
            cursePos = 5;
            doSomething(cursePos);
        }else if(key == 55){
            cursePos = 6;
        }else if(key == 56){
            cursePos = 7;
            doSomething(cursePos);
        }else if(key == 57){
            cursePos = 8;
        }

        clear();
    }

    return 0;
}