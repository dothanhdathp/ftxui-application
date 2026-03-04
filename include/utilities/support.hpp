#include "stdio.h"
#include <algorithm>
#include <iostream>
#include <chrono>
#include <fstream>
#include <string>
#include <bitset>
#include <vector>

#define plog(mnt, ...) printf("%s:%d: "#mnt"\n", __FILE__, __LINE__, ##__VA_ARGS__);

#define time_stamp(f) auto f = std::chrono::high_resolution_clock::now()

#define time_as_milliseconds(time_start, time_end) std::cout << "Milliseconds: " << std::chrono::duration_cast<std::chrono::milliseconds>(time_end - time_start).count() << " (ms)" << std::endl;
#define time_as_microseconds(time_start, time_end) std::cout << "Microseconds: " << std::chrono::duration_cast<std::chrono::microseconds>(time_end - time_start).count() << " (µs)" << std::endl;
#define time_as_seconds(time_start, time_end) std::cout << "Seconds:      " << std::chrono::duration<double>(time_end - time_start).count() << " (s)" << std::endl;

template<typename T>
std::vector<T> get_input_vector()
{
    std::vector<T> ans;
    T size_of_array;
    std::cin >> size_of_array;
    while(size_of_array--) {
        T var;
        std::cin >> var;
        ans.push_back(var);
    }
    return ans;
}

template<typename T>
void printf_vector(std::vector<T> &vec, const char* mnt)
{
    for(T var : vec) {
        printf(mnt, var);
    }
    printf("\n");
}

template<typename T>
void printf_2d_vector(std::vector<std::vector<T>> &vec, const char* mnt)
{
    for(auto V : vec) {
        for(T var : V) {
            printf(mnt, var);
        }
        printf("\n");
    }
    printf("\n");
}

#define debug(...) debug_print_value(__LINE__, #__VA_ARGS__, __VA_ARGS__)
template <typename... Args>
void debug_print_value(size_t line_number, std::string names, Args... args) {
    size_t pos = 0;
    std::cout << "[ line " << line_number << " ] ";
    // Fold expression that handles the name parsing and printing
    ([&](auto& val) {
        size_t next_comma = names.find(',', pos);
        std::string name = names.substr(pos, next_comma - pos);
        std::cout << name << " = " << val << "; ";
        pos = next_comma + 1;
        // Skip space after comma if it exists
        if (pos < names.size() && names[pos] == ' ') pos++;
    }(args), ...);
    std::cout << std::endl;
}