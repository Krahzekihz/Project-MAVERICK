/********************************************************************************
** Form generated from reading UI file 'dialog.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_H
#define UI_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCalendarWidget>
#include <QtWidgets/QDateTimeEdit>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QDialogButtonBox *buttonBox;
    QCalendarWidget *calendarWidget;
    QDateTimeEdit *dateTimeEdit;
    QListWidget *listWidget;
    QPushButton *addTaskButton;
    QPushButton *setReminderButton;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName("Dialog");
        Dialog->resize(557, 300);
        buttonBox = new QDialogButtonBox(Dialog);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setGeometry(QRect(200, 220, 341, 32));
        buttonBox->setOrientation(Qt::Orientation::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::StandardButton::Cancel|QDialogButtonBox::StandardButton::Ok);
        calendarWidget = new QCalendarWidget(Dialog);
        calendarWidget->setObjectName("calendarWidget");
        calendarWidget->setGeometry(QRect(0, 0, 200, 117));
        dateTimeEdit = new QDateTimeEdit(Dialog);
        dateTimeEdit->setObjectName("dateTimeEdit");
        dateTimeEdit->setGeometry(QRect(0, 120, 201, 22));
        listWidget = new QListWidget(Dialog);
        listWidget->setObjectName("listWidget");
        listWidget->setGeometry(QRect(200, 0, 221, 151));
        addTaskButton = new QPushButton(Dialog);
        addTaskButton->setObjectName("addTaskButton");
        addTaskButton->setGeometry(QRect(30, 200, 80, 18));
        setReminderButton = new QPushButton(Dialog);
        setReminderButton->setObjectName("setReminderButton");
        setReminderButton->setGeometry(QRect(30, 230, 80, 18));

        retranslateUi(Dialog);
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, Dialog, qOverload<>(&QDialog::accept));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, Dialog, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QCoreApplication::translate("Dialog", "Dialog", nullptr));
        addTaskButton->setText(QCoreApplication::translate("Dialog", "Add Task", nullptr));
        setReminderButton->setText(QCoreApplication::translate("Dialog", "Set Reminder", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_H
