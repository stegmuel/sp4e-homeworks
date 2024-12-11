# Homework 3


**Authors:** Guillaume Vray, Thomas Stegmüller

## Requirements
### Python
The required libraries can be installed with
```
pip install -r requirements.txt
```
### C++

- CMake: Version 3.1 or newer.
- C++ Compiler: A C++17-compatible compiler is required.
- FFTW (```sudo apt install libfftw3-dev```)

### Submodule(s)
```googletest``` can be added as a submodule with the following instructions.
```
git submodule add https://github.com/google/googletest.git googletest
git submodule update --init --recursive
``` 

Then symlink the ```googletest``` folder.
```
cd homework3
ln -s ../googletest googletest
```

## Exercise 1: Code discovery


## Exercise 2:



Build
```
cd build
cmake ../src
make
```

### Exercise 3:


Test the FFT (TODO:update)
```
./test_fft
```

### Exercise 4:



Test the temperature (TODO:update)

```
./test_temperature
```

Generate the input .csv file(TODO:update):

```
python generate_input_csv.py
```

Launch a simulation(TODO:update):

```
./particles 10 1 ../data/radial_heat_distribution.csv material_point 0.1 
```

