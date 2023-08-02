//
// Created by 哲 on 2023/7/7.
//

#include <iostream>
#include <string>

int main()
{
    std::string name;
    std::cout << "please input your name" << std::endl;
    std::cin >> name;
    std::cout << "Hello Wdeorld! " << name << std::endl;
    std::string previous = "";
    std::string current;
    while(std::cin>>current) {
        if(previous == current) {
            std::cout << "repeated word: " << current << std::endl;
        }
        previous = current;
    }
    return 0;
}