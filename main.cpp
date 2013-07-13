#include "Mathematics_Toolbox.h"

#include <iostream>
#include <list>
#include <chrono>
#include <limits>
#include <cmath>

using std::cout;
using std::endl;
using std::cin;

int main(){
    cout << "Mathematical Toolbox Test: \n";

    MTool::lli a, b, c;
    cout << "Enter in three integers, pressing ENTER after each one.\n";
    cin >> a >> b >> c;
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    cout << '\n';

    MTool::Precision_Int first(a), second(b), third(c);
    MTool::Precision_Int_String sfirst(a), ssecond(b), sthird(c);

    std::cout << "first: " << first.scientific_notation() << '\n';
    std::cout << "second: " << second.scientific_notation() << '\n';
    std::cout << "first+second: " << (first+second).scientific_notation() << '\n';
    std::cout << "first-second: " << (first-second).scientific_notation() << '\n';
    std::cout << "first*10000: " << (first*10000).scientific_notation() << '\n';
    std::cout << "first*second: " << (first*second).scientific_notation() << '\n';
    std::cout << "third: " << third.scientific_notation() << '\n';
    std::cout << "\n";
    std::cout << "first: " << sfirst.scientific_notation() << '\n';
    std::cout << "second: " << ssecond.scientific_notation() << '\n';
    std::cout << "first+second: " << (sfirst+ssecond).scientific_notation() << '\n';
    std::cout << "first-second: " << (sfirst-ssecond).scientific_notation() << '\n';
    std::cout << "first*10000: " << (sfirst*10000).scientific_notation() << '\n';
    std::cout << "first*second: " << (sfirst*ssecond).scientific_notation() << '\n';
    std::cout << "third: " << sthird.scientific_notation() << '\n';


    using Clock = std::chrono::high_resolution_clock;
    using std::chrono::nanoseconds;

    Clock::time_point low, high;
    std::pair<std::list<nanoseconds>, std::list<nanoseconds>>
        trial_data({},{});

    for(size_t trial(0); trial < 10; ++trial){

        low = Clock::now();

        for(size_t i(0); i < 1e6; ++i){
            (first+second);
            (first-second);
            (first*10000);
            (first*second);
        }

        high = Clock::now();
        trial_data.first.push_back(high-low);
        low = Clock::now();

        for(size_t i(0); i < 1e6; ++i){
            (first+second);
            (first-second);
            (first*10000);
            (first*second);
        }

        high = Clock::now();
        trial_data.second.push_back(high-low);
    }

    nanoseconds average1(0), average2(0);

    for(const auto& i : trial_data.first)
        average1 += i;
    average1 /= trial_data.first.size();
    for(const auto& i : trial_data.second)
        average2 += i;
    average2 /= trial_data.second.size();

    cout << "\n\nResults:\n"
        << "\tPrecision_Int took on average: " << average1.count() << " nanosecods.\n"
        << "\tPrecision_Int_String took on average: " << average2.count() << " nanosecods.\n"
        << "\tAnd the average difference is: " << std::abs(average1.count() - average2.count()) << " nanoseconds.\n"
    << '\n';

    cout << "Press ENTER to terminate the program.\n";
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    return 0;
}

