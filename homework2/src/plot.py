import matplotlib.pyplot as plt
import pandas as pd
import argparse
import os


def get_parser() -> argparse.Namespace:
    """
    Creates and returns an argument parser to plot the values stored in a file.

    Returns:
        argparse.Namespace: A configured argument parser.
    """
    parser = argparse.ArgumentParser(description="Args parser for the optimization")
    parser.add_argument(
        "--value_file",
        default="/home/thomas/Documents/phd/MATH-611/sp4e-homeworks/homework2/src/test.csv",
        type=str,
        help="Path to the file.",
    )
    parser.add_argument(
        "--maxiter",
        default=100,
        type=int,
        help="Maximum number of iterations.",
    )
    parser.add_argument(
        "--print_frequency",
        default=10,
        type=int,
        help="Frequency of the prints.",
    )
    return parser


def plot(args):
    # Infer separator based on file extension
    separator = " "
    if args.value_file.endswith(".txt"):
        separator = " "
    elif args.value_file.endswith(".csv"):
        separator = ","
    elif args.value_file.endswith(".psv"):
        separator = "|"
    else:
        raise ValueError("Unsupported file extension. Use .txt, .csv, or .psv")

    # Load the file with the inferred separator
    df = pd.read_csv(args.value_file, sep=separator, header=None)

    # Plot
    raise NotImplementedError
    

if __name__ == '__main__':
    parser = get_parser()
    args = parser.parse_args()
    plot(args)