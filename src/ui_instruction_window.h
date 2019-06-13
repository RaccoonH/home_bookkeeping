/********************************************************************************
** Form generated from reading UI file 'instructionwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INSTRUCTIONWINDOW_H
#define UI_INSTRUCTIONWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>

QT_BEGIN_NAMESPACE

class Ui_InstructionWindow
{
public:

    void setupUi(QDialog *InstructionWindow)
    {
        if (InstructionWindow->objectName().isEmpty())
            InstructionWindow->setObjectName(QString::fromUtf8("InstructionWindow"));
        InstructionWindow->resize(400, 300);

        retranslateUi(InstructionWindow);

        QMetaObject::connectSlotsByName(InstructionWindow);
    } // setupUi

    void retranslateUi(QDialog *InstructionWindow)
    {
        InstructionWindow->setWindowTitle(QApplication::translate("InstructionWindow", "Help", nullptr));
    } // retranslateUi

};

namespace Ui {
    class InstructionWindow: public Ui_InstructionWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INSTRUCTIONWINDOW_H
