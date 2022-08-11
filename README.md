# my_cpp_empty_project

## how to use it
```bash
# clone repository and submodule

git clone --recursive https://github.com/StoneHappy/my_cpp_empty_project.git

# create buid dir

mkdir build

# generate build project
cmake ..
```

``Ninja`` build tool is recommended!!!!

On the windows platform, add ``vcvars64.bat`` to the environment variable. Type ``vcvars64.bat`` on the command line to configure the current command line environment, and then 
``cmake -S ./ -B ./build -G Ninja``

On linx, just ``cmake -S ./ -B ./build -G Ninja``