#include <fstream>
#include <iostream>
#include <algorithm>
#include <map>
#include <gtest/gtest.h>

constexpr std::uint64_t RED_CUBE_POOL = 12;
constexpr std::uint64_t GREEN_CUBE_POOL = 13;
constexpr std::uint64_t BLUE_CUBE_POOL = 14;

std::pair<std::string, std::string> day2()
{
    std::cout << "=========================================\n";
    std::cout << "Advent of Code - Day 2\n";
    std::cout << "=========================================\n";

//    std::ifstream input("challenges/example_inputs/example_input2");
    std::ifstream input("challenges/inputs/input2");

    std::string line;
    std::uint64_t sum1  = 0;
    std::uint64_t sum2  = 0;
    while (std::getline(input, line))
    {
        const std::uint64_t game_id = std::stoi(line.substr(5, line.find(':')-5));
        std::map<char, std::uint64_t> cubes = {
                {'r', 0},
                {'g', 0},
                {'b', 0}
        };
        bool read_num = false;
        std::uint64_t num = 0;
        for (char const& ch : line.substr(6, line.size()-6))
        {
            if (read_num)
            {
                if (ch - '0' >= 0 && ch - '0' <= 9)
                {
                    num *= 10;
                    num += ch - '0';
                }
                else{
                    for (auto& color : cubes){
                        if (ch == color.first){
                            if (num > color.second){
                                color.second = num;
                            }
                            num = 0;
                            read_num = false;
                        }
                    }
                }
            }
            if (ch == ' ' && !read_num)
            {
                read_num = true;
            }
        }

        // First part
        if (cubes['r']  <= RED_CUBE_POOL && cubes['g'] <= GREEN_CUBE_POOL && cubes['b'] <= BLUE_CUBE_POOL)
        {
            sum1 += game_id;
        }

        // Second part
        std::uint64_t power = cubes['r'] * cubes['g'] * cubes['b'];
        sum2 += power;
    }
    input.close();

    return std::make_pair(std::to_string(sum1), std::to_string(sum2));
}
// Known answers: 2239, 83435

TEST(ResultTest, Day2Test)
{
    auto res = day2();
    EXPECT_EQ(res, std::make_pair(std::string{"2239"}, std::string{"83435"}));
}
