#include "gl_widget.hpp"
#include <QtGui>
#include <QtOpenGL>
#include <math.h>

#ifndef GL_MULTISAMPLE
#define GL_MULTISAMPLE  0x809D
#endif

using namespace bodycontroller;

GLWidget::GLWidget(QWidget *parent)
  : QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
{
  xRot = 0;
  yRot = 0;
  zRot = 0;
  qtGreen = QColor::fromCmykF(0.40, 0.0, 1.0, 0.0);
  qtPurple = QColor::fromCmykF(0.39, 0.39, 0.0, 0.0);
}

QSize GLWidget::minimumSizeHint() const
{
  return QSize(300, 300);
}

QSize GLWidget::sizeHint() const
{
  return QSize(400, 400);
}

static void qNormalizeAngle(int &angle)
{
  while (angle < 0)
    angle += 360 * 16;
  while (angle > 360 * 16)
    angle -= 360 * 16;
}

void GLWidget::setXRotation(int angle)
{
  qNormalizeAngle(angle);
  if (angle != xRot) {
    xRot = angle;
    emit xRotationChanged(angle);
    updateGL();
  }
}

void GLWidget::setYRotation(int angle)
{
  qNormalizeAngle(angle);
  if (angle != yRot) {
    yRot = angle;
    emit yRotationChanged(angle);
    updateGL();
  }
}

void GLWidget::setZRotation(int angle)
{
  qNormalizeAngle(angle);
  if (angle != zRot) {
    zRot = angle;
    emit zRotationChanged(angle);
    updateGL();
  }
}

void GLWidget::initializeGL()
{
  qglClearColor(Qt::black);

  glClearDepth(1.0f); // Depth buffer setup
  glEnable(GL_DEPTH_TEST); // Enable depth testing
  glDepthFunc(GL_LEQUAL); // Set type of depth test
  glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); // Really nice perspective calculations

  //glEnable(GL_CULL_FACE);
  //glShadeModel(GL_SMOOTH);
  //glEnable(GL_LIGHTING);
  //glEnable(GL_LIGHT0);
  //glEnable(GL_MULTISAMPLE);
  //static GLfloat lightPosition[4] = { 5, 5.0, 7.0, 1.0 };
  //glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
}

void GLWidget::paintGL()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity(); // Reset current modelview matrix
  glRotatef(xRot / 16.0, 1.0, 0.0, 0.0);
  glRotatef(yRot / 16.0, 0.0, 1.0, 0.0);
  glRotatef(zRot / 16.0, 0.0, 0.0, 1.0);

 // Draw cube in the right side of the window
  glTranslatef(0.0f, 0.0f, -7.0f); // Move 7 units into the screen



  //logo->draw();
  // TODO: Draw something here.
  // gluLookAt(0,0,-10,0.5,0.5,0,0,1,0);
  //glClear(GL_COLOR_BUFFER_BIT);
  //glColor3f(1,0,0);
  //glBegin(GL_POLYGON);
  //glVertex3f(0,0,0);
  //glVertex3f(0,1,0);
  //glVertex3f(1,1,0);
  //glVertex3f(1,0,0);
  //glEnd();

  glBegin(GL_QUADS);		// Draw The Cube Using quads
  glColor3f(0.0f,1.0f,0.0f);	// Color Blue
  glVertex3f( 1.0f, 1.0f,-1.0f);	// Top Right Of The Quad (Top)
  glVertex3f(-1.0f, 1.0f,-1.0f);	// Top Left Of The Quad (Top)
  glVertex3f(-1.0f, 1.0f, 1.0f);	// Bottom Left Of The Quad (Top)
  glVertex3f( 1.0f, 1.0f, 1.0f);	// Bottom Right Of The Quad (Top)
  glColor3f(1.0f,0.5f,0.0f);	// Color Orange
  glVertex3f( 1.0f,-1.0f, 1.0f);	// Top Right Of The Quad (Bottom)
  glVertex3f(-1.0f,-1.0f, 1.0f);	// Top Left Of The Quad (Bottom)
  glVertex3f(-1.0f,-1.0f,-1.0f);	// Bottom Left Of The Quad (Bottom)
  glVertex3f( 1.0f,-1.0f,-1.0f);	// Bottom Right Of The Quad (Bottom)
  glColor3f(1.0f,0.0f,0.0f);	// Color Red	
  glVertex3f( 1.0f, 1.0f, 1.0f);	// Top Right Of The Quad (Front)
  glVertex3f(-1.0f, 1.0f, 1.0f);	// Top Left Of The Quad (Front)
  glVertex3f(-1.0f,-1.0f, 1.0f);	// Bottom Left Of The Quad (Front)
  glVertex3f( 1.0f,-1.0f, 1.0f);	// Bottom Right Of The Quad (Front)
  glColor3f(1.0f,1.0f,0.0f);	// Color Yellow
  glVertex3f( 1.0f,-1.0f,-1.0f);	// Top Right Of The Quad (Back)
  glVertex3f(-1.0f,-1.0f,-1.0f);	// Top Left Of The Quad (Back)
  glVertex3f(-1.0f, 1.0f,-1.0f);	// Bottom Left Of The Quad (Back)
  glVertex3f( 1.0f, 1.0f,-1.0f);	// Bottom Right Of The Quad (Back)
  glColor3f(0.0f,0.0f,1.0f);	// Color Blue
  glVertex3f(-1.0f, 1.0f, 1.0f);	// Top Right Of The Quad (Left)
  glVertex3f(-1.0f, 1.0f,-1.0f);	// Top Left Of The Quad (Left)
  glVertex3f(-1.0f,-1.0f,-1.0f);	// Bottom Left Of The Quad (Left)
  glVertex3f(-1.0f,-1.0f, 1.0f);	// Bottom Right Of The Quad (Left)
  glColor3f(1.0f,0.0f,1.0f);	// Color Violet
  glVertex3f( 1.0f, 1.0f,-1.0f);	// Top Right Of The Quad (Right)
  glVertex3f( 1.0f, 1.0f, 1.0f);	// Top Left Of The Quad (Right)
  glVertex3f( 1.0f,-1.0f, 1.0f);	// Bottom Left Of The Quad (Right)
  glVertex3f( 1.0f,-1.0f,-1.0f);	// Bottom Right Of The Quad (Right)
  glEnd();			// End Drawing The Cube
}

void GLWidget::resizeGL(int width, int height)
{
//  int side = qMin(width, height);
//  glViewport((width - side) / 2, (height - side) / 2, side, side);
//
//  glMatrixMode(GL_PROJECTION);
//  glLoadIdentity();
//#ifdef QT_OPENGL_ES_1
//  glOrthof(-0.5, +0.5, -0.5, +0.5, 4.0, 15.0);
//#else
//  glOrtho(-0.5, +0.5, -0.5, +0.5, 4.0, 15.0);
//#endif
//  glMatrixMode(GL_MODELVIEW);
//  glLoadIdentity();

  // Prevent divide by zero (in the gluPerspective call)
  if (height == 0)
    height = 1;

  glViewport(0, 0, width, height); // Reset current viewport

  glMatrixMode(GL_PROJECTION); // Select projection matrix
  glLoadIdentity(); // Reset projection matrix

  glOrtho(-5, +5, -5, +5, 4.0, 15.0);
  //gluLookAt(30, 30, 30, 0, 0, 0, 0, 1, 0);
  //gluPerspective(45.0f, static_cast<GLfloat>(width)/height, 0.1f, 100.0f); // Calculate aspect ratio

  glMatrixMode(GL_MODELVIEW); // Select modelview matrix
  glLoadIdentity(); // Reset modelview matrix
}

void GLWidget::mousePressEvent(QMouseEvent *event)
{
  lastPos = event->pos();
}

void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
  int dx = event->x() - lastPos.x();
  int dy = event->y() - lastPos.y();

  if (event->buttons() & Qt::LeftButton) {
    setXRotation(xRot + 8 * dy);
    setYRotation(yRot + 8 * dx);
  } else if (event->buttons() & Qt::MiddleButton) {
    setZRotation(zRot + 8 * dx);
  } else if (event->buttons() & Qt::RightButton) {
    setXRotation(xRot + 8 * dy);
    setZRotation(zRot + 8 * dx);
  }
  lastPos = event->pos();
}
