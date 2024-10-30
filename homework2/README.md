# sp4e-homeworks

**Authors:** Thomas Stegmüller, Guillaume Vray

## Homework 2

### Collaboration

This homework involved the development of two main modules:

- **Mathematical Series Computation**: The first author implemented this module, which includes algorithms for calculating various mathematical series, such as the Arithmetic series, Pi estimation, and Riemann integrals.

- **Data Output Module**: The second author developed this module, which manages the functionality for displaying results in the terminal or saving them to different file formats as specified by the user.

### Dependencies

This project requires Python 3.11 and the following packages:

```plaintext
scipy==1.14.1
numpy==1.26.4
matplotlib==3.8.4
```

The C++ code has been tested with GCC 13.2.0.

### Project Structure

The code is organized as follows:

```plaintext
sp4e-homeworks
└─── homework2
     ├── src
     │    ├── main.cc
     │    ├── ...
     │    └── plot.py
     ├── CMakeLists.txt
     ├── README.md
     └── .gitignore
```

- **`main.cc`**: C++ program that computes series for the Arithmetic series, Pi approximation, and Riemann integral estimates. Results can be outputted to the terminal and/or saved to a file based on user preferences.
- **`plot.py`**: Python script to visualize computed series results for each step.

### Usage Instructions

#### 1. Build the Project

To build the project, execute the following commands in the terminal:

```bash
mkdir build
cd build
cmake ..
make
```
To run the executable in terminal, go to the `build` folder.

#### 2. Compute Series

The program can compute different mathematical series depending on the `--serie_type` argument provided:

- **Arithmetic Series**: Compute the arithmetic series up to a specified number of terms, `N`.

    ```bash
    ./src/main --serie_type arithmetic --maxiter N
    ```

- **Pi Estimation**: Estimate Pi by computing a converging series with `N` terms. Greater is `N`, more precise is the estimation.

    ```bash
    ./src/main --serie_type pi --maxiter N
    ```

- **Riemann Integral**: Compute the Riemann integral of a function `f` over the interval `[a, b]`. Supported functions are `cubic`, `cos`, and `sin`.

    ```bash
    ./src/main --serie_type integral --integral_f f --integral_a a --integral_b b --maxiter N
    ```

    Increase `--maxiter` to improve precision.

#### 3. Control Output Format and Frequency

To configure how results are displayed or saved, specify the `--dumper_type` option:

- **Print to Terminal**: To print results to the terminal.

    ```bash
    ./src/main --dumper_type print
    ```

- **Save to File**: To save results to a file, specify `--dumper_type write` and set the file delimiter with `--separator`:
    - `--separator ,` to save results in a `.csv` file
    - `--separator " "` to save results in a `.txt` file
    - `--separator |` to save results in a `.psv` file

Control how often results are printed or saved by specifying `--print_frequency`. To adjust decimal precision, use the `--precision` argument.

#### 4. Visualize Results

After saving results to a file, use the `plot.py` script to visualize them:

```bash
cd src
python plot.py --value_file output_file
```

This will generate a plot showing the series results over each iteration step. If the analytical prediction
is provided in the `value_file` it is also plotted along with the errors.

When the analytical prediction is not provided in the `value_file` it can be provided to the python script.
This can be used to infer the number of iterations needed to reach "convergence" (see Question 6.4):


```bash
python plot.py --value_file output_file --analytical_prediction analytical_prediction
```

In particular the following number of iterations are needed for the integrals:

- x**3 between 0 and 1: 50
- cos(x) between 0 and pi: 314 
- sin(x) between 0 and pi/2: 78

### Complexity of the program

The code is designed for computational efficiency, effectively preventing the need to recompute the entire series when producing intermediate steps. If we were to employ a heuristic approach that computes the series at every intermediate step, the time complexity would be $O(n^2)$.

In contrast, this implementation utilizes a strategy where previous results are stored and reused, resulting in a significantly improved complexity of $O(N)$.

Moreover, we can further minimize rounding errors in floating-point operations by summing the terms in reverse order. The optimal complexity for this approach remains $O(N)$, particularly if the series is strictly monotonic. For instance, in the case of an increasing series like the arithmetic series, the existing code suffices. However, when estimating $\pi$, we would need to incorporate additional code to explicitly compute the terms in reverse order.
