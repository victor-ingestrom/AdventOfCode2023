#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

// Known answers: 54697, 54885

std::uint64_t update_digits(std::pair<std::size_t, std::uint64_t>& first_digit,
                   std::pair<std::size_t, std::uint64_t>& second_digit,
                   std::vector<std::string> const& values,
                   std::string const& line)
{
    for (std::size_t i=0; i < line.size(); i++)
    {
        for (std::size_t n=0; n < values.size(); n++)
        {
            if (line.substr(i, values[n].size()) == values[n]){
                if (i < first_digit.first){
                    first_digit.first = i;
                    first_digit.second = n + 1;
                }
                else if (i > second_digit.first){
                    second_digit.first = i;
                    second_digit.second = n + 1;
                }
            }
        }
    }
    if (second_digit.second == 0){
        second_digit = first_digit;
    }
    std::uint64_t calibration_value1 = first_digit.second * 10 + second_digit.second;

    return calibration_value1;
}

int main()
{
    std::cout << "=========================================\n";
    std::cout << "Advent of Code - Day 1\n";
    std::cout << "=========================================\n";

//    std::ifstream input("challenges/example_inputs/example_input1");
    std::ifstream input("challenges/inputs/input1");

    const std::vector<std::string> digit_num = {"1", "2", "3", "4", "5", "6", "7", "8", "9"};
    const std::vector<std::string> spelled_num = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};

    std::string line;
    std::uint64_t sum1  = 0;
    std::uint64_t sum2  = 0;
    while (std::getline(input, line))
    {
        // Pair with (index, value)
        std::pair<std::size_t, std::uint64_t> first_digit = std::make_pair(100, 0);
        std::pair<std::size_t, std::uint64_t> second_digit = std::make_pair(0, 0);

        // First part
        std::uint64_t calibration_value1 = update_digits(first_digit, second_digit, digit_num, line);
        sum1 += calibration_value1;

        // Second part
        std::uint64_t calibration_value2 = update_digits(first_digit, second_digit, spelled_num, line);
        sum2 += calibration_value2;
    }
    input.close();

    std::cout << "Part 1 - Sum of calibration values: " << sum1 << "\n";
    std::cout << "Part 2 - Sum of calibration values: " << sum2 << "\n";
}
