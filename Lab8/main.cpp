#include<stdio.h>
#include<GL/gl.h>
#include<GL/glu.h>
#include<GL/glut.h>

float x1, y1, x2, y2;
float xmin = 50, ymin = 50, xmax = 100, ymax = 100;
const int RIGHT = 8, LEFT = 2, TOP = 4, BOTTOM = 1;
int code0, code1, codeout;


int compute(float x, float y){
    int code = 0;

    if(x < xmin)
        code |= LEFT;
    else if(x > xmax)
        code |= RIGHT;

    if(y < ymin)
        code |= BOTTOM;
    else if(y > ymax)
        code |= TOP;

    return code;
}

void cohen(float x1, float y1, float x2, float y2){
    bool done = false, accept = false;
    code0 = compute(x1, y1);
    code1 = compute(x2, y2);
    float x, y;

    do{
        //printf("%d %d\n", code0, code1);
        if((code0 | code1) == 0){
            done = true;
            accept = true;
        }
        else if(code0 & code1)
            done = true;
        else{
            if(code0)
                codeout = code0;
            else
                codeout = code0 ? code0 : code1;
                if(codeout & BOTTOM){
                    y = ymin;
                    x = x1 + ((x2 - x1) / (y2 - y1)) * (ymin - y1);
                }
                else if(codeout & TOP){
                    y = ymax;
                    x = x1 + ((x2 - x1) / (y2 - y1)) * (ymax - y1);
                }
                else if(codeout & LEFT){
                    x = xmin;
                    y = y1 + ((y2 - y1) / (x2 - x1)) * (xmin - x1);
                }
                else{
                    x = xmax;
                    y = y1 + ((y2 - y1) / (x2 - x1)) * (xmax - x1);
                }
                if(codeout == code0){
                    x1 = x;
                    y1 = y;
                    code0 = compute(x1, y1);
                }
                if(codeout == code1){
                    x2 = x;
                    y2 = y;
                    code1 = compute(x2, y2);
                }
        }
    }while(!done);
    if(accept){
        glTranslatef(100,100,0);
        glColor3f(1.0,0.0,0.0);
        glBegin(GL_LINE_LOOP);
            glVertex2i(xmin, ymin);
            glVertex2i(xmax, ymin);
            glVertex2i(xmax, ymax);
            glVertex2i(xmin, ymax);
        glEnd();

        glColor3f(0.0,1.0,0.0);
            glBegin(GL_LINES);
            glVertex2i(x1, y1);
            glVertex2i(x2, y2);
        glEnd();
    }
}

void display(){
    glClearColor(1,1,1,1);
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0,0.0,0.0);
    glBegin(GL_LINE_LOOP);
        glVertex2i(xmin, ymin);
        glVertex2i(xmax, ymin);
        glVertex2i(xmax, ymax);
        glVertex2i(xmin, ymax);
    glEnd();

    glColor3f(0.0,0.0,1.0);
        glBegin(GL_LINES);
        glVertex2i(x1, y1);
        glVertex2i(x2, y2);
    glEnd();

    cohen(x1, y1, x2, y2);

    glFlush();

}

void init(){
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, 500, 0, 500);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv){
    printf("Enter the line values\n");
    scanf("%f %f %f %f", &x1, &y1, &x2, &y2);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Cohen Sutherland and Drawing Algorithm");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
