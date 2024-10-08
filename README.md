
# sp4e-homeworks

**Authors:** Thomas Stegmüller, Guillaume Vray

## Homework 1

### Dependencies

This project requires Python 3.11 and the following packages:

```
scipy==1.14.1
numpy==1.26.4
matplotlib==3.8.4
```

### Project Structure

The code is organized as follows:
```
sp4e-homeworks
│   README.md
│   .gitignore    
└───homework1
    │   optimizer.py
    │   GMRES.py
```

- `optimizer.py`: Utilizes built-in functions from NumPy and SciPy to solve linear equations of the form \(Ax = b\), where A and b are hardcoded. It also includes a 3D plotting feature to visualize each step of the optimization process.
- `GMRES.py`: Implements the GMRES (Generalized Minimal Residual) method from scratch. Unlike `optimizer.py`, this script allows the user to specify the matrix A and vector b. 

### Usage Instructions

#### Running `optimizer.py`

To run the `optimizer.py` script, use the following command:

```
python optimizer.py --method <optimization_method>
```

- `--method` specifies the optimization method to be used. Available options are:
  - `bfgs`: Broyden–Fletcher–Goldfarb–Shanno (BFGS) algorithm
  - `lgmres`: LGMRES method

#### Running `GMRES.py`

To run the `GMRES.py` script, use:

```
python GMRES.py <matrix_A_elements> <vector_b_elements> --method <optimization_method> --plot
```

- `<matrix_A_elements>`: The elements of matrix A in row-major order (e.g., `a11a12 a21a22` for a 2x2 matrix).
- `<vector_b_elements>`: The elements of vector b (e.g., `b1b2` for a vector of size 2).
- `--method`: Choose from:
  - `bfgs` or `lgmres`: These options use the same built-in methods as in `optimizer.py`.
  - `lgmres2`: This uses the GMRES method implemented from scratch in `GMRES.py`.
- `--plot`: (Optional) Generates a 3D plot of the optimization process. This option is only available for 2D problems (i.e., a 2x2 matrix A and a 2D vector b).

#### Example Usage

For a 2x2 matrix A and 2D vector b:
```
python GMRES.py a11a12 a21a22 b1b2 --method lgmres2 --plot
```

For a 3x3 matrix A and 3D vector b, without plotting:
```
python GMRES.py a11a12a13 a21a22a23 a31a32a33 b1b2b3 --method lgmres2
```