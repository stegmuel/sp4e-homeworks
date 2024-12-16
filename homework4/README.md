# Homework 4


## Requirements

Eigen from the root of the repo
```
git submodule add https://gitlab.com/libeigen/eigen.git homework4/src/eigen
git submodule update --init --recursive
# sudo apt-get install libeigen3-dev
```

```
cd homework4
ln -s ../googletest googletest
```

PyBind from the root of the repo
```
git submodule add https://github.com/pybind/pybind11.git homework4/src/pybind11
git submodule update --init --recursive
```


## Building
```
cd homework4/build
cmake ../src
make
```

## Exercise 2

Launch the test
``` 
cd homework4/build
./test_finite_diff
```


## Exercise 3
## Exercise 4
## Exercise 5

Dummy tests:
```
cd homework4/build
make
mkdir dumps
python main.py 10 1 ../src/init.csv planet 1
python main.py 10 1 ../src/init.csv material_point 1
```

## Exercise 6

Launch a trajectory simulation for 365 days and a daily update of the position:
```
python main.py 365 1 ../src/init.csv planet 1  
```

## Exercise 7
Compute the error:
```
python compute_error.py --dumps_dir="homework4/build/dumps/" --refs_dir="homework4/build/refs/" --planet_name="mercury"
```

