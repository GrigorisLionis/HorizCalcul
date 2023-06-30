#include <stdio.h>
#include "definitions.h"
#include "linear.h"
#include <cstdlib>
#include <math.h>

#define sgn(v) ((v>0)-(v<0))

void rotate_xy(float x0, float y0,float theta, float *yn)
{
//*xn=x0*cos(theta)-y0*sin(theta);
*yn=x0*sin(theta)+y0*cos(theta);
}

bool tri_lin(vec3 tri[3],float theta)
{
float x1,y1,x2,y2,x3,y3;
float x,y1n,y2n,y3n;
x1=tri[0].x;
y1=tri[0].y;
x2=tri[1].x;
y2=tri[1].y;
x3=tri[2].x;
y3=tri[2].y;
//rotate all points - only y coordinates are used
rotate_xy(x1,y1,theta,&y1n);
rotate_xy(x2,y2,theta,&y2n);
rotate_xy(x3,y3,theta,&y3n);
//rotated[0].x=x1n;
//rotated[0].y=y1n;
//rotated[1].x=x2n;
//rotated[1].y=y2n;
//rotated[2].x=x3n;
//rotated[2].y=y3n;

//check if there is a single combination of yn of different sign
if ( (y1n*y2n<1) || (y1n*y3n<1) || (y2n*y3n<1) )
return true;
return false;

}



bool RayInterects(double *GridX,double *GridY,double *GridZ,int xL,int yL,vec3 line0[2])
{
/*function to check if Ray Intersects with Mesh
GrixX, GridY,GridZ are repspectively coordinates of X,Y,Z points
There are xL, and yL are the size of the Grid
Each point X,Y,Z is considered to be one point of the triangle mesh describing the topography
*/
int k,l,i,j;
vec3 tri[3];
vec3 rot_tri[3];
vec3 point;
int DirX,DirY;
float theta;
DirX=sgn(line0[1].x-line0[0].x);
DirY=sgn(line0[1].y-line0[0].y);
/*the direction of the line*/

theta=atan2(line0[1].y-line0[0].y,line0[1].x-line0[0].x);
/*angle of line*/


for(k=0; k<xL-1; k++)
{
for(l=0; l<yL-1; l++)
{

/*we compute a triangle*/
tri[0].x=GridX[k+l*xL];
tri[0].y=GridY[k+l*xL]; 
tri[0].z=GridZ[k+l*xL];
tri[1].x=GridX[k+1+l*xL];
tri[1].y=GridY[k+1+l*xL]; 
tri[1].z=GridZ[k+1+l*xL];
tri[2].x=GridX[k+1+(l+1)*xL];
tri[2].y=GridY[k+1+(l+1)*xL]; 
tri[2].z=GridZ[k+1+(l+1)*xL];

//if (tri_lin(tri,theta))

/*check if any of the grid points is on the correct quadrant. If not, no need to check 
It is cheaper to check if a triangle is on the "other" side of the eminating ray

*/
if ( ( (sgn(tri[0].x-line0[0].x)==DirX) && (sgn(tri[1].y-line0[0].y)==DirY) )  || ( (sgn(tri[1].x-line0[0].x)==DirX) && (sgn(tri[2].y-line0[0].y)==DirY)) || ( (sgn(tri[2].x-line0[0].x)==DirX) && (sgn(tri[2].y-line0[0].y)==DirY)) ) 
if(tri_lin(tri,-theta)==true)
if(LIT_CGAL(line0, tri, &point)) 
return true;



/*calcultate second triangle on the same XY Grid*/
/*each k,l cell has four points and defines two triangles*/
tri[1].x=GridX[k+(l+1)*xL];
tri[1].y=GridY[k+(l+1)*xL]; 
tri[1].z=GridZ[k+(l+1)*xL];


if ( ( (sgn(tri[0].x-line0[0].x)==DirX) && (sgn(tri[1].y-line0[0].y)==DirY) )  || ( (sgn(tri[1].x-line0[0].x)==DirX) && (sgn(tri[2].y-line0[0].y)==DirY)) || ( (sgn(tri[2].x-line0[0].x)==DirX) && (sgn(tri[2].y-line0[0].y)==DirY)) ) 
if(tri_lin(tri,-theta)==true)
if(LIT_CGAL(line0, tri, &point) ) 
return true;




}
} /*loop over Grid ends*/

//if (rand()<0.3*RAND_MAX)
//printf("\n CGAL %d",LIT(line0,tri,&point));
return false;


}

