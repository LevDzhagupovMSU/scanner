#include <iostream>   
#include <string>     
#include <chrono>     
#include <cstdlib>   
#include <thread>
#include "thread_scan.hpp"

int main(){
    std::cout << "Enter Scan Frequency in Seconds" << std::endl << ">";
    std::string str_period;
    std::cin >> str_period;
    try{
        int int_seconds = std::stoi(str_period);
        auto seconds = std::chrono::seconds(int_seconds);

        scanner_dir sc;


        std::thread th([&](){
            sc.find_periodic(seconds);
        });

        sc.input();

        th.join();
        
    }catch(std::invalid_argument& e){
        throw e;
    }

    return 0;
}