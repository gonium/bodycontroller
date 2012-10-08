#ifndef LIBBODYCONTROLLER_GUI_MAIN_WINDOW_HPP
#define LIBBODYCONTROLLER_GUI_MAIN_WINDOW_HPP 1

#include <QtGui>
#include <QGraphicsScene>
#include <libbodycontroller/common.hpp>
#include <libbodycontroller/ui_main_window.h>
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
      void on_testbutton_clicked();

    signals:
      void valueChanged(int newValue);

    protected:
      void closeEvent(QCloseEvent *event);
    private:
      GUIMainWindow (const GUIMainWindow& original);
      GUIMainWindow& operator= (const GUIMainWindow& rhs);
      Ui::SimpleUI* _ui;
  };

};


#endif /* LIBBODYCONTROLLER_GUI_MAIN_WINDOW_HPP */

