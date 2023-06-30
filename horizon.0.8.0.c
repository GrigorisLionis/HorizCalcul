#include <stdio.h>
#include <stdlib.h>
#include <math.h>


#include "definitions.h"

#include "linear.h"
#include "calchor.h"
#include "grid.h"

double Dis(double lat1,double lon1,double lat2,double lon2,double *dx,double *dy);



int main(void) {
 double x,y,z;
int i,n=0,j,k,l;
//double mylatitude;/// = 36.564393;
//double mylongitude;// = 23.050982;
// double myelevation = 5.0;
// double curlong,curlat;
 double *xhz,*yhz,*zhz;
 double dx,dy;
//std::array<double,2> Pref,Pcur,Cart;
//double theta,dis,phi;


double *GridX;
double *GridY;
double *GridZ;
int *GridI;
double xmin,ymin,xmax,ymax;
int gx,gy,Nx,Ny;
int myx,myy;
double Height;
int Lx,Ly;
int Horizon[360];
Lx=100;
Ly=100;
//grid size around point

double PointsToCheckX[300];
double PointsToCheckY[300];
int NoP=0;
double CurrGridX=0,CurrGridY=0;
double PosX,PosY;
double sum=0;

     FILE *fp = fopen("test1.csv", "r");
     if(fp == NULL) {
         perror("Unable to open file!");
         exit(1);
     }

while(fscanf(fp,"%lf,%lf\n",&y,&x)!=EOF) 
{
PointsToCheckX[NoP]=x;
PointsToCheckY[NoP]=y;
NoP++;
}
if(fp)fclose(fp);
fp=NULL;
for (i=0; i<NoP; i++)
printf("\n %lf %lf ",PointsToCheckX[i],PointsToCheckY[i]);



 fp = fopen("elevation.asc", "r");
     if(fp == NULL) {
         perror("Unable to open file!");
         exit(1);
     }




xhz=( double*)malloc(40000000*sizeof( double));
yhz=( double*)malloc(40000000*sizeof( double));
zhz=( double*)malloc(40000000*sizeof( double));
//1.5 mil points....
//we use a mask of 0.5 deg ~ 30x30 km... 
// 30 
if ((xhz==NULL) || (yhz==NULL) || (zhz==NULL))
{
printf("ERROR, could not allocate memory");
exit(1);
}

while(fscanf(fp,"%lf %lf %lf",&x,&y,&z)!=EOF) 
{

xhz[n]=x;
yhz[n]=y;
zhz[n]=z;
n++;
//if(n%1000000==0) printf("\n %d",n/1000);
}

fprintf(stderr,"\n File on memory");
fprintf(stderr,"\n #of points %d",n);
if(fp)fclose(fp);
xmin=180;
xmax=-180;
ymin=90;
ymax=-90;

for(i=0; i<n; i++)
{
xmax=xhz[i]>xmax?xhz[i]:xmax;
xmin=xhz[i]<xmin?xhz[i]:xmin;
ymax=yhz[i]>ymax?yhz[i]:ymax;
ymin=yhz[i]<ymin?yhz[i]:ymin;
}
Nx=6000;
Ny=6000;

dx=(xmax-xmin)/Nx;
dy=(ymax-ymin)/Ny;


GridX=(double*)malloc((Lx+1)*(Ly+1)*sizeof(double));
if(GridX==NULL) 
{
fprintf(stderr,"GridX could not be allocated,Aborting");
exit(1);
}

GridY=(double*)malloc((Lx+1)*(Ly+1)*sizeof(double));
if(GridY==NULL) 
{
fprintf(stderr,"GridY could not be allocated,Aborting");
exit(1);
}

GridZ=(double*)malloc((Lx+1)*(Ly+1)*sizeof(double));
if(GridZ==NULL) 
{
fprintf(stderr,"GridZ could not be allocated,Aborting");
exit(1);
}

GridI=(int*)malloc((Lx+1)*(Ly+1)*sizeof(int));
if(GridZ==NULL) 
{
fprintf(stderr,"GridZ could not be allocated,Aborting");
exit(1);
}

//char snum[10];
//Horizon=(int*)malloc(360*sizeof(int));

FILE *fp2=fopen("out.txt","w");
  if(fp2 == NULL) {
         perror("Unable to open file!");
         exit(1);}
FILE *fp1;
fp1=fopen("RAW.txt","w");
if(fp1 == NULL) {
         perror("Unable to open file RAW!");
         exit(1);}

for(j=0; j<NoP; j++)
{
if (Dis(CurrGridX,CurrGridY,PointsToCheckX[j],PointsToCheckY[j],&PosX,&PosY) >40)
{
printf("\n Create New Grid around point %lf-%lf",PointsToCheckX[j],PointsToCheckY[j]);
fprintf(stderr,"\n Position of point was determined %lf-%lf out of Grid",PosX,PosY);
CreateGrid(xhz,yhz,zhz,GridX,GridY,GridZ,GridI,Lx,Ly,n,xmin,dx,ymin,dy,PointsToCheckX[j],PointsToCheckY[j]);
CurrGridX=PointsToCheckX[j];
CurrGridY=PointsToCheckY[j];
printf("\n Grid Recalculated");
}

Dis(CurrGridX,CurrGridY,PointsToCheckX[j],PointsToCheckY[j],&PosX,&PosY);
fprintf(stderr,"\n Position of point was determined %lf-%lf",PosX,PosY);

fprintf(stderr,"\n Calculating Horizon" );
CalcHor(GridX,GridY,GridZ,Lx,Ly,360,Horizon,PosX,PosY,&Height);
sum=0;
for(i=0; i<360; i++)
{
fprintf(fp1,"\n %lf %lf %d %d",PointsToCheckX[j],PointsToCheckY[j],i,Horizon[i]);
sum=sum+Horizon[i];
}
printf("\n Σημείο %lf %lf, on Grid %lf-%lf Στερεοακτίνια ορίζοντα κατειλημένα : %f  Ποσοστό Ουρανού : %f",PointsToCheckX[j],PointsToCheckY[j],PosX,PosY,sum,sum/(360*90));
fprintf(fp2,"\n %lf %lf %lf %lf",PointsToCheckX[j],PointsToCheckY[j],Height,sum/(360*90));

}


}







double Dis(double lat1,double lon1,double lat2,double lon2,double *dx,double *dy)
{
double dlat,dlon;
dlat=lat2-lat1;
dlon=lon2-lon1;
*dy=dlat*111320; 
*dx=dlon*(111413*cos(lat1*3.141592/180)-93.5*cos(3*lat1*3.141592/180));
return(sqrt( (*dx)*(*dx)+(*dy)*(*dy)));
/*calculate distance over lat,lon*/
}





