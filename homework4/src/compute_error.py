import pandas as pd
import numpy as np
import argparse
import os

HEADERS = [
    "position_x",
    "position_y",
    "position_z",
    "velocity_x",
    "velocity_y",
    "velocity_z",
    "force_x",
    "force_y",
    "force_z",
    "mass",
    "name"
]

def get_parser():
    parser = argparse.ArgumentParser(description='Compute the prediction error in the trajectory predictions.')
    parser.add_argument('--dumps_dir', default="homework4/build/dumps/", type=str, help='specify the dumps directory.')
    parser.add_argument('--refs_dir', default="homework4/build/dumps/", type=str, help='specify the trajectories directory.')
    parser.add_argument('--planet_name', default="mercury", type=str, help='Name of the planet for which the trajectoriy must be verifies.')
    return parser


def readPositions(planet_name, directory):
    # Collect the input csv paths
    input_csvs = [os.path.join(directory, name) for name in sorted(os.listdir(directory))]

    # Read all csv as dataframes
    positions = []
    for input_csv in input_csvs:
        # Load the current csv
        current_df = pd.read_csv(input_csv, header=None, names=HEADERS, sep=r"\s{1,}", engine="python")

        # Select the specified planet
        current_df = current_df[current_df['name'] == planet_name]

        # Select the positions
        current_position = current_df[["position_x", "position_y", "position_z"]].values

        # Store
        positions.append(current_position)

    # Stack
    return np.concatenate(positions)


def computeError(positions, positions_ref):
    # Compute the squared difference
    error = (positions - positions_ref) ** 2

    # Sum and take the root
    return np.sqrt(error.sum())


def main(args):
    # Read the predicted positions for the specified planet
    positions_pred = readPositions(args.planet_name, args.dumps_dir)

    # Read the reference positions for the specified planet
    positions_ref = readPositions(args.planet_name, args.refs_dir)

    # Compute the errors
    error = computeError(positions_ref, positions_ref)
    print(error)


if __name__ == '__main__':
    # Parse the args
    parser = get_parser()
    args = parser.parse_args()

    # Call the main
    main(args)