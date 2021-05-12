#include<GL/gl.h>
#include<GL/glu.h>
#include<GL/glut.h>
#include<stdio.h>
int x1,y1,x2,y2;
void pixel(int x,int y)
{
    glColor3f(1,0,0);
    glBegin(GL_POINTS);
    glVertex2i(x,y);
    glEnd();
}
void line (int x1 , int y1 , int x2  , int y2)
{
    int dx , dy , dpos , dneg , incx , incy , x , y , de , i ;
    dx = x2 - x1;
    dy = y2 - y1;
    if(dx < 0)
        dx = dx * -1;
    if(dy < 0)
        dy = dy * -1;

    incx = 1;
    incy = 1;
    if(x1 > x2)
        incx = -1;
    if(y1 > y2)
        incy = -1 ;
    x = x1;
    y = y1;
    pixel(x, y);
    if(dx > dy){
        dpos = 2 * dy - 2 * dx;
        dneg = 2 * dy;
        de = 2 * dy - dx;
        for(i = 0; i < dx; i++){
            if(de < 0){
                x = x + incx;
                pixel(x, y);
                de = de + dneg;
            }
            else
            {
                x = x + incx ;
                y = y + incy ;
                pixel(x, y);
                de= de + dpos ;
            }
        }
    }
    else{
        dpos = 2 * dx - 2 * dy;
        dneg = 2 * dx;
        de = 2 * dx - dy;
        for(i = 0 ; i < dy ; i++){
            if(de < 0){
                y = y + incy;
                pixel(x, y);
                de = de + dneg;
            }
            else{
                x = x + incx ;
                y = y + incy ;
                pixel(x, y);
                de= de + dpos ;
            }
        }

    }
}
void disp()
{
    glClearColor(1,1,1,1);
    glClear(GL_COLOR_BUFFER_BIT);
    line(x1,y1, x2,y2);
    glColor3f(0,0,1);
    glPointSize(5);
    glBegin(GL_POINTS);
    glVertex2f(x1,y1);
    glVertex2f(x2,y2);
    glEnd();
	glFlush();
}

void init()
{
    glMatrixMode(GL_PROJECTION);
	gluOrtho2D(-500,500,-500,500);
	glMatrixMode(GL_MODELVIEW);
}

int main(int argc,char **argv)
{
	printf("Enter (x1,y1,x2,y2): ");
	scanf("%d%d%d%d",&x1,&y1,&x2,&y2);

	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);

    glutInitWindowSize(500,500);
	glutInitWindowPosition(0,0);
	glutCreateWindow("Bresenham's Algorithm");

	glutDisplayFunc(disp);
	init();

	glutMainLoop();
}
