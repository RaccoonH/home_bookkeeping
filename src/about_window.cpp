#include "about_window.h"

AboutWindow::AboutWindow(QWidget *parent) :
    QDialog(parent)
{
    resize(500,350);
    setWindowTitle(QApplication::translate("AboutWindow", "О программе", nullptr));

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setAlignment(Qt::AlignTop);

    QLabel *headline = new QLabel("Домашняя бухгалтерия\n",this);
    QFont headlineFont;
    headlineFont.setPixelSize(20);
    headline->setFont(headlineFont);

    QFont textFont;
    textFont.setPixelSize(15);
    QString text;
    QLabel *textLable = new QLabel(this);
    textLable->setWordWrap(true);
    text += "Программа для расчета и отображения предполагаемого остатка денег на некоторое время вперед\n\n";
    text += "Разработчик: Андрей Тудунов\n\n";
    text += "Версия 1.0\n\n";
    textLable->setText(text);
    textLable->setFont(textFont);

    layout->addWidget(headline);
    layout->addWidget(textLable);
}


AboutWindow::~AboutWindow()
{
    this->close();
}
