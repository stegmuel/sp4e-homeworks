# Homework 4


## Requirements

Eigen
```
cd homework4
wget https://gitlab.com/libeigen/eigen/-/archive/3.4.0/eigen-3.4.0.tar.gz
tar -xvzf eigen-3.4.0.tar.gz
mv eigen-3.4.0 eigen
```

```
cd homework4
ln -s ../googletest googletest
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
