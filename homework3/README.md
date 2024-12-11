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


## Building the project
```
cd homework3/build
cmake ../src
make
```

## Exercise 1
The particles are organized as follows.

- ```MaterialPoint```, ```Planet``` and ```PingPongBall``` inherit from the class ```Particle``` 
- ```MaterialPointFactory```, ```PlanetFactory``` and ```PingPongBallFactory``` inherit from the class ```ParticleFactoryInterface``` 
- ```ParticleFactoryInterface``` is an interface and cannot be instantiated. The remaining factory classes are implemented as singletons, implying that only a single factory can be instantiated.
- The factories are responsible for the creation of the particles.
- The creation of particles is typically triggered by the class ```CsvReader```which parses an input csv file and adds particle to the system.
- The system stores pointer to the particles in a vector. The particles are "owned" by the system and can be accessed via their index in the vector.
- The factories are responsible for the creation of simulations via the class ```SystemEvolution``` which stores a pointer to the system and pointers to ```Compute``` subclasses.



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

