import numpy as np
from scipy.sparse.linalg import lgmres
from scipy.optimize import minimize
import argparse
import matplotlib.pyplot as plt
from numpy.typing import NDArray
from typing import Callable, Optional, Tuple


class MyCallback:
    """
    Class to collect intermediate results during optimization.
    """

    def __init__(
        self,
    ):
        self.xs = []

    def __call__(self, x):
        self.xs.append(x)


def get_parser() -> argparse.Namespace:
    """
    Creates and returns an argument parser for the GMRES optimization methods.

    Returns:
        argparse.Namespace: A configured argument parser.
    """
    parser = argparse.ArgumentParser(description="Args parser for GMRES")
    parser.add_argument(
        "--method",
        type=str,
        choices=["lgmres", "minimize"],
        default="minimize",
        help="Method used to compute the minimizer.",
    )
    return parser


def get_function(matrix_a: NDArray, vector_b: NDArray) -> Callable[[NDArray], NDArray]:
    """
    Convenient way to get the optimization objective with A and b pre-set.
    Args:
        matrix_a (NDArray): A (m, m).
        vector_b (NDArray): b (m,).

    Returns:
        Callable[[NDArray], NDArray]: Functor to compute the value of the objective at query points.
    """

    def function(x: NDArray) -> NDArray:
        """
        Computes the optimization objective.
        Args:
            x (NDArray): Query point.

        Returns:
            NDArray: Value the objective at input point(s).
        """
        if x.ndim == 1:
            return np.einsum("m, m n, n -> ", x, matrix_a, x) - np.einsum(
                "m, m ->", x, vector_b
            )
        elif x.ndim == 2:
            return np.einsum("b m, m n, b n -> b", x, matrix_a, x) - np.einsum(
                "b m, m -> b", x, vector_b
            )
        elif x.ndim == 3:
            return np.einsum("b c m, m n, b c n -> b c", x, matrix_a, x) - np.einsum(
                "b c m, m -> b c", x, vector_b
            )
        else:
            raise NotImplementedError

    return function


def minimize_gmres(
    function: Optional[Callable[[NDArray], NDArray]] = None,
    matrix_a: Optional[NDArray] = None,
    vector_b: Optional[NDArray] = None,
    method: str = "lgmres",
) -> Tuple[NDArray, MyCallback]:
    # Initialize the callback
    callback = MyCallback()

    # Ensure matrix a and vector b are provided when the method is lgmres
    if method == "lgmres":
        assert (
            matrix_a is not None and vector_b is not None
        ), "Matrix a vector b can not be none when using lgmres."
        return lgmres(matrix_a, vector_b, callback=callback)

    # Get the function if not provided
    if function is None:
        assert (
            matrix_a is not None and vector_b is not None
        ), "Function and matrix a & vector b can not all be none."
        function = get_function(matrix_a=matrix_a, vector_b=vector_b)

    # Minimize
    return (
        minimize(
            fun=function, x0=np.array([5.0, 5.0]), method="BFGS", callback=callback
        )["x"],
        callback,
    )


def plot_function(function: Callable[[NDArray], NDArray], callback: MyCallback) -> None:
    """Plot the function landscape and the intermediate optimization steps.

    Args:
        function (Callable[[NDArray], NDArray]): Functor to access the value of the objective at desired points.
        callback (MyCallback): Object storing the intermediate optimization steps.
    """
    # Get the intermediate points from the callback
    intermediate_xs = callback.xs
    intermediate_xs = np.stack(intermediate_xs, axis=0)

    # Evaluate the points at the intermediate points
    intermediate_s_xs = function(intermediate_xs)

    # Set the grid
    xs = np.linspace(-3, 3, num=20)
    x_grid, y_grid = np.meshgrid(xs, xs)
    grid = np.stack([x_grid, y_grid], axis=-1)

    # Compute the value of the function at each point
    s_xs = function(grid)

    # Plot the surface
    fig = plt.figure()
    ax = fig.add_subplot(111, projection="3d")
    ax.plot_surface(x_grid, y_grid, s_xs, alpha=0.7)
    ax.scatter(
        intermediate_xs[:, 0], intermediate_xs[:, 1], intermediate_s_xs, "red", s=100
    )
    ax.plot(
        intermediate_xs[:, 0],
        intermediate_xs[:, 1],
        intermediate_s_xs,
        "red",
        linewidth=5,
    )
    plt.show()


def main(args: argparse.Namespace) -> None:
    # Define the matrix a
    matrix_a = np.array([[8, 1], [1, 3]], dtype=np.float32)

    # Define the vector b
    vector_b = np.array([2, 4], dtype=np.float32)

    # Get the function
    function = get_function(matrix_a=matrix_a, vector_b=vector_b)

    # Minimize the function
    minimizer, callback = minimize_gmres(
        matrix_a=matrix_a, vector_b=vector_b, method=args.method
    )

    # Plot the function
    plot_function(function, callback)


if __name__ == "__main__":
    # Parse the arguments
    parser = get_parser()
    args = parser.parse_args()
    main(args)
