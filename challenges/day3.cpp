#include <fstream>
#include <iostream>
#include <algorithm>
#include <map>
#include <vector>
#include <stdlib.h>
#include <gtest/gtest.h>

struct Number
{
    std::uint64_t value;
    std::vector<std::uint64_t> index;
};

bool check_for_symbol(std::vector<std::pair<std::uint64_t, std::uint64_t>> const& symbols_xy,
                      Number const& number_pos,
                      std::uint64_t line_nr)
{
    std::uint64_t min_index = *std::min_element(number_pos.index.begin(), number_pos.index.end());
    std::uint64_t max_index = *std::max_element(number_pos.index.begin(), number_pos.index.end());
    for (std::uint64_t x = (min_index > 0 ? min_index - 1 : min_index) ; x < max_index + 2; x++)
    {
        for (std::uint64_t y = (line_nr > 0 ? line_nr - 1: line_nr); y < line_nr + 2; y++)
        {
            if (std::find(symbols_xy.begin(), symbols_xy.end(), std::make_pair(x,y)) != symbols_xy.end())
            {
                return true;
            }
        }
    }
    return false;
}

std::uint64_t check_for_gear(std::pair<std::uint64_t, std::uint64_t> const& gear_xy,
                      std::vector<std::vector<Number>> const& schematics)
{
    std::uint64_t n_adj_numbers = 0;
    std::uint64_t gear_value = 1;
    for (std::uint64_t y = (gear_xy.second > 0 ? gear_xy.second - 1 : gear_xy.second); y < gear_xy.second + 2; y++)
    {
        for (auto const& numpos : schematics[y])
        {
            for (std::uint64_t const& x : numpos.index)
            {
                if (std::abs(static_cast<std::int64_t>(x-gear_xy.first)) < 2 && std::abs(static_cast<std::int64_t>(y-gear_xy.second)) < 2)
                {
                    n_adj_numbers++;
                    gear_value *= numpos.value;
                    break;
                }
            }
        }
    }
    if (n_adj_numbers == 2)
    {
        return gear_value;
    }
    return 0;
}


std::pair<std::string, std::string> day3() {
    std::cout << "=========================================\n";
    std::cout << "Advent of Code - Day 3\n";
    std::cout << "=========================================\n";

//    std::ifstream input("challenges/example_inputs/example_input3");
    std::ifstream input("challenges/inputs/input3");

    std::string line;
    std::uint64_t sum1  = 0;
    std::uint64_t sum2  = 0;
    std::vector<std::vector<Number>> engine_schematics = {};
    std::vector<std::pair<std::uint64_t , std::uint64_t>> symbols_xy{};
    std::vector<std::pair<std::uint64_t, std::uint64_t>> gear_xy{};
    std::uint64_t line_number = 0;
    while (std::getline(input, line))
    {
        std::uint64_t num = 0;
        std::vector<std::uint64_t> line_index{};
        std::vector<Number> numbers{};
        for (std::uint64_t i=0; i < line.size(); i++){
            if (line[i] - '0' >= 0 && line[i] - '0' <= 9)
            {
                num *= 10;
                num += line[i] - '0';
                line_index.push_back(i);
            }
            else if (num > 0)
            {
                numbers.emplace_back(Number{num, line_index});
                line_index.clear();
                num = 0;
            }

            if ((line[i] < '0' || line[i] > '9') && line[i] != '.')
            {
                symbols_xy.emplace_back(std::make_pair(i, line_number));
            }

            if (line[i] == '*')
            {
                gear_xy.emplace_back(std::make_pair(i, line_number));
            }

            if (i == line.size() - 1 && num > 0){
                numbers.emplace_back(Number{num, line_index});
            }

        }

        engine_schematics.push_back(numbers);
        line_number++;
    }
    input.close();

    // First part
    for (std::uint64_t line_nr = 0; line_nr < engine_schematics.size(); line_nr++)
    {
        for (Number const& numpos : engine_schematics[line_nr])
        {
            if (check_for_symbol(symbols_xy, numpos, line_nr))
            {
                sum1 += numpos.value;
            }
        }
    }

    // Second part
    for (auto const& xy : gear_xy)
    {
        std::uint64_t gear_value = check_for_gear(xy, engine_schematics);
        if (gear_value > 0)
        {
            sum2 += gear_value;
        }
    }

    return std::make_pair(std::to_string(sum1), std::to_string(sum2));
}
// Known answers: 544664, 84495585

TEST(ResultTest, Day3Test)
{
    auto res = day3();
    EXPECT_EQ(res, std::make_pair(std::string{"544664"}, std::string{"84495585"}));
}
