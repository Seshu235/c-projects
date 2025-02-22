// Write a C program to implement date calculator

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    int days;
    int months;
    int years;
}date;

static const int DAYS_IN_MONTH[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

static inline bool isleapyear(short int year) {
    return (!(year % 4) && (!(year % 400) || (year % 100)));
}

static int getdaysinmonth(int month, int year) {
    return (month == 2 && isleapyear(year)? 29 : DAYS_IN_MONTH[month - 1]);
}

static bool isdatevalid(const date *ptr) {
    if (!ptr)  return false;

    bool ret = true;
    
    int days = getdaysinmonth(ptr->months, ptr->years);
    
    if (ptr->days < 1 || ptr->days > days) {
        printf("Invalid day: %d. Day must be between 1 and %d\n", ptr->days, days);
        ret = false;
    } else {
        /*  Nothing To Do   */
    }

    if (ptr->months < 1 || ptr->months > 12) {
        printf("Invalid month: %d. Month must be between 1 and 12\n", ptr->days);
        ret = false;
    } else {
        /*  Nothing To Do   */
    }
    
    if (ptr->years < 1900 || ptr->years > 2025) {
        printf("Invalid year: %d. Year must be between 1900 and 2025\n", ptr->days);
        ret = false;
    } else {
        /*  Nothing To Do   */
    }

    return ret;
}

static void calculate_age(date *ptr, const date *str) {
    time_t currenttime;

    currenttime = time(NULL);

    struct tm *ltime = localtime(&currenttime);

    char days = ltime->tm_mday - str->days;
    char months = (1 + ltime->tm_mon) - str->months;
    short int years = (1900 + ltime->tm_year) - str->years;

    if (days < 0) {
        months--;
        int prevmonth = ltime->tm_mon;
        if (prevmonth == 0) prevmonth = 12;
        days += getdaysinmonth(prevmonth, years);

    }

    if (months < 0)
    {
        years--;
        months += 12;
    }

    ptr->days = days;
    ptr->months = months;
    ptr->years = years;
}

int main() {
    date *v1 = malloc(sizeof(date));
    if (v1 == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    } else {
        /*  Nothing To Do   */
    }

    printf("Enter the Date in the order dd-mm-year\n");
    scanf("%d-%d-%d", &v1->days, &v1->months, &v1->years);
    
    if (!isdatevalid(v1)) {
        return -1;
    } else {
        /*  Nothing To Do   */
    }

    date *v2 = malloc(sizeof(date));
    if (v2 == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    } else {
        /*  Nothing To Do   */
    }

    calculate_age(v2, v1);

    printf("date differnce is %d years %.2d months %.2d days\n", v2->years, v2->months, v2->days);

    return 0;
}