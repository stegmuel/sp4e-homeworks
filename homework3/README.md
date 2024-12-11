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
- The creation of particles is typically triggered by the class ```CsvReader```which parses an input ```.csv``` file and adds particle to the system.
- The system stores pointer to the particles in a vector. The particles are "owned" by the system and can be accessed via their index in the vector.
- The factories are responsible for the creation of simulations via the class ```SystemEvolution``` which stores a pointer to the system and pointers to ```Compute``` subclasses.



## Exercise 3:

The implementations of the forward/backward FFT interfaces and the function that computes the wave numbers can be tested as follows.

```
cd homework3/build
./test_fft
```

## Exercise 4:

### Testing the solver
The implementation of the ```ComputeTemperature``` subclass that computes a full step of the time integration can be tested as follows.

```
cd homework3/build
./test_temperature
```


### Generating a radial heat rate distribution

The script ```generate_input_csv.py``` will generate a ```.csv``` file that can be fed as input to the ```main.cc``` script to launch a simulation.

```
cd homework3/
mkdir data
cd src/
python generate_input_csv.py \
  --savepath ../data/radial_heat_distribution.csv \
  --n_points_per_side 512 \
  --radius 0.5 \
  --x_min -1.0 \
  --x_max 1.0 \
  --y_min -1.0 \
  --y_max 1.0
```
To handle the boundary conditions, we add a boolean flag to the particle attributes. This flag is added as an extra column in the ```.csv``` file and then parsed by the ```initself``` function from the ```MaterialPoint``` class. We add a condition in ```ComputeTemperature::compute``` to prevent the update of boundary particles' state.


### Launching a simulation

Given the input ```.csv``` file generated as above described, one can launch a simulation with the following command:

```
cd /homework3/build/
mkdir -p dumps
./particles 10 1 ../data/radial_heat_distribution.csv material_point 0.001 
```
This will produce output ```.csv``` files in ```homework3/build/dumps/``` that can be used as input in Paraview.

