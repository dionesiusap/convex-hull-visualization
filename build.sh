# A script to build the files for the first time
rm -R build
mkdir build
cd build
cmake ..
make -j 4