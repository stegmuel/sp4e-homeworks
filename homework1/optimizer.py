import argparse
import numpy as np
import matplotlib.pyplot as plt

from numpy.typing import NDArray
from scipy.sparse.linalg import lgmres
from scipy.optimize import minimize
from typing import Callable, Tuple
from GMRES import gmres_
from utils import ResultsSaverCallback


def get_parser() -> argparse.Namespace:
    """
    Creates and returns an argument parser for the optimization methods.

    Returns:
        argparse.Namespace: A configured argument parser.
    """
    parser = argparse.ArgumentParser(description="Args parser for the optimization")
    parser.add_argument(
        "A",
        type=list[float],
        nargs="+",
        help="Provide matrix A, should be a square matrix. Ex: 12 23",
    )
    parser.add_argument(
        "b",
        type=list[float],
        help="Provide vector b, should be a vector of same size as A. Ex: 34",
    )
    parser.add_argument(
        "-m",
        "--method",
        type=str,
        choices=["lgmres2", "lgmres", "bfgs"],
        default="lgmres2",
        help="Method used to compute the minimizer.",
    )
    parser.add_argument(
        "--plot",
        action="store_true",
        help="Whether to plot the optimization steps or not. Matrix A and vector b should have dimension 2 !",
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
            return 0.5 * np.einsum(
                "m, m -> ", x, np.einsum("m n, n -> m ", matrix_a, x)
            ) - np.einsum("m, m ->", x, vector_b)
        elif x.ndim == 2:
            return 0.5 * np.einsum(
                "b m, b m -> b", x, np.einsum("m n, b n -> b m", matrix_a, x)
            ) - np.einsum("b m, m -> b", x, vector_b)
        elif x.ndim == 3:
            return 0.5 * np.einsum(
                "b c m, b c m -> b c", x, np.einsum("m n, b c n -> b c m", matrix_a, x)
            ) - np.einsum("b c m, m -> b c", x, vector_b)
        else:
            raise NotImplementedError

    return function


def get_minimizer(
    matrix_a: NDArray,
    vector_b: NDArray,
    method: str = "lgmres",
) -> Tuple[NDArray, ResultsSaverCallback]:
    """Solves linear equation Ax=b using a specified optimization method

    Args:
        matrix_a (NDArray): matrix A of dimension (n x n)
        vector_b (NDArray): vector b of dimension (n,)
        method (str, optional): optimization method used to solve the equation. Defaults to "lgmres".

    Raises:
        NotImplementedError: In case the method specified is not implemented by the function

    Returns:
        Tuple[NDArray, ResultsSaverCallback]: Returns the minimizer x and the intermediate steps.
    """

    # Initialize starting point
    x_zero = np.zeros_like(vector_b)

    # Initialize the callback
    callback = ResultsSaverCallback(x_zero)

    # Ensure matrix a and vector b are provided when the method is lgmres
    if method in {"lgmres", "lgmres2"}:
        assert (
            matrix_a is not None and vector_b is not None
        ), "Matrix a vector b can not be none when using lgmres."
        if method == "lgmres":
            return (
                lgmres(matrix_a, vector_b, x0=x_zero, callback=callback)[0],
                callback,
            )
        return gmres_(matrix_a, vector_b, x_zero, callback)

    elif method == "bfgs":
        function = get_function(matrix_a=matrix_a, vector_b=vector_b)
        return (
            minimize(fun=function, x0=x_zero, method="BFGS", callback=callback).x,
            callback,
        )

    else:
        raise NotImplementedError(f"Optimization method {method} not implemented !")


def plot_function(
    function: Callable[[NDArray], NDArray], callback: ResultsSaverCallback
) -> None:
    """Plot the function landscape and the intermediate optimization steps.

    Args:
        function (Callable[[NDArray], NDArray]): Functor to access the value of the objective at desired points.
        callback (ResultsSaverCallback): Object storing the intermediate optimization steps.
    """
    # Get the intermediate points from the callback
    intermediate_xs = callback.xs
    intermediate_xs = np.stack(intermediate_xs, axis=0)

    # Evaluate the points at the intermediate points
    intermediate_s_xs = function(intermediate_xs)

    # Set the grid
    xs = np.linspace(-3, 3, num=100)
    x_grid, y_grid = np.meshgrid(xs, xs)
    grid = np.stack([x_grid, y_grid], axis=-1)

    # Compute the value of the function at each point
    s_xs = function(grid)
    s_xs = s_xs.reshape(x_grid.shape)

    # Plot the surface
    fig = plt.figure()
    ax = fig.add_subplot(111, projection="3d")
    ax.view_init(elev=30.0, azim=135, roll=0)
    ax.plot_surface(x_grid, y_grid, s_xs, alpha=0.3, cmap="viridis")
    ax.contour3D(x_grid, y_grid, s_xs, 10, colors="black")
    ax.set_xlabel(r"$x_1$")
    ax.set_ylabel(r"$x_2$")
    ax.set_zlabel(r"$s(x_1,x_2)$")
    ax.plot(
        intermediate_xs[:, 0],
        intermediate_xs[:, 1],
        intermediate_s_xs,
        marker="o",
        c="red",
        linewidth=1,
        linestyle="dashed",
        markersize=4,
        alpha=1.0,
    )
    plt.show()


def main(args: argparse.Namespace) -> None:
    # Define the matrix a
    matrix_a = np.array(args.A, dtype=np.float32)

    # Define the vector b
    vector_b = np.array(args.b, dtype=np.float32)

    # Minimize the function
    minimizer, callback = get_minimizer(
        matrix_a=matrix_a, vector_b=vector_b, method=args.method
    )
    print(f"Solution x to Ax=b is: {minimizer}")

    # Get the function for plotting
    function = get_function(matrix_a=matrix_a, vector_b=vector_b)

    # Plot the function
    if args.plot:
        assert (
            len(vector_b) == 2
        ), "Matrix A and vector b should have dimension 2 for plotting. Considere removing --plot option."
        function = get_function(matrix_a=matrix_a, vector_b=vector_b)
        plot_function(function, callback)


if __name__ == "__main__":
    # Parse the arguments
    parser = get_parser()
    args = parser.parse_args()
    main(args)
