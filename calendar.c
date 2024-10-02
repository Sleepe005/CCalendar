#include <stdio.h>
#include <ncurses.h>
#include <locale.h>

// Globals variables
int cursePos = 0;
int maxCursePos = 8;

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
        if (i == cursePos){
            printw("  %s", "<--");
        }
        printw("\n");
    }
}

int GetYear(char strData[10]);

int GetMonth(char strData[10]);

int GetDay(char strData[10]);

bool visokosYear(char strData[10]){
    // int year;
    // if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0){
    //     return true;
    // }
    // else{
    //     return false;
    // }
}

int valDayInMonth(char strData[10]){
    bool vis = visokosYear(strData);

    // if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)
    // {
    //     return 31
    // }
    // else{
    //     if (month == 2){
    //         if (vis){
    //             return 29
    //         }
    //         else{
    //             return 28
    //         }
    //     }
    //     else{
    //         return 30
    //     }
    // }
}

int dataCoder(char strData[10]){
    int totalDays = 0;

    return totalDays;
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
        }

        clear();
    }

    return 0;
}