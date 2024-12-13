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
