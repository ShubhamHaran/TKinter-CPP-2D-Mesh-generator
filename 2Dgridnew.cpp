#include <iostream>
#include<stdlib.h>
#include<cstring>
#include<cmath>
using namespace std;
static int N;
static int M;
static float xdim;
static float ydim;
static int pointx;
static int pointy;
struct point{
float x;
float y;
};
struct face{
point findex[2];
long area;
point lr[2];
point face_centroid;
point face_normal;
int type_of_face=0;
public:
void set_type_of_face(){
if(this->findex[1].x==N||this->findex[0].x==N) this->type_of_face=4;
else if(this->findex[1].y==M||this->findex[0].y==M) this->type_of_face=3;
else if(this->findex[1].y==0||this->findex[0].y==0) this->type_of_face=2;
if(this->findex[0].x==0) this->type_of_face=1;
}
void get_type_of_face(){
if(this->type_of_face==0) cout<<"Face type is field");
if(this->type_of_face==1) cout<<"Face type is wall");
if(this->type_of_face==2) cout<<"Face type is inflow");
if(this->type_of_face==3) cout<<"Face type is far field");
if(this->type_of_face==4) cout<<"Face type is outflow");

}
};
struct cell{
point index;
point p[4];
int number_of_neighbours=4;
vector<point>neighbours;
int type_of_cell=0;
point centroid;
struct face faces[4];

public:

void get_face_area(){
for(int i=0;i<4;i++)
 cout<<"The face area of face "<<i+1<<"is: "<<this->faces[i].area<<endl;}
void get_face_index(){
for(int i=0;i<4;i++) cout<<"The nodes across the face is : ("<<this->faces[i].findex[0].x<<","<<this->faces[i].findex[0].y<<")  and"<<this->faces[i].findex[1].x<<","<<this->faces[i].findex[1].y<<endl;}
void getindex(){
cout<<"The cell index is: ("<<this->index.x<<","<<this->index.y<<" )"<<endl;
}
void getpoints(){
cout<<"The points are : "<<endl;
for(int i=0;i<4;i++)
cout<<"("<<this->p[i].x<<","<<this->p[i].y<<")"<<endl;
}

void get_face_centroid(){
cout<<"The face centroids are : "<<endl;
for(int i=0;i<4;i++)
cout<<"("<<this->faces[i].face_centroid.x<<","<<this->faces[i].face_centroid.y<<")"<<endl;}

void getcentroid(){
cout<<"The cell centroid is: ("<<this->centroid.x<<","<<this->centroid.y<<" )"<<endl;}
void get_face_normal(){
cout<<"The face normals are : "<<endl;
for(int i=0;i<4;i++)
cout<<this->faces[i].face_normal.x<<"i+"<<this->faces[i].face_normal.y<<"j"<<endl;}

void set_type_of_cell(){
for(int i=0;i<4;i++) {if(this->faces[i].type_of_face!=0) {this->type_of_cell=1; break; }}

}
void setnnum(){
this->number_of_neighbours=neighbours.size();
set_type_of_cell();
}

void set_face_normals(){
int i;
float dy,dx,l;
for(i=1;i<=3;i++){
this->faces[i-1].findex[0]=p[i-1];
this->faces[i-1].findex[1]=p[i];
dy=this->p[i].x-this->p[i-1].x;
dx=this->p[i].y-this->p[i-1].y;
l=sqrt(pow(dy,2)+pow(dx,2));
this->faces[i-1].area=l;
this->faces[i-1].face_normal.x=dy/l;
this->faces[i-1].face_normal.y=dx/l;
faces[i-1].set_type_of_face();
}
dy=this->p[0].x-this->p[3].x;
dx=this->p[0].y-this->p[3].y;
l=sqrt(pow(dy,2)+pow(dx,2));
this->faces[3].face_normal.x=dy/l;
this->faces[3].face_normal.y=dx/l;
this->faces[3].area=l;
this->faces[3].findex[0]=p[3];
this->faces[3].findex[1]=p[0];
faces[3]set_type_of_face();
}
void set_face_centroid(){
this->faces[0].face_centroid.x=(this->p[0].x+this->p[1].x)/2;
this->faces[0].face_centroid.y=(this->p[0].y+this->p[1].y)/2;
this->faces[1].face_centroid.x=(this->p[1].x+this->p[2].x)/2;
this->faces[1].face_centroid.y=(this->p[1].y+this->p[2].y)/2;
this->faces[2].face_centroid.x=(this->p[2].x+this->p[3].x)/2;
this->faces[2].face_centroid.y=(this->p[3].y+this->p[2].y)/2;
this->faces[3].face_centroid.x=(this->p[0].x+this->p[3].x)/2;
this->faces[3].face_centroid.y=(this->p[0].y+this->p[0].y)/2;
set_face_normals();
}

void setcentroid(){
this->centroid.x=(p[0].x+p[1].x+p[2].x+p[3].x)/4;
this->centroid.y=(p[0].y+p[1].y+p[2].y+p[3].y)/4;
set_face_centroid();
}

void setp(){
this->p[0].x=this->index.x*xdim;
this->p[0].y=this->index.y*ydim;
this->p[1].x=this->index.x*xdim+xdim;
this->p[1].y=this->index.y*ydim;
this->p[2].x=this->index.x*xdim+xdim;;
this->p[2].y=this->index.y*ydim+ydim;
this->p[3].x=this->index.x*xdim;
this->p[3].y=this->index.y*ydim+ydim;
setcentroid();
setnnum();
}

void setindex(float x,float y){
this->index.x=x;
this->index.y=y;
setp();}

};
int main(){
cout<<"Enter dimension along x"<<endl;
cin>>N;
cout<<"Enter dimension along y"<<endl;
cin>>M;
cout<<"Enter number of points along x"<<endl;
cin>>pointx;
cout<<"Enter number of points along y"<<endl;
cin>>pointy;
xdim=N/(pointx-1);
ydim=M/(pointy-1);
struct cell *mesh=(struct cell*)malloc((pointx-2)*(pointy-2)*sizeof(struct cell));
for(int x=0;x<pointx-2;x++) for(int y=0;y<pointy-2;y++) mesh[x*(pointx-2)+y].setindex(x,y);
vector<vector<point>>adjacency(pointx*pointy);
int c=0;
struct point tmp;
for(int x=0;x<pointx-2;x++){ for(int y=0;pointy-2;y++) {
for(int i=0;i<4;i++){
c=mesh[x*(pointx-2)+y].p[i].x*pointx+mesh[x*(pointx-2)+y].p[i].y;
tmp.x=x;
tmp.y=y;
adjacency[c].push_back(temp);
}
}}
}
