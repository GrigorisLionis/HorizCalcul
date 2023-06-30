#include <stdio.h>
#include <stdlib.h>
#include <math.h>



#include <CGAL/Simple_cartesian.h>
#include <CGAL/intersections.h>
#include <CGAL/iterator.h>
#include <CGAL/point_generators_2.h>
#include <boost/bind.hpp>
#include <CGAL/Point_3.h>
#include <CGAL/Triangle_3.h>
#include <CGAL/Ray_3.h>
#include <CGAL/Segment_3.h>


#include "definitions.h"

typedef CGAL::Simple_cartesian<double> K;
typedef K::Point_3                     Point;
typedef K::Triangle_3 Triangle;
typedef K::Ray_3 Ray;
typedef K::Segment_3 Segment;



bool LIT_CGAL(vec3 line[2],vec3 tri[3],vec3 *point)
{
 Point po1(tri[0].x,tri[0].y,tri[0].z);
 Point po2(tri[1].x,tri[1].y,tri[1].z);
 Point po3(tri[2].x,tri[2].y,tri[2].z);
 Triangle tr1(po1,po2,po3);

 Point orig(line[0].x,line[0].y,line[0].z);
 Point op(line[1].x,line[1].y,line[1].z);
 Ray ray1(orig,op);
 return (CGAL::do_intersect(tr1,ray1));
 
}



