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
  , _xpos(0)
  , _ypos(0)
  , _xrot(0)
  , _yrot(0)
  , _zrot(0)
  , _zoom(500)
{
}

QSize GLWidget::minimumSizeHint() const
{
  return QSize(640, 480);
}

QSize GLWidget::sizeHint() const
{
  return QSize(640, 480);
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
  if (angle != _xrot) {
    _xrot = angle;
    emit x_rotation_changed(angle);
    updateGL();
  }
}

void GLWidget::setYRotation(int angle)
{
  qNormalizeAngle(angle);
  if (angle != _yrot) {
    _yrot = angle;
    emit y_rotation_changed(angle);
    updateGL();
  }
}

void GLWidget::setZRotation(int angle)
{
  qNormalizeAngle(angle);
  if (angle != _zrot) {
    _zrot = angle;
    emit z_rotation_changed(angle);
    updateGL();
  }
}

void GLWidget::reset_camera() {
  _xpos=0;
  _ypos=0;
  _xrot=0;
  _yrot=0;
  _zrot=0;
  _zoom=500;
  update_projection_matrix();
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
  //static GLfloat lightPosition[4] = { 15, 15.0, 15.0, 10.0 };
  //glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
}

void GLWidget::draw_cube(float x, float y, float z) {
  glPushMatrix();
  glTranslatef(x, y, z); 
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
  glPopMatrix();
}

/**
 * TODO: Refactor so that single joints can be updated. 
 * for now: Just specify the coordinates of the head, draw mockup.
 */
void GLWidget::draw_man(float x, float y, float z) {
  glPushMatrix();
  glTranslatef(x, y, z); 
  // we're now back to (0,0,0) - so just draw cubes 
  // in absolute coordinates.
  // define layers.
  float xl=-3;
  float xc=0;
  float xr=3;
  float yhead=15;
  float yshoulder=12;
  float yelbow=9;
  float yhand=6;
  float yknee=3;
  float yfoot=0;

  draw_cube(xc,yhead,0);
  draw_cube(xc,yshoulder,0);
  draw_cube(xl,yelbow,0);
  draw_cube(xr,yelbow,0);
  draw_cube(xl,yhand,0);
  draw_cube(xr,yhand,0);
  draw_cube(xc,yhand,0);
  draw_cube(xl,yknee,0);
  draw_cube(xr,yknee,0);
  draw_cube(xl,yfoot,0);
  draw_cube(xr,yfoot,0);

  glLineWidth (8.0);
  glColor3f (1,1,1); 
  glBegin(GL_LINES);
  glVertex3f (xc,yhead,0);
  glVertex3f (xc,yshoulder,0);
  glVertex3f (xc,yshoulder,0);
  glVertex3f (xl,yelbow,0);
  glVertex3f (xc,yshoulder,0);
  glVertex3f (xr,yelbow,0);
  glVertex3f (xc,yshoulder,0);
  glVertex3f (xc,yhand,0);
  glVertex3f (xr,yelbow,0);
  glVertex3f (xr,yhand,0);
  glVertex3f (xl,yelbow,0);
  glVertex3f (xl,yhand,0);
  glVertex3f (xc,yhand,0);
  glVertex3f (xl,yknee,0);
  glVertex3f (xc,yhand,0);
  glVertex3f (xr,yknee,0);
  glVertex3f (xr,yknee,0);
  glVertex3f (xr,yfoot,0);
  glVertex3f (xl,yknee,0);
  glVertex3f (xl,yfoot,0);
  glEnd();

  glPopMatrix();
}

void GLWidget::draw_axes(void) {
  glPushMatrix ();
  glLineWidth (4.0);

  glBegin (GL_LINES);
  glColor3f (1,0,0); // X axis is red.
  glVertex3f (0,0,0);
  glVertex3f (10,0,0 ); 
  glColor3f (0,1,0); // Y axis is green.
  glVertex3f (0,0,0);
  glVertex3f (0,10,0);
  glColor3f (0,0,1); // z axis is blue.
  glVertex3f (0,0,0);
  glVertex3f (0,0,10); 
  glEnd();
  
  glPopMatrix ();
}

void GLWidget::paintGL()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity(); // Reset current modelview matrix
  glRotatef(_xrot / 16.0, 1.0, 0.0, 0.0);
  glRotatef(_yrot / 16.0, 0.0, 1.0, 0.0);
  glRotatef(_zrot / 16.0, 0.0, 0.0, 1.0);
  draw_axes();

  // Draw cube in the right side of the window
  // next code will draw a line at starting and ending coordinates specified by glVertex3f
//  glBegin(GL_LINES);
//  glColor3f(1.0f,1.0f,1.0f);	// Color Violet
//  glVertex3f(1.0f, 1.0f, 0.0f); // origin of the line
//  glVertex3f(2.0f, 3.0f, 5.0f); // ending point of the line
//  glEnd( );
 // draw_cube(-1.5f, 0.0, 0.0);
 // draw_cube(1.5f, 0.0, 0.0);
  draw_man(6,2,4);
  draw_man(-6,-2,-4);
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
  glOrtho(-0.1*_zoom, 0.1*_zoom, -0.1*_zoom, 0.1*_zoom, -30.0, 30.0);
  glMatrixMode(GL_MODELVIEW); // Select modelview matrix
  glLoadIdentity(); // Reset modelview matrix
  glTranslatef(0,0,-10);
}

void GLWidget::mousePressEvent(QMouseEvent *event)
{
  lastPos = event->pos();
}

void GLWidget::update_projection_matrix() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-0.1*_zoom, 0.1*_zoom, -0.1*_zoom, 0.1*_zoom, -30.0, 30.0);
    glTranslatef(_xpos,_ypos,-10);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    updateGL();
}

void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
  int dx = event->x() - lastPos.x();
  int dy = event->y() - lastPos.y();
  int dzoom = event->y() - lastPos.y();

  if (event->buttons() & Qt::LeftButton) {
    setXRotation(_xrot + 8 * dy);
    setYRotation(_yrot + 8 * dx);
  } else if (event->buttons() & Qt::MiddleButton) {
    _zoom+=dzoom;
    update_projection_matrix();
  } else if (event->buttons() & Qt::RightButton) {
    _xpos+=(dx*0.1f);
    _ypos-=(dy*0.1f);
    update_projection_matrix();
  }
  lastPos = event->pos();
}
