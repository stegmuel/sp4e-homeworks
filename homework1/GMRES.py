import argparse
import numpy as np

from numpy.typing import NDArray
from numpy.linalg import norm
from scipy.linalg import lstsq
from typing import Tuple

from utils import ResultsSaverCallback


def gmres_(
    matrix_a: NDArray,
    vector_b: NDArray,
    x_zero: NDArray,
    callback: ResultsSaverCallback,
    tol: float = 1e-6,
    max_iters: int = 100,
) -> Tuple[NDArray, ResultsSaverCallback]:
    """Solves linear equation Ax=b using the General Minimal Residual Method.

    Args:
        matrix_a (NDArray): The matrix A, an invertible square matrix of shape (n x n)
        vector_b (NDArray): The vector b of shape (n,)
        x_zero (NDArray): Initialization for x of shape (n,)
        callback (ResultsSaverCallback): Callable object to store intermediate points.
        tol (float, optional): Value under which the solution error is accepted. Defaults to 1e-6.
        max_iters (int, optional): Maximum number of iterations before returning a solution. Defaults to 100.

    Returns:
        Tuple[NDArray, ResultsSaverCallback]: Returns the minimizer x and the intermediate steps.
    """
    # The matrix A is assumed to be invertible
    assert (
        matrix_a.shape[0] == matrix_a.shape[1] and matrix_a.ndim == 2
    ), "A square matrix is expected."
    assert np.linalg.det(matrix_a) != 0, "The matrix is expected to be invertible."

    def arnoldi_iteration(
        matrix_a: NDArray, matrix_q: NDArray, matrix_h: NDArray, i: int
    ) -> Tuple[NDArray, NDArray]:
        """Compute a basis of the (n + 1)-Krylov subspace of the matrix A used for GMRES optimization"""
        # Arnoldi process to build the orthonormal basis V and Hessenberg matrix H
        q_k = np.einsum("m n, n -> m", matrix_a, matrix_q[:, i])
        for j in range(i + 1):
            matrix_h[j, i] = np.einsum("m, m ->", matrix_q[:, j].conj(), q_k)
            q_k = q_k - matrix_h[j, i] * matrix_q[:, j]

        matrix_h[i + 1, i] = norm(q_k)
        matrix_q[:, i + 1] = q_k / matrix_h[i + 1, i]
        return matrix_h, matrix_q

    # Set default values
    n = len(vector_b)

    # Normalize the right-hand side vector
    b_norm = norm(vector_b)

    # Initialize variables
    x = x_zero
    residual = vector_b - np.einsum("m n, n -> m", matrix_a, x)

    beta = norm(residual)
    if beta < tol:
        return x, callback

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

        # Return intermediate value x
        callback(x)

        # Check if the current approximation is close enough
        residual = vector_b - np.einsum("m n, n -> m", matrix_a, x)
        error = norm(residual)
        if error < tol:
            return x, callback
    return x, callback
