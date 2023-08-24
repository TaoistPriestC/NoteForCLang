#include <stdio.h>
#include <string.h>

// 用于描述星期几
const char *daysOfWeek[] = {
    "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"
};

// 判断是否是闰年
int isLeapYear(int year) {
    return (year % 400 == 0) || (year % 4 == 0 && year % 100 != 0);
}

// 蔡勒公式，用于确定某一天是星期几
int Zeller(int year, int month, int day){
    int c = year / 100, y = year % 100, m = month, d = day;
    int w = (y + y / 4 + c / 4 - 2 * c + 2 * m + (3 * (m + 1) / 5) + d + 1) % 7;
    return w;
}


// 获取每个月的天数
int daysInMonth(int month, int year) {
    int days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (isLeapYear(year) && month == 2) {
        return 29;
    }
    return days[month - 1];
}

// 打印整年的日历, 格式是正确的，但是打印得到的逻辑是错误的
void printYearCalendar(int year) {
    for (int row = 0; row < 3; row++) {
        // 打印月份标题
        for (int month = 1 + row * 4; month <= 4 + row * 4; month++) {
            printf("         %3d/%4d          \t", month, year);
        }
        printf("\n");

        // 打印星期标题
        char dest[4];
        for (int i = 0; i < 4; i++){
            for (int j = 0; j < 7; j++) {
                strncpy(dest, daysOfWeek[j], 3);
                dest[3] = '\0';  // 确保字符串以 null 结尾
                printf("%3s ", dest);
            }
            printf("\t");  // 在月份之间添加制表符
        }
        printf("\n");

        // 打印每个月的日历
        for (int dayRow = 0; dayRow < 6; dayRow++) {
            for (int month = 1 + row * 4; month <= 4 + row * 4; month++) {
                int firstDayOfWeek = Zeller(year, month, 1);
                int daysOfMonth = daysInMonth(month, year);
                for (int dayCol = 0; dayCol < 7; dayCol++) {
                    int dayNum = dayRow * 7 + dayCol - firstDayOfWeek + 1;
                    if (dayNum > 0 && dayNum <= daysOfMonth) {
                        printf("%3d ", dayNum);
                    } else {
                        printf("    ");
                    }
                }
                printf("\t");  // 在月份之间添加制表符
            }
            printf("\n");
        }
    }
}

int main(int argc, char *argv[]) {
    int year, month, day;

    // 解析命令行参数
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--date") == 0 && i + 1 < argc) {
            if (sscanf(argv[i + 1], "%4d%2d%2d", &year, &month, &day) != 3) {
                printf("Invalid date format. Use YYYYMMDD.\n");
                return 1;
            }
            printf("The day %d-%d-%d is %s\n", year, month, day, daysOfWeek[Zeller(year, month, day)]);
            return 0;
        }

        if (strcmp(argv[i], "--year") == 0 && i + 1 < argc) {
            if (sscanf(argv[i + 1], "%4d", &year) != 1){
                printf("Invalid year format. Use YYYY(4 digits).\n");
                return 1;
            }
            printYearCalendar(year);
            return 0;
        }
    }
}