#ifndef INSTRUCTIONWINDOW_H
#define INSTRUCTIONWINDOW_H

#include <QDialog>
#include <QApplication>

class InstructionWindow : public QDialog
{
    Q_OBJECT

public:

    explicit InstructionWindow(QWidget *parent = 0);
    ~InstructionWindow();

private:

};

#endif // INSTRUCTIONWINDOW_H
