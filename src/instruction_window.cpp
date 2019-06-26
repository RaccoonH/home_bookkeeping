#include "instruction_window.h"

InstructionWindow::InstructionWindow(QWidget *parent) :
    QDialog(parent)
{
    resize(550,400);
    setWindowTitle(QApplication::translate("InstructionWindow", "Инструкция", nullptr));

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setAlignment(Qt::AlignTop);

    QLabel *headline = new QLabel("Инструкция\n",this);
    QFont headlineFont;
    headlineFont.setPixelSize(20);
    headline->setFont(headlineFont);

    QFont textFont;
    textFont.setPixelSize(15);
    QString text;
    QLabel *textLable = new QLabel(this);
    textLable->setWordWrap(true);
    text += "Программа используется для расчета и отображение предполагаемого остатка денег. Базовые шаги для работы с программой:\n\n";
    text += "1. Выберите месяц используя клавиши в верхней части интерфейса.\n";
    text += "2. Нажмите на день который вы хотите редактировать.\n";
    text += "3. Введите данные в поле Доход и Расход.\n";
    text += "4. Для изменения информации нажмите на Принять, для отмены нажмите на клавишу Отмена.\n";
    textLable->setText(text);
    textLable->setFont(textFont);

    layout->addWidget(headline);
    layout->addWidget(textLable);
}

InstructionWindow::~InstructionWindow()
{
    this->close();
}
