import numpy as np
from scipy.sparse.linalg import lgmres
from scipy.optimize import minimize
import argparse
import matplotlib.pyplot as plt


def get_parser():
    parser = argparse.ArgumentParser(description="Args parser for GMRES")
    parser.add_argument(
        "--method",
        type=str,
        choices=["lgmres", "minimize"],
        default="minimize",
        help="Method used to compute the minimizer.",
    )
    return parser


def get_function(matrix_a, vector_b):
    def function(x):
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


def minimize_gmres(function=None, matrix_a=None, vector_b=None, method="lgmres"):
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

def main(args):
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


if __name__ == "__main__":
    # Parse the arguments
    parser = get_parser()
    args = parser.parse_args()
    main(args)
