import argparse
from numpy.linalg import norm
import numpy as np
from scipy.linalg import lstsq


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


def arnoldi_iteration(matrix_a, matrix_q, matrix_h, i):
    # Arnoldi process to build the orthonormal basis V and Hessenberg matrix H
    q_k = np.einsum("m n, n -> m", matrix_a, matrix_q[:, i])
    for j in range(i+1):
        matrix_h[j, i] = np.einsum("m, m ->", matrix_q[:, j].conj(), q_k)
        q_k = q_k - matrix_h[j, i] * matrix_q[:, j]
    
    matrix_h[i+1, i] = norm(q_k)
    matrix_q[:, i+1] = q_k / matrix_h[i+1, i]
    return matrix_h, matrix_q


def gmres_(matrix_a, vector_b, tol=1e-15, max_iters=100):
    # The matrix A is assumed to be invertible
    assert (
        matrix_a.shape[0] == matrix_a.shape[1] and matrix_a.ndim == 2
    ), "A square matrix is expected."
    assert np.linalg.det(matrix_a) != 0, "The matrix is expected to be invertible."

    # Set default values
    n = len(vector_b)
    x_zero = np.random.randn(matrix_a.shape[1])

    # Normalize the right-hand side vector
    b_norm = norm(vector_b)

    # Initialize variables
    x = x_zero
    residual = vector_b - np.einsum("m n, n -> m", matrix_a, x)

    beta = norm(residual)
    if beta < tol:
        return x

    # Initialize the matrices and vectors
    matrix_q = np.zeros((n, max_iters + 1))
    matrix_h = np.zeros((max_iters + 1, max_iters))
    matrix_q[:, 0] = residual / beta
    e1 = np.zeros(max_iters + 1)
    e1[0] = beta

    # Run until error is below the tolerance or the max. number of iterations is reached
    for i in range(max_iters):
        # Calculate q_n with the Arnoldi method
        matrix_h, matrix_q = arnoldi_iteration(matrix_a, matrix_q, matrix_h, i)

        # Find the y_n which minimizes ‖ r_n ‖ using lstsq
        y, _, _, _ = lstsq(matrix_h[: i + 2, : i + 1], e1[: i + 2])

        # Compute x_n = x_0 + Q_n @ y_n
        x = x_zero + np.einsum("m n, n -> m", matrix_q[:, : i + 1], y)

        # Check if the current approximation is close enough
        residual = vector_b - np.einsum("m n, n -> m", matrix_a, x)
        error = norm(residual)
        if error < tol:
            return x
    return x


def main(args):
    # Define the matrix a
    matrix_a = np.random.randn(30, 30)

    # Define the vector b
    vector_b = np.random.randn(30)

    # GMRES
    x = gmres_(matrix_a, vector_b)

    print(matrix_a @ x, vector_b)


if __name__ == "__main__":
    # Parse the arguments
    parser = get_parser()
    args = parser.parse_args()
    main(args)
