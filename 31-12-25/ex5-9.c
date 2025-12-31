#include <stdio.h>

static char daytab[2][13] = {
    {0,31,28,31,30,31,30,31,31,30,31,30,31},
    {0,31,29,31,30,31,30,31,31,30,31,30,31}
};

int day_of_year(int year, int month, int day) {
    int leap;
    char *p;

    if (year <= 0)
        return -1;

    leap = year%4 == 0 && year%100 != 0 || year%400 == 0;
    p = *(daytab + leap);

    if (month < 1 || month > 12)
        return -1;

    if (day < 1 || day > *(p + month))
        return -1;

    while (--month)
        day += *++p;

    return day;
}

int month_day(int year, int yearday, int *pmonth, int *pday) {
    int leap, days_in_year, i;
    char *p;

    if (year <= 0 || pmonth == NULL || pday == NULL)
        return -1;

    leap = year%4 == 0 && year%100 != 0 || year%400 == 0;
    days_in_year = leap ? 366 : 365;

    if (yearday < 1 || yearday > days_in_year)
        return -1;

    p = *(daytab + leap);
    i = 1;

    while (i <= 12 && yearday > *(p + i)) {
        yearday -= *(p + i);
        i++;
    }

    if (i > 12)
        return -1;

    *pmonth = i;
    *pday = yearday;

    return 0;
}

int main(void) {
    int year = 2024;
    int pmonth, pday;

    printf("%d\n", day_of_year(year, 2, 29));
    printf("%d\n", day_of_year(2023, 2, 29));

    printf("%d\n", month_day(year, 60, &pmonth, &pday));
    printf("%d %d\n", pmonth, pday);

    printf("%d\n", month_day(year, 400, &pmonth, &pday));
    printf("%d\n", day_of_year(-2024, 3, 10));

    return 0;
}
