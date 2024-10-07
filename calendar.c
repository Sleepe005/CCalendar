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

long long int date1 = 0;

// Ввод второго времени
char strTime2[8];
bool hasStrTime2 = false;

// Ввод второй даты
char strDate2[10];
bool hasStrDate2 = false;

long long int date2 = 0;

// Ввод кол-ва дней
char addDays[5];
bool hasAddDays = false;

long long addDaysInSecond = 0;

// Ввод времени
char addTime[8];
bool hasAddTime = false;

long long int addTimeInSeconds = 0;

int startDate[3] = {1,1,1930};
int startTime[3] = {0,0,0};

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
    char substr[2];

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

bool visokosYear(int year){
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
    bool vis = visokosYear(year);

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

unsigned long long int codeDateTimeToSeconds(char strData[10], char strTime[8]){
    unsigned long long int totalSeconds = 0;
    int *date = dateStrParser(strData);
    int *time = timeStrParser(strTime);

    for(int i = startDate[2]; i < date[2]; ++i){
        if(visokosYear(i)){
            totalSeconds += 366;
        }else{
            totalSeconds += 365;
        }
    }

    for(int i = 1; i < date[1]; ++i){
        totalSeconds += (unsigned long long int)valDayInMonth(date[2], i);
    }

    totalSeconds += (unsigned long long int)(date[0] - 1);
    totalSeconds *= 86400;
    
    totalSeconds += (unsigned long long int)(time[0]*60*60+time[1]*60 + time[2]);

    return totalSeconds;
}

int *decodeDateTimeFromSeconds(unsigned long long int totalSeconds){
    
    int totalDays = 0, hours = 0, minutes = 0, seconds = 0;

    while(totalSeconds >= 86400){
        totalSeconds -= 86400;
        totalDays++;
    }

    while(totalSeconds >= 3600){
        totalSeconds -= 3600;
        hours++;
    }

    while(totalSeconds >= 60){
        totalSeconds -= 60;
        minutes++;
    }

    seconds = totalSeconds;

    // Second step: decode total days to year,month,day
    int year = startDate[2];
    int month = 1;
    int day = 1;

    day += totalDays;
    while(day > valDayInMonth(year, month)){
        day -= valDayInMonth(year, month);
        month += 1;
        if(month > 12){
            year += 1;
            month = 1;
        }
    }

    int DateTime[6] = {hours,minutes,seconds,day,month,year};
    return DateTime;
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