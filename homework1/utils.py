from numpy.typing import NDArray


class ResultsSaverCallback(object):
    """
    Class to collect intermediate results during optimization.
    
    Args:
        x0 (NDArray): Coordinates of the initial point.
    """
    def __init__(
        self, x0 : NDArray
    ):
        self.xs = [x0]

    def __call__(self, x):
        self.xs.append(x)