//
// Created by 哲 on 2023/8/2.
//

#include <iostream>


typedef void (*callback_function)(int); // 函数指针类型，该类型的函数接受一个整数作为参数，并无返回值

void processNumbers(int* nums, int size, callback_function func) {
    for(int i = 0; i < size; i++) {
        func(nums[i]);
    }
}

void printNumber(int num) {
    std::cout << "The number is " << num << std::endl;
}

void squareNumber(int num) {
    std::cout << "The square of the number is " << num * num << std::endl;
}

int main() {
    int numbers[] = {1, 2, 3, 4, 5};
    std::cout << "Printing numbers:" << std::endl;
    processNumbers(numbers, 5, printNumber);
    std::cout << "Printing square of numbers" << std::endl;
    processNumbers(numbers, 5, squareNumber);

    return 0;
}
