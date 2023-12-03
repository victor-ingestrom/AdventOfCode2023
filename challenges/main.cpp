
#include <functional>
#include <string>
#include <vector>
#include <iostream>

std::pair<std::string, std::string> day1();
std::pair<std::string, std::string> day2();
std::pair<std::string, std::string> day3();
std::pair<std::string, std::string> day4();

int main(int argc, char **argv)
{
    std::vector<std::function<std::pair<std::string,std::string>()>> days { day1, day2, day3, day4 };

    auto const day_input = std::strtol(argv[1], nullptr, 10);
    if (argc == 2 && day_input && day_input > 0 && day_input < days.size() + 1)
    {
        std::pair<std::string, std::string> result = days[day_input - 1]();
        std::cout << "Results: " << result.first << ", " << result.second << "\n";
    }
    else
    {
        std::cout << "Invalid argument\n";
    }

    return 0;
}