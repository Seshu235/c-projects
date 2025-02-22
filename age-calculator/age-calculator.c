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

int current_year;

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
    }

    if (ptr->months < 1 || ptr->months > 12) {
        printf("Invalid month: %d. Month must be between 1 and 12\n", ptr->days);
        ret = false;
    }
    
    if (ptr->years < 1900 || ptr->years > current_year) {
        printf("Invalid year: %d. Year must be between 1900 and %d\n", ptr->days, current_year);
        ret = false;
    }

    return ret;
}

static void calculate_age(date *age, const date *today, const date *birth) {
    age->days = today->days - birth->days;
    age->months = today->months - birth->months;
    age->years = today->years - birth->years;

    if (age->days < 0) {
        age->months--;
        int prevmonth = today->months - 1;
        if (prevmonth == 0) prevmonth = 12;
        age->days += getdaysinmonth(prevmonth, today->years);

    }

    if (age->months < 0)
    {
        age->years--;
        age->months += 12;
    }
}

int main() {
    date *birthdate = malloc(sizeof(date));
    date *today = malloc(sizeof(date));
    date *age = malloc(sizeof(date));

    time_t currenttime;

    currenttime = time(NULL);

    struct tm *ltime = localtime(&currenttime);

    today->days = ltime->tm_mday;
    today->months = 1 + ltime->tm_mon;
    today->years = 1900 + ltime->tm_year;

    current_year = today->years;

    printf("Enter the Date in the order dd-mm-year\n");
    scanf("%d-%d-%d", &birthdate->days, &birthdate->months, &birthdate->years);
    
    if (!isdatevalid(birthdate)) {
        return -1;
    } else {
        /*  Nothing To Do   */
    }

    calculate_age(age, today, birthdate);

    printf("date differnce is %d years %.2d months %.2d days\n", age->years, age->months, age->days);

    return 0;
}