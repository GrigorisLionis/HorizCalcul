CC=g++

LIBS_CGAL = -lm -lCGAL -lstdc++
LIBS_LIGHT = -lm
objects_cgal = horizon.0.8.0.o linear_cgal.o linear.o calchor.o grid.o ray.o
objects_light = horizon.0.8.0.o linear.o calchor.o grid.o ray.o


horizon_cgal: $(objects_cgal)
	cc -o horizon $(objects_cgal) $(LIBS_CGAL)

horizon_light: $(objects_light)
	cc -o horizon $(objects_light) $(LIBS_LIGHT)


horizon.0.8.0.o: definitions.h linear.h grid.h calchor.h
linear_cgal.o : definitions.h
linear.o : definitions.h
grid.o: calchor.h definitions.h
ray.o : linear.h definitions.h version.def


.PHONY : clean

clean :
	rm  -f horizon $(objects_cgal)

