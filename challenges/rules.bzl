load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_test")

# Add a cpp file and a test_input file when you add a new challenge
# cpp file: name should be: day<X>, where X is the day of month, directory: //challenges
# example input: name should be: example_input<X> where X is the day of month, directory: //challenges/example_inputs
AVAILABLE_CHALLENGES = [1, 2, 3, 4]


def generate_challenges_targets():
    for day in AVAILABLE_CHALLENGES:
        native.filegroup(
            name = "input_files_{}".format(day),
            srcs = [
                ":example_inputs/example_input{}".format(day),
                ":inputs/input{}".format(day)
            ],
        )

        cc_binary(
            name = "day{}".format(day),
            srcs = ["day{}.cpp".format(day)],
            data = [":input_files_{}".format(day)],
            deps = ["@com_google_googletest//:gtest_main"],
        )

        cc_test(
            name = "day{}_test".format(day),
            size = "small",
            srcs = ["day{}.cpp".format(day)],
            data = [":input_files_{}".format(day)],
            deps = ["@com_google_googletest//:gtest_main"],
        )

    cc_binary(
        name = "main",
        srcs = ["main.cpp"] + ["day{}.cpp".format(day) for day in AVAILABLE_CHALLENGES],
        data = [":input_files_{}".format(day) for day in AVAILABLE_CHALLENGES],
        deps = ["@com_google_googletest//:gtest_main"],
    )



