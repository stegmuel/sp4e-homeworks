import matplotlib.pyplot as plt
import pandas as pd
import argparse
import numpy as np
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
        default="/home/thomas/Documents/phd/MATH-611/sp4e-homeworks/homework2/test.csv",
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
    df = pd.read_csv(args.value_file, sep=separator, header=None, index_col=False)

    # Infer the output filename
    output_file = f'{".".join(args.value_file.split(".")[:-1])}.pdf'

    # Get the empirical values
    iteration = df.iloc[:, 0]
    empirical_prediction = df.iloc[:, 1]

    # Plot
    plt.plot(
        iteration,
        empirical_prediction,
        label="Empirical",
        linestyle="--",
        color="red",
        marker="o",
    )
    plt.xlabel(r"$k$", fontsize=16)
    plt.ylabel(r"$S_{n}$", fontsize=16)
    handles, labels = (
        plt.gca().get_legend_handles_labels()
    )  # Handles for the primary y-axis

    # Get the analytical values if available
    if df.shape[-1] == 3:
        analytical_prediction = df.iloc[:, 2]
        plt.plot(iteration, analytical_prediction, label="Analytical", color="blue")
        handles, labels = (
            plt.gca().get_legend_handles_labels()
        )  # Handles for the primary y-axis

        # Compute the error
        errors = np.abs(analytical_prediction - empirical_prediction)

        # Handle the case where the error is zero
        smallest_float = np.finfo(errors.dtype).tiny
        errors[errors == 0.0] = smallest_float

        # Create a second y-axis for the errors
        ax2 = plt.gca().twinx()
        ax2.plot(iteration, errors, label="Errors", color="green", linestyle="--")

        # Set the y-axis scale to logarithmic
        ax2.set_yscale("log")

        # Add a horizontal line at y = 1e-2
        ax2.axhline(y=1e-2, color="orange", linestyle=":", label="Tolerance (1e-2)")

        temp_handles, temp_labels = (
            ax2.get_legend_handles_labels()
        )  # Handles for the secondary y-axis
        handles += temp_handles
        labels += temp_labels

        # Set the label for the second y-axis
        ax2.set_ylabel("Errors", color="green", fontsize=16)

    # Set the labels and title for the primary y-axis
    plt.title("Empirical and analytical predictions with errors")

    # Create a single legend
    plt.legend(handles, labels)

    # Save the plot
    plt.savefig(output_file)


if __name__ == "__main__":
    parser = get_parser()
    args = parser.parse_args()
    plot(args)
