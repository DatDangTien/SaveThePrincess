#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fstream>
#include <math.h>
#include "knight.h"

using namespace std;						

int readFile(const char* filename, knight& theKnight, int& nEvent, int* arrEvent)
{
    // This function is used to read the input file,
    // DO NOT MODIFY THIS FUNTION
    // Because you do not submit this main file.
    const char* file_name = filename;
    FILE* f = 0;
    char* str = new char[MAX_CHARACTER_EACH_LINE];
    int num;
    errno_t f;
    f = fopen_s(file_name);
    if (f == NULL)	//file not found || cannot read
        return 0;

    fgets(str, MAX_CHARACTER_EACH_LINE, f);
    if (feof(f))
        return 0;

    int start = 0;
    int len = strlen(str);

    // read HP
    while (start < len && str[start] == ' ')
        start ++;
    num = 0;
    while (start < len && str[start] <= '9' && str[start] >= '0'){
        num = num * 10 + str[start] - '0';
        start++;
    }
    theKnight.HP = num;
    if (theKnight.HP < 1 || theKnight.HP > 999)
        return 0;

    // read DF
    while (start < len && (str[start] > '9' || str[start] < '0'))
        start ++;
    num = 0;
    while (start < len && str[start] <= '9' && str[start] >= '0'){
        num = num * 10 + str[start] - '0';
        start++;
    }
    theKnight.DF = num;
    if (theKnight.DF < 1 || theKnight.DF > 20)
        return 0;

    // read level
    while (start < len && (str[start] > '9' || str[start] < '0'))
        start ++;
    num = 0;
    while (start < len && str[start] <= '9' && str[start] >= '0'){
        num = num * 10 + str[start] - '0';
        start++;
    }
    theKnight.level = num;
    if (theKnight.level < 1 || theKnight.level > 10)
        return 0;

    // read remedy
    while (start < len && (str[start] > '9' || str[start] < '0'))
        start ++;
    num = 0;
    while (start < len && str[start] <= '9' && str[start] >= '0'){
        num = num * 10 + str[start] - '0';
        start++;
    }
    theKnight.remedy = num;
    if (theKnight.remedy < 0 || theKnight.remedy > 99)
        return 0;

    // read gold
    while (start < len && (str[start] > '9' || str[start] < '0'))
        start ++;
    num = 0;
    while (start < len && str[start] <= '9' && str[start] >= '0'){
        num = num * 10 + str[start] - '0';
        start++;
    }
    theKnight.gold = num;
    if (theKnight.gold < 0 || theKnight.gold > 500)
        return 0;

    // read phoenixdown
    while (start < len && (str[start] > '9' || str[start] < '0'))
        start ++;
    num = 0;
    while (start < len && str[start] <= '9' && str[start] >= '0'){
        num = num * 10 + str[start] - '0';
        start++;
    }
    theKnight.phoenixdown = num;
    if (theKnight.phoenixdown < 0 || theKnight.phoenixdown > 99)
        return 0;

    // read events
    nEvent = 0;
    while (1){
        if (feof(f))
            break;
        fgets(str, MAX_CHARACTER_EACH_LINE, f);
        if (str == NULL)
            break;
        start = 0;
        len = strlen(str);
        while (start < len){
            while (start < len && (str[start] > '9' || str[start] < '0'))
                start++;
            if (start >= len)
                break;
            arrEvent[nEvent] = 0;
            while (start < len && str[start] <= '9' && str[start] >= '0'){
                arrEvent[nEvent] = arrEvent[nEvent] * 10 + str[start] - '0';
                start++;
            }
            nEvent++;
        }
        delete[] str;
    }

    fclose(f);
    return 1;
}

int main(int argc, char** argv)
{
    //You can change the value of filename to test your code
    const char* filename = "test/input_text.txt";

    struct knight theKnight;
    int nEvent; //number of events
    int* arrEvent = new int[EVENT_SIZE]; // array of events
    int result;                           // final result

    int check = readFile(filename, theKnight, nEvent, arrEvent);

    if (check == 1) {
        //Handle events
        result = startJourney(theKnight, nEvent, arrEvent);

        //result
        cout << result;
    }
    else {
        cout << "error";
    }
    return 0;
}
