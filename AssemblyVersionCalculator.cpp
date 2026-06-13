// AssemblyVersionCalculator.cpp - Calculate assembly version by current time.
// Written by Xiaoxuan4096.

// This program is distributed under MIT License.
// See LICENSE.txt for details.

#include <iostream>
#include <string>
#include <limits>
#include <chrono>
#include <sstream>

size_t getBuild() {
    auto begin = std::chrono::sys_days{std::chrono::year{2000} / 1 / 1}; // Year 2000, Month 1, Day 1
    auto end = std::chrono::floor<std::chrono::days>(std::chrono::system_clock::now());
    return static_cast<size_t>((end - begin).count());
}
size_t getRevision() {
    auto begin = std::chrono::floor<std::chrono::days>(std::chrono::system_clock::now());
    auto end = std::chrono::system_clock::now();
    return std::chrono::duration_cast<std::chrono::seconds>(end - begin).count() / 2;
}

void pause() {
    std::cout << "Press Enter to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}

int main(){
    size_t major = 0, minor = 0;
    std::cout << "Assembly Version Calculator" << std::endl
              << "---------------------------" << std::endl;

    std::string input;
    std::cout << "Version (e.g. 1.2): " << std::endl
              << ">>> ";
    std::cin >> input;

    std::stringstream ss(input);
    char dot;
    if (!(ss >> major >> dot >> minor) || dot != '.' || ss >> dot) {
        std::cerr << "Invalid format. Use: Major.Minor" << std::endl;
        pause();
        return 1;
    }

    std::cout << major << '.' << minor << '.' << getBuild() << '.' << getRevision() << std::endl;
    pause();
    return 0;
}