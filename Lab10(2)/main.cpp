#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<GL/gl.h>
#include<GL/glu.h>
#include<GL/glut.h>

int xStart, yStart, xEnd, yEnd;

int round(float a){
    return int(a + 0.5);
}

void draw_pixel(int x, int y){
    glColor3f(1.0,0.0,0.0);
    glPointSize(1.0);
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

void lineDDA(int x0, int y0, int x1, int y1){
    int dx = x1 - x0, dy = y1 - y0, steps, k;
    float xIncrement, yIncrement, x = x0, y = y0;
    if(fabs(dx) > fabs(dy))
        steps = fabs(dx);
    else
        steps = fabs(dy);
    xIncrement = float(dx) / float(steps);
    yIncrement = float(dy) / float(steps);
    draw_pixel(round(x), round(y));
    for(k = 0; k < steps; k++){
        x += xIncrement;
        y += yIncrement;
        draw_pixel(round(x), round(y));
    }
}

void display(){
    glClearColor(1.0,1.0,1.0,1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    lineDDA(xStart, yStart, xEnd, yEnd);
    glFlush();
}

void init(){
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, 500, 0, 500);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv){
    printf("Enter the starting coordinates of the line\n");
    scanf("%d%d", &xStart, &yStart);
    printf("Enter the ending coordinates of the line\n");
    scanf("%d%d", &xEnd, &yEnd);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("DD Algorithm");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
