#ifndef LIBBODYCONTROLLER_GUI_MAIN_WINDOW_HPP
#define LIBBODYCONTROLLER_GUI_MAIN_WINDOW_HPP 1

#include <QtGui>
#include <QGraphicsScene>
#include <libbodycontroller/common.hpp>
#include <libbodycontroller/ui_main_window.h>
#include <libbodycontroller/gl_widget.hpp>
#include <boost/filesystem.hpp>

namespace bfs=boost::filesystem;

namespace bodycontroller {

  class GUIMainWindow : public QWidget, private Ui::SimpleUI {
    Q_OBJECT 

    public:
      typedef boost::shared_ptr<GUIMainWindow> Ptr;
      GUIMainWindow ();
      virtual ~GUIMainWindow();

    private slots:
      void on_reset_btn_clicked();

    signals:
      void valueChanged(int newValue);

    protected:
      void closeEvent(QCloseEvent *event);
    private:
      GUIMainWindow (const GUIMainWindow& original);
      GUIMainWindow& operator= (const GUIMainWindow& rhs);
      Ui::SimpleUI* _ui;
      GLWidget* _gl_widget;
  };

};


#endif /* LIBBODYCONTROLLER_GUI_MAIN_WINDOW_HPP */

