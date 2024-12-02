## Homework 2


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
```


