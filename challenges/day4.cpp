#include <fstream>
#include <iostream>
#include <algorithm>
#include <map>
#include <vector>
#include <stdlib.h>
#include <cmath>
#include <gtest/gtest.h>
#include <queue>


std::pair<std::string, std::string> day4() {
    std::cout << "=========================================\n";
    std::cout << "Advent of Code - Day 4\n";
    std::cout << "=========================================\n";

//    std::ifstream input("challenges/example_inputs/example_input4");
    std::ifstream input("challenges/inputs/input4");

    std::string line;
    std::uint64_t sum1  = 0;
    std::uint64_t sum2  = 0;
    std::deque<std::uint64_t> tail(std::deque<std::uint64_t>(300));
    while (std::getline(input, line))
    {
        std::size_t const start_index = line.find(':') + 2;
        std::uint64_t num = 0;
        std::vector<std::uint64_t> winning_numbers{};
        std::vector<std::uint64_t> my_numbers{};
        std::vector<std::uint64_t>* num_ptr = &winning_numbers;
        for (std::uint64_t i = start_index; i < line.size(); i++) {
            if (line[i] == '|') {
                num_ptr = &my_numbers;
            }
            if (line[i] - '0' >= 0 && line[i] - '0' <= 9) {
                num *= 10;
                num += line[i] - '0';
            } else if (num > 0) {
                (*num_ptr).emplace_back(num);
                num = 0;
            }

            if (num > 0 && i == line.size()-1)
            {
                (*num_ptr).emplace_back(num);
            }

        }

        // First part
        std::uint64_t n_winning_nums = 0;
        for (auto const& my_num : my_numbers)
        {
            if (std::find(winning_numbers.begin(), winning_numbers.end(), my_num) != winning_numbers.end())
            {
                n_winning_nums++;
            }
        }
        if (n_winning_nums > 0)
        {
            sum1 += std::pow(2, n_winning_nums - 1);
        }

        // Secong part
        tail.at(0)++; // Add the original card
        for (std::size_t x = 1; x < n_winning_nums + 1; x++)
        {
            tail.at(x) += tail.at(0); // add the copies
        }
        sum2 += tail.front();
        tail.pop_front();
    }
    input.close();

    return std::make_pair(std::to_string(sum1), std::to_string(sum2));
}
// Known answers: 22488, 7013204

TEST(ResultTest, Day4Test)
{
    auto res = day4();
    EXPECT_EQ(res, std::make_pair(std::string{"22488"}, std::string{"7013204"}));
}
