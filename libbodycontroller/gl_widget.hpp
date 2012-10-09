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

    signals:
      void xRotationChanged(int angle);
      void yRotationChanged(int angle);
      void zRotationChanged(int angle);

    protected:
      void initializeGL();
      void paintGL();
      void resizeGL(int width, int height);
      void mousePressEvent(QMouseEvent *event);
      void mouseMoveEvent(QMouseEvent *event);

    private:
      GLWidget (const GLWidget& original);
      GLWidget& operator= (const GLWidget& rhs);
      int xRot;
      int yRot;
      int zRot;
      QPoint lastPos;
      QColor qtGreen;
      QColor qtPurple;
  };


};


#endif /* LIBBODYCONTROLLER_GL_WIDGET_HPP */

