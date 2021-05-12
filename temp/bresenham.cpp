#include<GL/gl.h>
#include<GL/glu.h>
#include<GL/glut.h>
#include <stdlib.h>
#include<stdio.h>
int a, b, c, d;
void draw_pixel(int x, int y)
{
 glBegin(GL_POINTS);
 glVertex2f(x, y);
 glEnd();
}
void bresenhams(int x1, int y1, int x2, int y2)
{
 int dx=x2-x1, dy=y2-y1;
 if(dx<0) dx=-dx;
 if(dy<0) dy=-dy; int p, pPos, pNeg;
 if(dy<dx)
 {
 p=(2*dy)-dx;
 pNeg=2*dy;
 pPos=2*(dy-dx);
 if(x1>x2){
 int temp;
 temp=x2;
 x2=x1;
 x1=temp;
 temp=y2;
 y2=y1;
 y1=temp;
 }
 int yinc=1;
 if(y2<y1) yinc=-1;
 int x=x1;
 int y=y1;
 draw_pixel(x, y);
 for(int k=0;k<dx;k++){
 x++;
 if(p<0){
 p=p+pNeg;
 }
 else{
 y=y+yinc;
 p=p+pPos; }
 draw_pixel(x, y);
 }
 }
 else
 {
 p=(2*dx)-dy;
 pNeg=2*dx;
 pPos=2*(dx-dy);
 if(y1>y2){
 int temp;
 temp=x2;
 x2=x1;
 x1=temp;
 temp=y2;
 y2=y1;
 y1=temp;
 }
 int xinc=1;
 if(x2<x1) xinc=-1;
 int x=x1;
 int y=y1;
 draw_pixel(x, y);
 for(int k=0;k<dy;k++){
 y++;
 if(p<0){
 p=p+pNeg;
 }
 else{ x=x+xinc;
 p=p+pPos;
 }
 draw_pixel(x, y);
 }
 }
}
void display()
{
 glClearColor(1,1,1,1);
 glClear(GL_COLOR_BUFFER_BIT);
 glColor3f(1,0,0);
 glPointSize(1);
 bresenhams(a,b,c,d);
 glColor3f(0,0,1);
 glPointSize(5);
 glBegin(GL_POINTS);
 glVertex2f(a,b);
 glVertex2f(c,d);
 glEnd();
 glFlush();
}
void init(){
 glMatrixMode(GL_PROJECTION);
 glLoadIdentity();
 gluOrtho2D(0,500,0,500);
 glMatrixMode(GL_MODELVIEW);
}
int main(int argc, char** argv)
{
 printf("Enter the points: (x1 y1 x2 y2)\n");
 scanf("%d%d%d%d", &a, &b, &c, &d);
glutInit(&argc,argv);
glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
 glutInitWindowSize(500,500);
glutInitWindowPosition(200,200);
glutCreateWindow("Bresenham's Line Drawing - Abhishek Datta");
glutDisplayFunc(display);
init();
glutMainLoop();
}
