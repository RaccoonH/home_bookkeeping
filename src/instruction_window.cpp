#include "instruction_window.h"

InstructionWindow::InstructionWindow(QWidget *parent) :
    QDialog(parent)
{
    if (objectName().isEmpty())
        setObjectName(QString::fromUtf8("InstructionWindow"));
    resize(400, 300);
    setWindowTitle(QApplication::translate("InstructionWindow", "Инструкция", nullptr));
}

InstructionWindow::~InstructionWindow()
{
    this->close();
}
