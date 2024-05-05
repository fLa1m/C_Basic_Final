#include <stdio.h>
#include "func.h"
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int MaxMonthTemperature(struct monthData *month, int monthNumber, int temperature)
{
    int maxT;
    if (month[monthNumber-1].countSense != 0)
    {
        maxT = month[monthNumber-1].maxTemperature;
    }
    else
    {
        maxT = -100;
    }
    if (temperature > maxT)
    {
        maxT = temperature;
    }
    return maxT;
}

int MinMonthTemperature(struct monthData *month, int monthNumber, int temperature)
{
    int minT;
    if (month[monthNumber-1].countSense != 0)
    {
        minT = month[monthNumber-1].minTemperature;
    }
    else
    {
        minT = 100;
    }
    if (temperature < minT)
    {
        minT = temperature;
    }
    return minT;
}

float AvgMonthTemperature(struct monthData *month, int monthNumber)
{
    long long signed int sumT = month[monthNumber-1].totalTemperature, count = month[monthNumber-1].countSense;
    float avgT = 0.0;
    avgT = sumT / (float)count;
    return avgT;
}

float AvgYearTemperature(struct monthData *month)
{
    float totalYearTemperature = 0.0;
    float avg = 0.0;
    for (int i = 1; i <= COUNT_MONTH; i++)
    {
        totalYearTemperature += AvgMonthTemperature(month, i);
    }
    avg = totalYearTemperature / COUNT_MONTH;
    return avg;
}

int MaxYearTemperature(struct monthData *month)
{
    int maxT = -1000;
    for (int i = 0; i < COUNT_MONTH; i++)
    {
        if (month[i].maxTemperature > maxT)
        {
            maxT = month[i].maxTemperature;
        }
    }
    return maxT;
}

int MinYearTemperature(struct monthData *month)
{
    int minT = 1000;
    for (int i = 0; i < COUNT_MONTH; i++)
    {
        if (month[i].minTemperature < minT)
        {
            minT = month[i].minTemperature;
        }
    }
    return minT;
}

int ScanKeys(int argc, char *argv[], char *fileName)
{
    int check = 0;
    int rez = 0;
    if (argc == 1)
    {
        printf("Error found! No such key exists. Try -h for help.\n");
    }
    while ((rez = getopt(argc, argv, "hf:m:")) != -1)
    {
        switch (rez)
        {
        case 'h':
            printf("Set of supported keys by the application:\n\
            -h Description of the application functionality. List of keys that handles the given application and their purpose.\n\
            -f <filename.csv> input csv file to process. Output statistics for the each month.\n\
            -m <month number> if this key is given, then output only statistics for the specified month. Type 0 to output statistics for the year.\n");
            break;
        case 'f': 
            strcpy(fileName, optarg);
            printf("Uploaded file: %s\n", fileName);
            check = 365;
            break;
        case 'm':
            check = atoi(optarg);
            break;
        }        
    }
    return check;   
}

int ScanData(struct monthData *month, FILE *open, char *name)
{
    open = fopen(name, "r");
    if (open == NULL)
    {
        return 1;
    }

    int Y, M, D, h, m, t;
    int result, counter = 0;
    while ((result = fscanf(open, "%d;%d;%d;%d;%d;%d", &Y, &M, &D, &h, &m, &t)) > 0)
    {
        counter++;
        if (result < N)
        {
            char s[21];
            result = fscanf(open, "%[^\n]", s);
            printf("ERROR in %d string = %s\n", counter, s);
        }
        else
        {
            month[M-1].info.year = Y;
            month[M-1].info.month = M;
            month[M-1].info.day = D;
            month[M-1].info.hour = h;
            month[M-1].info.min = m;
            month[M-1].info.temperature = t;
            month[M-1].maxTemperature = MaxMonthTemperature(month, M, t);
            month[M-1].minTemperature = MinMonthTemperature(month, M, t);
            month[M-1].totalTemperature += t;
            month[M-1].countSense++;
        }
    }
    fclose(open);
    return 0;
}

void PrintResult(struct monthData *month, int check, int data)
{
    if (check != 0 && check != 365 && data != 1)
    {
        printf("Data for the selected (%d) month.\n", check);
        printf("Average T = %0.2f, Min T = %d, Max T = %d\n", AvgMonthTemperature(month, check), month[check-1].minTemperature, month[check-1].maxTemperature);
    }
    else if (check == 365 && data != 1)
    {
        printf("Data for the each month\n");
        for (int i = 1; i <= COUNT_MONTH; i++)
        {
            printf("Month %d: Average = %0.2f, Min T = %d, Max T = %d\n", i, AvgMonthTemperature(month, i), month[i-1].minTemperature, month[i-1].maxTemperature);
        }
    }
    else if (check == 0 && data != 1)
    {
        printf("Data for the year.\n");
        printf("Average T = %0.2f, Min T = %d, Max T = %d\n", AvgYearTemperature(month), MinYearTemperature(month), MaxYearTemperature(month));
    }
       

}
