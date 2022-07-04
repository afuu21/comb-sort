#include<iostream>
using namespace std;
#include<stdlib.h>
#include<GL/glut.h>
#include<GL/freeglut.h>
#include<math.h>

int n;
char a[100];
int yellow_color[100];
int red_color[100];
GLfloat space;

void RenderString(float x, float y, void* font, char string)
{
	glColor3f(0.0, 0.0, 1.0);
	glRasterPos2f(x, y);
	glutBitmapCharacter(font, string);
}

int index_i = 1, index_j;
char temp = '\0';

void drawer() {
	Sleep(1000);
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	for (int i = 1; i <= n; i++) {
		glColor3f(1.0, 1.0, 1.0);
		if (yellow_color[i - 1])
			glColor3f(0.0, 1.0, 0.0);
		else if (red_color[i - 1])
			glColor3f(1.0, 0.0, 0.0);
		glRectf(space * i - 25, 300, space * i + 25, 400);
		RenderString(space * i - 3, 345, GLUT_BITMAP_TIMES_ROMAN_24, a[i - 1]);
		glColor3f(0.5, 0.5, 0.5);
		glRectf(475, 450, 525, 550);
		glColor3f(0.5, 0, 0.5);
		RenderString(500 - 3, 495, GLUT_BITMAP_TIMES_ROMAN_24, temp);
	}
	glFlush();
}


void combSort() {
	temp = a[index_i];
	index_j = index_i - 1;
	memset(yellow_color, 0, sizeof(yellow_color));
	memset(red_color, 0, sizeof(red_color));
	red_color[index_j + 1] = 1;
	red_color[index_j] = 1;
	while (temp < a[index_j] && index_j >= 0)
		/*To sort elements in descending order, change temp<data[j] to temp>data[j] in above line.*/
	{
		red_color[index_j + 1] = 1;
		red_color[index_j] = 1;
		a[index_j + 1] = a[index_j];
		--index_j;
		drawer();
		memset(red_color, 0, sizeof(red_color));
	}
	yellow_color[index_j + 1] = 1;
	yellow_color[index_i] = 1;
	drawer();
	Sleep(1000);
	a[index_j + 1] = temp;
	index_i += 1;
	if (index_i == n) {
		drawer();
		Sleep(5000);
		exit(0);
	}
}

void display() {
	drawer();
	combSort();
	glutPostRedisplay();
}

void myInit() {
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0, 1000, 0, 700);
}

// Initializes GLUT, the display mode, and main window; registers callbacks;
// enters the main event loop.
int main(int argc, char** argv) {
	cout << "Enter Number of Elements\n";
	cin >> n;
	cout << "Enter Elements\n";
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	space = 1000 / (n + 1.0);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(10, 10);
	glutInitWindowSize(1500, 700);
	glutCreateWindow("Comb Sort");
	glutDisplayFunc(display);
	myInit();
	glutMainLoop();
}
