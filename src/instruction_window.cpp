#include "instruction_window.h"
#include "ui_instruction_window.h"

InstructionWindow::InstructionWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InstructionWindow)
{
    ui->setupUi(this);
}

InstructionWindow::~InstructionWindow()
{
    delete ui;
}
