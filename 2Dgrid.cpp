#include <iostream>
#include<stdlib.h>
#include<cstring>
#include<cmath>
using namespace std;
static int N;
static int M;
static float xdim;
static float ydim;
struct point{
float x;
float y;
};
struct cell{
point index;
point p[4];
point centroid;
point face_centroid[4];
point face_normal[4];

public:
point getindex(){
return index; }

point* getpoints(){
return p; }

point* get_face_centroid(){
return face_centroid;}

point getcentroid(){
return centroid;}

void set_face_centroid(){
this->face_centroid[0].x=(this->p[0].x+this->p[1].x)/2;
this->face_centroid[0].y=(this->p[0].y+this->p[1].y)/2;
this->face_centroid[1].x=(this->p[1].x+this->p[2].x)/2;
this->face_centroid[1].y=(this->p[1].y+this->p[2].y)/2;
this->face_centroid[2].x=(this->p[2].x+this->p[3].x)/2;
this->face_centroid[2].y=(this->p[3].y+this->p[2].y)/2;
this->face_centroid[3].x=(this->p[0].x+this->p[3].x)/2;
this->face_centroid[3].y=(this->p[0].y+this->p[0].y)/2;
}

void setcentroid(){
this->centroid.x=(p[0].x+p[1].x+p[2].x+p[3].x)/4;
this->centroid.y=(p[0].y+p[1].y+p[2].y+p[3].y)/4;
set_face_centroid();
}

void setp(){
this->p[0].x=this->index.x*ydim;
this->p[0].y=this->index.y*xdim;
this->p[1].x=this->index.x*ydim+ydim;
this->p[1].y=this->index.y*xdim;
this->p[2].x=this->index.x*ydim+ydim;;
this->p[2].y=this->index.y*xdim+xdim;
this->p[3].x=this->index.x*ydim;
this->p[3].y=this->index.y*xdim+xdim;
setcentroid();
}

void setindex(float x,float y){
this->index.x=x;
this->index.y=y;
setp();}

point* get_face_normals(){
int i;
float dy,dx,l;
for(i=1;i<=3;i++){
dy=this->p[i].x-this->p[i-1].x;
dx=this->p[i].y-this->p[i-1].y;
l=sqrt(pow(dy,2)+pow(dx,2));
this->face_normal[i-1].x=dy/l;
this->face_normal[i-1].y=dx/l;
}
dy=this->p[0].x-this->p[3].x;
dx=this->p[0].y-this->p[3].y;
l=sqrt(pow(dy,2)+pow(dx,2));
this->face_normal[3].x=dy/l;
this->face_normal[3].y=dx/l;
return face_normal;
}};
int main(int argc, char *argv[]){
N=atoi(argv[1]);
M=atoi(argv[2]);
int pointx=atoi(argv[3]);
int pointy=atoi(argv[4]);
//cout<<N<<" "<<M<<" "<<pointx<<" "<<pointy<<" "<<endl;
ydim=N/(pointx-1);
xdim=M/(pointy-1);
struct cell t;
float cx=atof(argv[5]);
float cy=atof(argv[6]);
t.setindex(cx,cy);
FILE *fptr;
fptr=fopen("buffertext.txt","w");
char data[200];
char c1[200];
char c2[200];
if(fptr==NULL){
cout<<"FAILED TO OPEN BUFFER!!!"<<endl;}
else{
struct point p=t.getindex();
strcpy(data,"");
sprintf(c1,"%.2f",p.x);
sprintf(c2,"%.2f",p.y);
strcat(data,"The cell index is (");
strcat(data,c1);
strcat(data,",");
strcat(data,c2);
strcat(data,")");
fputs(data,fptr);
fputs("\n",fptr);
struct point *pt=t.getpoints();
sprintf(c1,"%.2f",pt[0].x);
sprintf(c2,"%.2f",pt[0].y);
strcpy(data,"");
strcat(data,"The left lower index is (");
strcat(data,c1);
strcat(data,",");
strcat(data,c2);
strcat(data,")");
fputs(data,fptr);
fputs("\n",fptr);
sprintf(c1,"%.2f",pt[1].x);
sprintf(c2,"%.2f",pt[1].y);
strcpy(data,"");
strcat(data,"The right lower index is (");
strcat(data,c1);
strcat(data,",");
strcat(data,c2);
strcat(data,")");
fputs(data,fptr);
fputs("\n",fptr);
sprintf(c1,"%.2f",pt[2].x);
sprintf(c2,"%.2f",pt[2].y);
strcpy(data,"");
strcat(data,"The right upper index is (");
strcat(data,c1);
strcat(data,",");
strcat(data,c2);
strcat(data,")");
fputs(data,fptr);
fputs("\n",fptr);
sprintf(c1,"%.2f",pt[3].x);
sprintf(c2,"%.2f",pt[3].y);
strcpy(data,"");
strcat(data,"The left upper index is (");
strcat(data,c1);
strcat(data,",");
strcat(data,c2);
strcat(data,")");
fputs(data,fptr);
fputs("\n",fptr);
struct point cent=t.getcentroid();
strcpy(data,"");
sprintf(c1,"%.2f",cent.x);
sprintf(c2,"%.2f",cent.y);
strcat(data,"The centroid is (");
strcat(data,c1);
strcat(data,",");
strcat(data,c2);
strcat(data,")");
fputs(data,fptr);
fputs("\n",fptr);
struct point *fcent=t.get_face_centroid();
strcpy(data,"");
sprintf(c1,"%.2f",fcent[0].x);
sprintf(c2,"%.2f",fcent[0].y);
strcat(data,"The fc1 point is (");
strcat(data,c1);
strcat(data,",");
strcat(data,c2);
strcat(data,")");
fputs(data,fptr);
fputs("\n",fptr);
strcpy(data,"");
sprintf(c1,"%.2f",fcent[1].x);
sprintf(c2,"%.2f",fcent[1].y);
strcat(data,"The fc2 point is (");
strcat(data,c1);
strcat(data,",");
strcat(data,c2);
strcat(data,")");
fputs(data,fptr);
fputs("\n",fptr);
strcpy(data,"");
sprintf(c1,"%.2f",fcent[2].x);
sprintf(c2,"%.2f",fcent[2].y);
strcat(data,"The fc3 point is (");
strcat(data,c1);
strcat(data,",");
strcat(data,c2);
strcat(data,")");
fputs(data,fptr);
fputs("\n",fptr);
strcpy(data,"");
sprintf(c1,"%.2f",fcent[3].x);
sprintf(c2,"%.2f",fcent[3].y);
strcat(data,"The fc4 point is (");
strcat(data,c1);
strcat(data,",");
strcat(data,c2);
strcat(data,")");
fputs(data,fptr);
fputs("\n",fptr);

point *face_normals=t.get_face_normals();
int i;
for(i=0;i<4;i++){
strcpy(data,"The face normal of surface");
strcat(data," ");
sprintf(c1,"%d",i);
strcat(data,c1);
strcat(data," : ");
sprintf(c1,"%.2f",face_normals[i].x);
strcat(data,c1);
strcat(data,"i+");
sprintf(c2,"%.2f",face_normals[i].y);
strcat(data,c2);
strcat(data,"j");
fputs(data,fptr);
fputs("\n",fptr);
}
fclose(fptr);
}}
