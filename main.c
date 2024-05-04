#include <stdio.h>
#include "func.h"
#include <unistd.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    char fileName[256];
    struct monthData month[COUNT_MONTH] = {0};
    int data;
    int check;
    FILE *open;

    check = ScanKeys(argc, argv, fileName);

    data = ScanData(month, open, fileName);

    PrintResult(month, check, data);
}
