instructions:
cmake -DCGAL_DIR=$CMAKE_INSTALLED_PREFIX/lib/CGAL -DCMAKE_BUILD_TYPE=Release .
make
./PROJECT -i input.txt -o outpout.txt -algorithm convex_hull -edge_selection 1 or 2 or 3
