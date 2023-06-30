#include <math.h>
#include <stdio.h>

#include "definitions.h"
#include "linear.h"
#include "calchor.h"
#include "ray.h"

int CalcHor(double *GridX,double *GridY,double *GridZ,int xL,int yL,int AzDi,int *Horizon,double Xo,double Yo,double *Height)
{

int k,l,i,j;
vec3 tri[3];
vec3 line0[2];
vec3 point;
//double Height;
bool Ascend;



/*calculate height of point*/
/*it is calculated by finding which cell intersects with a ray towards the sky*/
bool fl=false;
for(k=0; k<xL-1; k++)
{
fl=false;
for(l=0; l<yL-1; l++)
{
tri[0].x=GridX[k+l*xL];
tri[0].y=GridY[k+l*xL]; 
tri[0].z=GridZ[k+l*xL];
tri[1].x=GridX[k+1+l*xL];
tri[1].y=GridY[k+1+l*xL]; 
tri[1].z=GridZ[k+1+l*xL];
tri[2].x=GridX[k+1+(l+1)*xL];
tri[2].y=GridY[k+1+(l+1)*xL]; 
tri[2].z=GridZ[k+1+(l+1)*xL];

line0[0].x=Xo;
line0[0].y=Yo;
line0[0].z=0;
line0[1].x=Xo;
line0[1].y=Yo;
line0[1].z=10;

  if(LIT(line0, tri, &point))  
  {
  *Height=point.z;
  fl=true;
  printf("LTI_C res: %d",LIT_CGAL(line0,tri,&point));
  break;
  }

tri[1].x=GridX[k+(l+1)*xL];
tri[1].y=GridY[k+(l+1)*xL]; 
tri[1].z=GridZ[k+(l+1)*xL];
  if(LIT(line0, tri, &point)) 
  {
  
  *Height=point.z;
  fl=true;
  break;
  }

}
if(fl) break; //

}
fprintf(stderr,"\n Point  Height Calculated: %lf",*Height);


/*the rays are calculated from the calculated heihjt*/
line0[0].x=Xo;
line0[0].y=Xo;
line0[0].z=*Height+1;


int p1XS,p1YS,p2XS,p2YS,p3XS,p3YS;
for(i=0; i<AzDi; i++)
{
Horizon[i]=0; // zero value to the Vector of view angle wrt Azimuth angle

line0[1].x=Xo+cos(i*3.1415/180);  //calculate direction vector, unity vector, one meter with angle i, counterclocwise
line0[1].y=Yo+sin(i*3.1415/180); 

//test view angle 8. If intersects, go up-wards
//if not, go downwards
//a simple binary search over the angles

line0[1].z=*Height+1+tan(8*3.1415/180);  //horizontal projection of vector  is of length 1. vertical component is defined as 
Ascend=RayInterects(GridX,GridY,GridZ,xL,yL,line0);
//printf("\n Azimuth angle :%d , test Angle %s\n",i,(Ascend?"True":"False") ) ;
if(Ascend)
{
Horizon[i]=8;
for(j=9; j<89; j++)
{
line0[1].z=*Height+1+tan(j*3.1415/180);
if(!RayInterects(GridX,GridY,GridZ,xL,yL,line0)) break; // 
Horizon[i]=j; // if intersects, then Horizon[i] is at least j. 
}
}
else // decrease 
{
for(j=8; j>0; j--)
{
line0[1].z=*Height+1+tan(j*3.1415/180); //new dir of line, with j being reduced
if(RayInterects(GridX,GridY,GridZ,xL,yL,line0))
   { // first break, Horizon is defined as the first view angle where the we have an intersection
   Horizon[i]=j;
   break;
   }
}

}

}
return 1;
}



