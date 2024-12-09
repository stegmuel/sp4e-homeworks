import numpy as np
import argparse


def get_parser():
    parser = argparse.ArgumentParser()
    parser.add_argument(
        "--savepath",
        default="homework3/data/radial_heat_distribution.csv",
        type=str,
        help="Where to save the generated .csv file",
    )
    parser.add_argument("--n_points_per_side", default=11, type=float)
    parser.add_argument("--radius", default=0.1, type=float)
    parser.add_argument("--x_min", default=-1.0, type=float)
    parser.add_argument("--x_max", default=1.0, type=float)
    parser.add_argument("--y_min", default=-1.0, type=float)
    parser.add_argument("--y_max", default=1.0, type=float)
    return parser


def main(args):
    # Initialize the positions
    x = np.linspace(start=args.x_min, stop=args.x_max, num=args.n_points_per_side)
    y = np.linspace(start=args.y_max, stop=args.y_min, num=args.n_points_per_side)
    xv, yv = np.meshgrid(x, y, indexing="xy")

    # Compute the squared distance from the center
    distance_from_center = xv**2 + yv**2

    # Compute the heat rate at each position
    heat_rate = np.zeros((args.n_points_per_side, args.n_points_per_side))
    heat_rate[distance_from_center < args.radius] = 1
    heat_rate = heat_rate.flatten()[:, None]

    # Add z component to the positions and flatten
    zv = np.zeros_like(xv)
    position = np.stack([xv, yv, zv], axis=-1).reshape(-1, 3)
    velocity = np.zeros_like(position)
    force = np.zeros_like(position)
    mass = np.ones_like(position[:, :1])
    temperature = np.zeros_like(mass)

    # Create boundary conditions and flatten
    boundary = np.zeros_like(xv)
    boundary[:, 0] = 1.
    boundary[:, -1] = 1.
    boundary[0, :] = 1.
    boundary[-1, :] = 1.
    boundary = boundary.reshape(-1, 1)

    # Stack everything to obtain rows
    rows = np.concatenate(
        [position, velocity, force, mass, temperature, heat_rate, boundary], axis=-1
    )

    # Save as CSV
    np.savetxt(args.savepath, rows, delimiter=",", fmt="%f")


if __name__ == "__main__":
    # Get the args
    parser = get_parser()
    args = parser.parse_args()
    main(args)
