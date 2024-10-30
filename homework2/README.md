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
          ├── ...
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

#### 2. Compute Series

The program can compute different mathematical series depending on the `--serie_type` argument provided:

- **Arithmetic Series**: Compute the arithmetic series up to a specified number of terms, `N`.

    ```bash
    ./main --serie_type arithmetic --maxiter N
    ```

- **Pi Estimation**: Estimate Pi by computing a converging series with `N` terms. Greater is `N`, more precise is the estimation.

    ```bash
    ./main --serie_type pi --maxiter N
    ```

- **Riemann Integral**: Compute the Riemann integral of a function `f` over the interval `[a, b]`. Supported functions are `cubic`, `cos`, and `sin`.

    ```bash
    ./main --serie_type integral --integral_f f --integral_a a --integral_b b --maxiter N
    ```

    Increase `--maxiter` to improve precision.

#### 3. Control Output Format and Frequency

To configure how results are displayed or saved, specify the `--dumper_type` option:

- **Print to Terminal**: To print results to the terminal.

    ```bash
    ./main --dumper_type print
    ```

- **Save to File**: To save results to a file, specify `--dumper_type write` and set the file delimiter with `--separator`:
    - `--separator ,` to save results in a `.csv` file
    - `--separator " "` to save results in a `.txt` file
    - `--separator |` to save results in a `.psv` file (pipe-separated values)

Control how often results are printed or saved by specifying `--print_frequency`. To adjust decimal precision, use the `--precision` argument.

#### 4. Visualize Results

After saving results to a file, use the `plot.py` script to visualize them:

```bash
python plot.py --value_file output_file
```

This will generate a plot showing the series results over each iteration step.
