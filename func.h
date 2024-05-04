#include <stdio.h>
#define N 6
#define COUNT_MONTH 12

typedef struct data
{
    int year, month, day, hour, min, temperature;
} data;

typedef struct monthData
{
    struct data info;
    int maxTemperature;
    int minTemperature;
    long long signed int countSense;
    long long signed int totalTemperature;
} monthData;

int MaxMonthTemperature(struct monthData *month, int monthNumber, int temperature);

int MinMonthTemperature(struct monthData *month, int monthNumber, int temperature);

float AvgMonthTemperature(struct monthData *month, int monthNumber);

float AvgYearTemperature(struct monthData *month);

int MaxYearTemperature(struct monthData *month);

int MinYearTemperature(struct monthData *month);

int ScanKeys(int argc, char *argv[], char *fileName);

int ScanData(struct monthData *month, FILE *open, char *name);

void PrintResult(struct monthData *month, int check, int data);