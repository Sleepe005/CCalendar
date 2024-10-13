#include <stdio.h>
#include <ncurses.h>
#include <locale.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

// Globals variables
int cursePos = 0;
int maxCursePos = 8;

// Воод 1-ого времени
char strTime1[10] = "00:00:00";
bool hasStrTime1 = false;

// Ввод 1-ой даты
char strDate1[12] = "01.01.1930";
bool hasStrDate1 = false;

// Дата и время 1
unsigned long long int date1 = 0;

// Ввод второго времени
char strTime2[10] = "00:00:00";
bool hasStrTime2 = false;

// Ввод второй даты
char strDate2[12] = "01.01.1930";
bool hasStrDate2 = false;

// Дата и время 2
unsigned long long int date2 = 0;

// Ввод кол-ва дней
char addDays[5];
bool hasAddDays = false;

// Ввод времени
char addTime[9];
bool hasAddTime = false;
unsigned long long int addTimeSec = 0;

// Result 5
unsigned long long int totalSecondsRes5 = 0;
bool hasRes5 = false;
int res5[5];

// Default value
int startDate[3] = {1,1,1930};
int startTime[3] = {0,0,0};

// Parse data
void Split(char data[12], int *value){
    char element[5] = "";
    int pos = 0;
    int j = 0;
    for(int i = 0; i < strlen(data); ++i){
        if(ispunct(data[i])){
            value[j] = atoi(element);
            j++;
            strcpy(element, "");
            pos = 0;
        }else{
            element[pos] = data[i];
            pos++;
        }
    }
    value[j] = atoi(element);
}

// Function witch define visokos year
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

// Fuction witch cout day in month
int valDayInMonth(int year, int month){
    bool vis = visokosYear(year);

    int res;
    month%=12;

    if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 0)
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

// Coder for date in seconds
unsigned long long int codeDateTimeToSeconds(char strData[12], char strTime[10]){
    unsigned long long int totalSeconds = 0;

    int date[3] = {0,0,0};
    Split(strData, date);

    int time[3] = {0,0,0};
    Split(strTime, time);

    for(int i = startDate[2]; i < date[2]; ++i){
        if(visokosYear(i)){
            totalSeconds += 366*86400;
        }else{
            totalSeconds += 365*86400;
        }
    }

    for(int i = 1; i < date[1]; ++i){
        totalSeconds += (unsigned long long int)(valDayInMonth(date[2], i)*86400);
    }

    totalSeconds += (unsigned long long int)((date[0] - 1)*86400);
    
    totalSeconds += (unsigned long long int)(time[0]*60*60+time[1]*60 + time[2]);

    return totalSeconds;
}

// Decoder seconds to the date
int decodeDateTimeFromSeconds(unsigned long long int totalSeconds, int *dateTime, int startDate[3]){
    
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

    dateTime[0] = hours;
    dateTime[1] = minutes;
    dateTime[2] = seconds;

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

    dateTime[3] = year;
    dateTime[4] = month;
    dateTime[5]=  day;

    return totalDays;
}

// Check input format
bool isSample(char strData[12]){
    bool allDigIsDig = true;
    bool hasSep = true; // __.__.____/__:__:__
    for(int i = 0; i < strlen(strData); ++i){
        if(i == 2 || i == 5){
            if(!ispunct(strData[i])){
                hasSep = false;
            }
        }else if(!isdigit(strData[i]))
            allDigIsDig = false;
        }
    return allDigIsDig && hasSep;
}

// Do something
void doSomething(int doing){
    switch (doing)
    {
    case 0:
        clear();
        printw("Введите первое время (ЧЧ:ММ:СС): ");
        scanw("%s", strTime1);

        hasStrTime1 = true;
        if(!isSample(strTime1)){
            strcpy(strTime1, "");
            hasStrTime1 = false;
            printf("\nНеверный формат времени :(\n");
            printf("\nНажмите любую клавишу для выхода в меню :(\n");
            getch();
        }else{
            date1 += codeDateTimeToSeconds("01.01.1930", strTime1);
        }

        break;
    
    case 1:
        clear();
        printw("Введите первую дату (ДД:ММ:ГГГГ): ");
        scanw("%s", strDate1);
        
        hasStrDate1 = true;
        if(!isSample(strDate1)){
            strcpy(strDate1, "");
            hasStrDate1 = false;
            printf("\nНеверный формат даты :(\n");
            printf("\nНажмите любую клавишу для выхода в меню :(\n");
            getch();
        }else{
            date1 += codeDateTimeToSeconds(strDate1, "00:00:00");
        }

        break;
    
    case 2:
        clear();
        printw("Введите второе время (ЧЧ:ММ:СС): ");
        scanw("%s", strTime2);

        hasStrTime2 = true;
        if(!isSample(strTime2)){
            strcpy(strTime2, "");
            hasStrTime2 = false;
            printf("\nНеверный формат времени :(\n");
            printf("\nНажмите любую клавишу для выхода в меню :(\n");
            getch();
        }else{
            date2 += codeDateTimeToSeconds("01.01.1930", strTime2);
        }

        break;
    
    case 3:
        clear();
        printw("Введите вторую дату (ДД:ММ:ГГГГ): ");
        scanw("%s", strDate2);

        hasStrDate2 = true;
        if(!isSample(strDate2)){
            strcpy(strDate2, "");
            hasStrDate2 = false;
            printf("\nНеверный формат даты :(\n");
            printf("\nНажмите любую клавишу для выхода в меню :(\n");
            getch();
        }else{
            date1 += codeDateTimeToSeconds(strDate2, "00:00:00");
        }
        break;
    
    case 4:
        clear();
        if(hasStrDate1 && hasStrTime1 && hasStrDate2 && hasStrTime2){
            unsigned long long int totalSeconds1 = codeDateTimeToSeconds(strDate1, strTime1);
            unsigned long long int totalSeconds2 = codeDateTimeToSeconds(strDate2, strTime2);

            int totalDays = 0;
            int dateTime[6] = {0,0,0,0,0,0};
            if(totalSeconds1 > totalSeconds2){
                unsigned long long int difSeconds = totalSeconds1 - totalSeconds2;
                totalDays = decodeDateTimeFromSeconds(difSeconds, dateTime, strDate2);
            }else{
                unsigned long long int difSecons = totalSeconds2 - totalSeconds1;
                totalDays = decodeDateTimeFromSeconds(difSecons, dateTime, strDate1);
            }

            printw("%s %s\n", strDate1, strTime1);
            printw("%s %s\n", strDate2, strTime2);
            printw("Между датами %d дней %d часов %d минут %d секунд\n", totalDays, dateTime[0], dateTime[1], dateTime[2]);
            
        }else{
            printw("Некоторые данные не были введены\n");
        }

        printw("\nДля выхода в меню нажмите на любую клавишу :)\n");
        getch();
        break;

    case 5:
        clear();
        printw("Введите кол-во дней: ");
        scanw("%s", &addDays);
        hasAddDays = true;
        for(int i = 0; i < strlen(addDays); ++i){
            if(!isdigit(addDays[i])){
                hasAddDays = false;
            }
        }
        if(!hasAddDays){
            printf("\nНеверный формат :(\n");
            printf("\nНажмите любую клавишу для выхода в меню :(\n");
            getch();
        }
        break;
    
    case 6:
        clear();
        if(hasAddDays && hasStrDate1){
            unsigned long long int totalSec1 = codeDateTimeToSeconds(strDate1, strTime1);
            unsigned long long int totalSecAdd = atoi(addDays)*24*3600;

            int dateTimeAdd[6] = {0,0,0,0,0,0};
            unsigned long long int totalSecRes = totalSec1 + totalSecAdd;
            decodeDateTimeFromSeconds(totalSecRes, dateTimeAdd, startDate);

            int d1[6]  = {0,0,0,0,0,0};
            decodeDateTimeFromSeconds(totalSec1, d1, startDate);

            printw("Первая дата: %02d.%02d.%d\n", d1[5], d1[4], d1[3]);
            printw("Новая дата: %02d.%02d.%d\n", dateTimeAdd[5], dateTimeAdd[4], dateTimeAdd[3]);
        }else{
            printw("Некоторые данные не были введены\n");
        }

        printw("\nДля выхода в меню нажмите на любую клавишу :)\n");
        getch();
        break;
    
    case 7:
        clear();
        printw("Введите время (ЧЧ:ММ:СС): ");
        scanw("%s", &addTime);

        hasAddTime = true;
        if(!isSample(addTime)){
            strcpy(addTime, "");
            hasAddTime = false;
            printf("\nНеверный формат времени :(\n");
            printf("\nНажмите любую клавишу для выхода в меню :(\n");
            getch();
        }else{
            addTimeSec += codeDateTimeToSeconds("01.01.1930", addTime);
        }

        break;
    
    case 8:
        clear();
        if(hasAddTime && hasStrTime1){
            unsigned long long int totalSec1 = codeDateTimeToSeconds("01.01.1930", strTime1);
            unsigned long long int totalSecAdd = codeDateTimeToSeconds("01.01.1930", addTime);

            int dateTimeAdd[6];
            unsigned long long int totalSecRes = totalSec1 + totalSecAdd;
            decodeDateTimeFromSeconds(totalSecRes, dateTimeAdd, startDate);

            int time1[6] = {0,0,0,0,0,0};
            decodeDateTimeFromSeconds(totalSec1, time1, startDate);

            printw("Первое время: %02d:%02d:%02d\n", time1[0], time1[1], time1[2]);
            printw("Новое время: %02d:%02d:%02d\n", dateTimeAdd[0], dateTimeAdd[1], dateTimeAdd[2]);
        }else{
            printw("Некоторые данные не были введены\n");
        }

        printw("\nДля выхода в меню нажмите на любую клавишу :)\n");
        getch();
        break;

    default:
        break;
    }
}

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

    int valDate1[6] = {0,0,0,0,0,0};
    decodeDateTimeFromSeconds(date1, valDate1, startDate);

    int valDate2[6] = {0,0,0,0,0,0};
    decodeDateTimeFromSeconds(date2, valDate2, startDate);

    for(int i = 0; i < 9; ++i){
        printw("%s", menu[i]);
        if(hasStrTime1 && i == 0){
            printw(": %02d:%02d:%02d", valDate1[0], valDate1[1], valDate1[2]);
        }
        if(hasStrDate1 && i == 1){
            printw(": %02d.%02d.%d", valDate1[5], valDate1[4], valDate1[3]);
        }
        if(hasStrTime2 && i == 2){
            printw(": %02d:%02d:%02d", valDate2[0], valDate2[1], valDate2[2]);
        }
        if(hasStrDate2 && i == 3){
            printw(": %02d.%02d.%d", valDate2[5], valDate2[4], valDate2[3]);
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
            doSomething(cursePos);
        }else if(key == 54){
            cursePos = 5;
            doSomething(cursePos);
        }else if(key == 55){
            cursePos = 6;
            doSomething(cursePos);
        }else if(key == 56){
            cursePos = 7;
            doSomething(cursePos);
        }else if(key == 57){
            cursePos = 8;
            doSomething(8);
        }

        clear();
    }

    return 0;
}