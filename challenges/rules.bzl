load("@rules_cc//cc:defs.bzl", "cc_binary")

# Add a cpp file and a test_input file when you add a new challenge
# cpp file: name should be: day<X>, where X is the day of month, directory: //challenges
# test input: name should be: test_input<X> where X is the day of month, directory: //challenges/test_inputs
AVAILABLE_CHALLENGES = [1, 2]

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
            data = [":input_files_{}".format(day)]
        )
