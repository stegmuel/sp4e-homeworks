## Homework 3


#### Add googletest as a submodule
```
git submodule add https://github.com/google/googletest.git googletest
git submodule update --init --recursive
``` 

Then symlink the ```googletest``` folder.
```
cd homework3
ln -s ../googletest googletest
```

Build
```
cd build
cmake ../src
make
```

Test the FFT (TODO:update)
```
./test_fft
```


Test the temperature (TODO:update)

```
./test_temperature
```

Launch a simulation (TODO:update)

```
./particles 10 1 ../data/radial_heat_distribution.csv material_point 0.1 
```

