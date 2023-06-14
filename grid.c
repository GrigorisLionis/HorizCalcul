#include <math.h>
#include <stdlib.h>
#include "calchor.h"

#include "definitions.h"
void CreateGrid(double *xhz,double *yhz,double *zhz,double *GridX,double *GridY,double *GridZ,int *GridI,int Lx,int Ly,int n,double xmin,double dx,double ymin,double dy,double mylatitude,double mylongitude)
{
/*
this function calculates a cartesian grid around the point of interest
the coordinates are transformed into easting and northing (meters)
*/



int i,j,k,l,myx,myy;
double dlat,dlon,curlong,curlat;
int gx,gy;
bool *Grid=NULL;
if(Grid==NULL)
Grid=(bool*)malloc((Lx+1)*(Ly+1)*sizeof(bool));
for(i=0; i<=Lx; i++)
for(j=0; j<=Ly; j++)
{
Grid[i+(Lx+1)*j]=false;
}
myx=(int)round((mylongitude-xmin)/dx);
myy=(int)round((mylatitude-ymin)/dy);
for(i=0; i<n; i++)
{
gx=(int)round((xhz[i]-xmin)/dx);
gy=(int)round((yhz[i]-ymin)/dy);
if((abs(gx-myx)<=Lx/2)&&(abs(gy-myy)<=Ly/2))
{
GridI[Lx/2-gx+myx+Lx*(Ly/2-gy+myy)]=i;
Grid[Lx/2-gx+myx+Lx*(Ly/2-gy+myy)]=true;
}

}
//find height of cpoint

for(k=0; k<Lx; k++)
for(j=0; j<Ly; j++)
{
//if(!Grid[k+Lx*j])
//{
//printf("\n ERROR - grid point is missing");
//continue;
//}
i=GridI[k+Lx*j];
GridZ[k+Lx*j]=zhz[i];
curlong=xhz[i];
curlat=yhz[i];
dlat=curlat-mylatitude;
dlon=curlong-mylongitude;
dx=dlat*111320; 
dy=dlon*(111413*cos(mylatitude*3.141592/180)-93.5*cos(3*mylatitude*3.141592/180));
//https://calgary.rasc.ca/latlong.htm
//formulats for calculationg local coordinates
GridX[k+Lx*j]=dx;
GridY[k+Lx*j]=dy;
}
if(Grid) free(Grid);
return;
}

