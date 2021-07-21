#include<stdio.h>
#include<math.h>
#include<GL/gl.h>
#include<GL/glu.h>
#include<GL/glut.h>

int xc, yc, r;

void draw_pixel(int cx, int cy){
    glColor3f(1.0,0.0,0.0);
    glPointSize(2.0);
    glBegin(GL_POINTS);
    glVertex2i(cx, cy);
    glEnd();
}
void plotpixels(int h, int k, int x, int y){
    draw_pixel(x+h, y+k);
    draw_pixel(-x+h, y+k);
    draw_pixel(x+h, -y+k);
    draw_pixel(-x+h, -y+k);
    draw_pixel(y+h, x+k);
    draw_pixel(-y+h, x+k);
    draw_pixel(y+h, -x+k);
    draw_pixel(-y+h, -x+k);
}

void circle_draw(int h, int k, int r)
{
    int d = 1 - r, x = 0, y = r;
    while(y > x){
        plotpixels(h,k,x,y);
        if(d < 0)
            d += 2*x + 3;
        else{
            d += 2*(x-y)+5;
            y--;
        }
        x++;
    }
}
void display(){
    glClearColor(1.0,1.0,1.0,1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    circle_draw(xc,yc,r);
    glFlush();
}

void init(){
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, 500, 0, 500);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv){
    printf("Enter the x and y coordinates of the center\n");
    scanf("%d%d", &xc,&yc);
    printf("Enter the radius of the circle\n");
    scanf("%d",&r);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Circle Program");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
