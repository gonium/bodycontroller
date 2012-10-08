#include "gui_main_window.hpp"
#include <iostream>
#include <fstream>

using namespace bodycontroller;

GUIMainWindow::GUIMainWindow(
  ) : _ui(new Ui::SimpleUI)
{
  _ui->setupUi(this);
  //// connect the slider and the spinbox: reflects the frame number
  //connect(_ui->frame_slider, SIGNAL(valueChanged(int)),
  //        this, SLOT(draw_frame(int)));
  //connect(this, SIGNAL(valueChanged(int)),
  //        _ui->frame_slider, SLOT(setValue(int)));
  //connect(_ui->frame_spinbox, SIGNAL(valueChanged(int)),
  //        this, SLOT(draw_frame(int)));
  //connect(this, SIGNAL(valueChanged(int)),
  //        _ui->frame_spinbox, SLOT(setValue(int)));
  //// connect the timer: set to framerate
  //connect(_timer, SIGNAL(timeout()), this, SLOT(draw_next_frame()));
}

GUIMainWindow::~GUIMainWindow() {
  delete _ui;
}

void GUIMainWindow::on_testbutton_clicked() {
  std::cout << "TEST" << std::endl;
}

void GUIMainWindow::closeEvent(QCloseEvent *event) {
  std::cout << "Goodbye." << std::endl;
}
