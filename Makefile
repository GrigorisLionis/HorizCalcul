CC=g++

horizon: horizon.0.8.0.o linear_cgal.o linear.o calchor.o grid.o ray.o
	$(CC) -o horizon horizon.0.8.0.o linear_cgal.o linear.o calchor.o grid.o ray.o -lm -lCGAL

LIBS=CGAL
