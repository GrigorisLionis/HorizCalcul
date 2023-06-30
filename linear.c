#include <math.h>
#include <stdlib.h>

#include "definitions.h"


/*simple function to calculate 3x3 Determinant*/
double Det(double R[3][3]){
double a,b,c,d,e,f,g,h,i;
a=R[0][0];
b=R[0][1];
c=R[0][2];
d=R[1][0];
e=R[1][1];
f=R[1][2];
g=R[2][0];
h=R[2][1];
i=R[2][2];
return ( a*(e*i-f*h)-d*(b*i-h*c)+g*(b*f-e*c)  );
}

/*simple function for solving a 3x3 Ax=b linear problem*/
/*more fast-sophisticated solutions could be used*/
bool LSS(double A[3][3],double b[3],double x[3])
{
double D,D1,D2,D3;
double R[3][3];
int i,j;
D=Det(A);
if(abs(D)<0.0001)//ill defined system, return 0;
return false;
/*determinants when b is substituded on each column of A are calculated*/

for(i=0; i<3; i++)
for(j=0; j<3; j++)
R[i][j]=(j==0)?b[i]:A[i][j];
D1=Det(R);

for(i=0; i<3; i++)
for(j=0; j<3; j++)
R[i][j]=(j==1)?b[i]:A[i][j];

D2=Det(R);
for(i=0; i<3; i++)
for(j=0; j<3; j++)
R[i][j]=(j==2)?b[i]:A[i][j];

D3=Det(R);
x[0]=D1/D;
x[1]=D2/D;
x[2]=D3/D;

return true;
}




bool LIT(vec3 line[2],vec3 tri[3],vec3 *point)
{
/*fucntion to check wheter line intersects triangle
trianlge is defined from the three points
line is defined from the two points*/

double A[3][3];
double b[3],x[3];
bool Solv;
A[0][0]=tri[0].x-tri[2].x;
A[1][0]=tri[0].y-tri[2].y;
A[2][0]=tri[0].z-tri[2].z;

A[0][1]=tri[1].x-tri[2].x;
A[1][1]=tri[1].y-tri[2].y;
A[2][1]=tri[1].z-tri[2].z;

A[0][2]=-(line[1].x-line[0].x);
A[1][2]=-(line[1].y-line[0].y);
A[2][2]=-(line[1].z-line[0].z);

b[0]=line[0].x-tri[2].x;
b[1]=line[0].y-tri[2].y;
b[2]=line[0].z-tri[2].z;

Solv=LSS(A,b,x);
/*sovle to see if line inersects plane defined by the triangle*/


if(!Solv) {return false;} /*system has no solution. No intersection*/

if( x[0]>=0 && x[0]<=1 && x[1]>=0 &&  x[1]<=1 && (x[0]+x[1])<=1 && x[2]>0 )
{
/*check to establish that point is inside triangle*/
/*if so, return point*/
point->x=line[0].x+x[2]*line[1].x;
point->y=line[0].y+x[2]*line[1].y;
point->z=line[0].z+x[2]*line[1].z;
return true;
}
return false;
}




