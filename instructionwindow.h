#ifndef INSTRUCTIONWINDOW_H
#define INSTRUCTIONWINDOW_H

#include <QDialog>

namespace Ui {
class InstructionWindow;
}

class InstructionWindow : public QDialog
{
    Q_OBJECT

public:
    explicit InstructionWindow(QWidget *parent = nullptr);
    ~InstructionWindow();

private:
    Ui::InstructionWindow *ui;
};

#endif // INSTRUCTIONWINDOW_H
