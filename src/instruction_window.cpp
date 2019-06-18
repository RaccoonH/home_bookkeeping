#include "instruction_window.h"

InstructionWindow::InstructionWindow(QWidget *parent) :
    QDialog(parent)
{
    resize(400, 300);
    setWindowTitle(QApplication::translate("InstructionWindow", "Инструкция", nullptr));
}

InstructionWindow::~InstructionWindow()
{
    this->close();
}
