//
// Created by dsz on 23-8-4.
//

#include <chrono>
#include <ctime>
#include <iostream>

void getCurrentDateTime(int* year, int* month, int* day, int* hour, int* minute, int* second, int* millisecond) {
    // 获取当前时间
    auto now = std::chrono::system_clock::now();

    // 获取秒数
    auto seconds = std::chrono::time_point_cast<std::chrono::seconds>(now);
    auto epoch_seconds = seconds.time_since_epoch().count();

    // 获取毫秒数
    auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch());
    auto epoch_milliseconds = milliseconds.count();

    // 格式化日期和时间
    std::time_t time = static_cast<std::time_t>(epoch_seconds);
    std::tm* tm = std::localtime(&time);

    // 保存到参数中
    if (year) *year = tm->tm_year + 1900;  // tm_year是自1900年以来的年数
    if (month) *month = tm->tm_mon + 1;     // tm_mon是从0开始的月数
    if (day) *day = tm->tm_mday;
    if (hour) *hour = tm->tm_hour;
    if (minute) *minute = tm->tm_min;
    if (second) *second = tm->tm_sec;
    if (millisecond) *millisecond = epoch_milliseconds % 1000;  // 获取毫秒部分
}

int main() {
    int year, month, day, hour, minute, second, millisecond;
    getCurrentDateTime(&year, &month, &day, &hour, &minute, &second, &millisecond);
    std::cout << year << "-" << month << "-" << day << " "
              << hour << ":" << minute << ":" << second << "." << millisecond << std::endl;
    return 0;
}
