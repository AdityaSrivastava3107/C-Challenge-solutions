#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

typedef struct my_date_t {
    uint8_t date;
    uint8_t month;
    uint16_t year;
} my_date_t;

typedef enum status_t {
    SUCCESS,
    NULL_PTR,
    INCORRECT
} status_t;

status_t string_to_date_converter(char* input_string, my_date_t* result_date) {
    if (input_string == NULL || result_date == NULL) {
        return NULL_PTR;
    }

    int day, month, year;
    if (sscanf(input_string, "%d/%d/%d", &day, &month, &year) != 3) {
        return INCORRECT;
    }

    if (day < 1 || day > 31 || month < 1 || month > 12 || year < 0) {
        return INCORRECT;
    }

    result_date->date = (uint8_t)day;
    result_date->month = (uint8_t)month;
    result_date->year = (uint16_t)year;

    return SUCCESS;
}

void get_system_date(my_date_t* result_date) {
    if (result_date == NULL) {
        return;
    }

    time_t rawtime;
    struct tm* timeinfo;

    time(&rawtime);
    timeinfo = localtime(&rawtime);

    result_date->date = (uint8_t)timeinfo->tm_mday;
    result_date->month = (uint8_t)(timeinfo->tm_mon + 1);
    result_date->year = (uint16_t)(timeinfo->tm_year + 1900);
}

int main() {
    char input_string[] = "25/06/2023";
    my_date_t result_date;
    status_t conversion_status;

    conversion_status = string_to_date_converter(input_string, &result_date);

    if (conversion_status == SUCCESS) {
        printf("Conversion successful.\n");
        printf("Date: %02d\n", result_date.date);
        printf("Month: %02d\n", result_date.month);
        printf("Year: %04d\n", result_date.year);
    } else {
        printf("Conversion failed with status code %d\n", conversion_status);
    }

    printf("\n");

    get_system_date(&result_date);
    printf("System Date:\n");
    printf("Date: %02d\n", result_date.date);
    printf("Month: %02d\n", result_date.month);
    printf("Year: %04d\n", result_date.year);

    return 0;
}
