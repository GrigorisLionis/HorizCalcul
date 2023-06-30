# HorizCalcul
Simple horizon calculation from elevation data
This simple C program calculates the horizon "seen" from a point, given sufficient elevation data.  
It was inspired by the description given by Sherry Towers in [Archaeoastronomy](http://sherrytowers.com/2014/04/13/archeoastronomy-calculating-the-horizon-profile-using-online-us-geographic-survey-data/)

## Usage
The usage is prety simple.  
The elevation data are stored in elevetion.asc (i compiled such a file by encoding a geoTIFF file)  
A second file (test1.csv) contains lon,lat points to check the horizon.  
The compiled file is simply exectued, with the two files in the directory.  
Two files are written, (out.txt, RAW.txt). The first contains the percentage of the sky blocked by the terrain, the second the complete horizon for each point
A simple makefile is included

## How it works
The algorithm uses the elevation map to compute a triangle mesh around the point of interest.  
The for each ray eminating from the point of interest, it computes if the terrain intersects with the ray.  
Thus, a complete horizon map of the terrain is acquired  
Verison is  linked to CGAL (verison 4.7.1)   as in greatly simplifies code.  
Original -simple - functions to copute intersections between ray and triangle are also included



### Code Structure
The code is split into four source code files.
* horizon.c contains the main function. It reads the data and iterates over all the points to be cheked
* linear.c contains simple linear algebra functions. The current version links to CGAL computational geomtery library. We also include a  custom function  to reduce source dependenciession. Some minor changes to code/make file need to be made for this to work
* grid.c contains a function that computes a grid around the point of interest. 
* calchor.c is the acutal horizon computation function. It works by computing if/where each discrete ray eminating from the point of interest intersects the horizon
* ray.c contains a function that computes whether a ray intersects a mesh of triangles

### ToDo
It is a 0.8 level so there is substantial work to be made
* code cleaning, some redundant code is there
*  <del>connect with a computational geometry library. Ray-Triangle computations are bread-&-butter for computational libraries</del>
* implement a geotiff layer. This would substantially increase speed and reduce a lot of helper code. In particular, geoTIFF is already in a grid, so a lot of constructions would be un necessary

 
