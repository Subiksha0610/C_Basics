#include <stdio.h>

static char daytab[2][13] = {
    {0,31,28,31,30,31,30,31,31,30,31,30,31},
    {0,31,29,31,30,31,30,31,31,30,31,30,31}
};

int day_of_year(int year, int month, int day) {
    int leap;

    if (year <= 0)
        return -1;

    leap = year%4 == 0 && year%100 != 0 || year%400 == 0;

    if (month < 1 || month > 12)
        return -1;

    if (day < 1 || day > daytab[leap][month])
        return -1;

    for (int i = 1; i < month; i++)
        day += daytab[leap][i];

    return day;
}

int month_day(int year, int yearday, int *pmonth, int *pday) {
    int leap, days_in_year, i;

    if (year <= 0 || pmonth == NULL || pday == NULL)
        return -1;

    leap = year%4 == 0 && year%100 != 0 || year%400 == 0;
    days_in_year = leap ? 366 : 365;

    if (yearday < 1 || yearday > days_in_year)
        return -1;

    for (i = 1; i <= 12 && yearday > daytab[leap][i]; i++)
        yearday -= daytab[leap][i];

    if (i > 12)
        return -1;

    *pmonth = i;
    *pday = yearday;

    return 0;
}

int main(void) {
    int year = 2024;
    int doy;
    int pmonth, pday;

    doy = day_of_year(year, 2, 29);
    printf("%d\n", doy);

    doy = day_of_year(2023, 2, 29);
    printf("%d\n", doy);

    printf("%d\n", month_day(year, 60, &pmonth, &pday));
    printf("%d %d\n", pmonth, pday);

    printf("%d\n", month_day(year, 400, &pmonth, &pday));

    printf("%d\n", day_of_year(-2024, 3, 10));

    return 0;
}
