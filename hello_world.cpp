#include <iostream>
#include<stdlib.h>
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
};
int main(int argc, char *argv[]){
N=atoi(argv[1]);
M=atoi(argv[2]);
int pointx=atoi(argv[3]);
int pointy=atoi(argv[4]);
//cout<<N<<" "<<M<<" "<<pointx<<" "<<pointy<<" "<<endl;
xdim=N/(pointx-1);
ydim=M/(pointy-1);
struct cell t;
float cx=atof(argv[5]);
float cy=atof(argv[6]);
t.setindex(cx,cy);
struct point p=t.getindex();
cout<<"The cell index is "<<p.x<<" "<<"and "<<p.y<<endl;
struct point *pt=t.getpoints();
cout<<"The left lower point is ("<<pt[0].x<<","<<pt[0].y<<")"<<endl;
cout<<"The right lower point is ("<<pt[1].x<<","<<pt[1].y<<")"<<endl;
cout<<"The right upper point is ("<<pt[2].x<<","<<pt[2].y<<")"<<endl;
cout<<"The left upper point is ("<<pt[3].x<<","<<pt[3].y<<")"<<endl;
struct point cent=t.getcentroid();
cout<<"The centroid is ("<<cent.x<<","<<cent.y<<")"<<endl;
struct point *fcent=t.get_face_centroid();
cout<<"The fc1 point is ("<<fcent[0].x<<","<<fcent[0].y<<")"<<endl;
cout<<"The fc2 point is ("<<fcent[1].x<<","<<fcent[1].y<<")"<<endl;
cout<<"The fc3 point is ("<<fcent[2].x<<","<<fcent[2].y<<")"<<endl;
cout<<"The fc4 point is ("<<fcent[3].x<<","<<fcent[3].y<<")"<<endl;
}
