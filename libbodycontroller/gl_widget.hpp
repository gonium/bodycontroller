#ifndef LIBBODYCONTROLLER_GL_WIDGET_HPP
#define LIBBODYCONTROLLER_GL_WIDGET_HPP 1

#include <libbodycontroller/common.hpp>
#include <QGLWidget>

namespace bodycontroller {

  class GLWidget : public QGLWidget {
    Q_OBJECT

    public:
      typedef boost::shared_ptr<GLWidget> Ptr;
      GLWidget (QWidget* parent = 0);
      virtual ~GLWidget() {};
      QSize minimumSizeHint() const;
      QSize sizeHint() const;

    public slots:
      void setXRotation(int angle);
      void setYRotation(int angle);
      void setZRotation(int angle);
      void reset_camera();

    signals:
      void x_rotation_changed(int angle);
      void y_rotation_changed(int angle);
      void z_rotation_changed(int angle);

    protected:
      void initializeGL();
      void paintGL();
      void resizeGL(int width, int height);
      void mousePressEvent(QMouseEvent *event);
      void mouseMoveEvent(QMouseEvent *event);

    private:
      GLWidget (const GLWidget& original);
      GLWidget& operator= (const GLWidget& rhs);
      void draw_cube(float x, float y, float z);
      void draw_man(float x, float y, float z);
      void draw_axes(void);
      void update_projection_matrix();
      int _xpos;
      int _ypos;
      int _xrot;
      int _yrot;
      int _zrot;
      int _zoom;
      QPoint lastPos;
  };


};


#endif /* LIBBODYCONTROLLER_GL_WIDGET_HPP */

