/********************************************************************************
** Form generated from reading UI file 'taskmanager.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TASKMANAGER_H
#define UI_TASKMANAGER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCalendarWidget>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TaskManager
{
public:
    QCalendarWidget *calendarWidget;
    QLineEdit *lineEdit;
    QTextEdit *textEdit;
    QPushButton *pushButton;
    QListWidget *listWidget;
    QLabel *labelToday;
    QLabel *label_2;
    QLabel *label_3;
    QPushButton *removeButton;

    void setupUi(QWidget *TaskManager)
    {
        if (TaskManager->objectName().isEmpty())
            TaskManager->setObjectName("TaskManager");
        TaskManager->resize(771, 431);
        calendarWidget = new QCalendarWidget(TaskManager);
        calendarWidget->setObjectName("calendarWidget");
        calendarWidget->setGeometry(QRect(0, 60, 391, 371));
        lineEdit = new QLineEdit(TaskManager);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setGeometry(QRect(400, 80, 371, 41));
        textEdit = new QTextEdit(TaskManager);
        textEdit->setObjectName("textEdit");
        textEdit->setGeometry(QRect(400, 150, 371, 61));
        pushButton = new QPushButton(TaskManager);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(400, 220, 111, 51));
        listWidget = new QListWidget(TaskManager);
        listWidget->setObjectName("listWidget");
        listWidget->setGeometry(QRect(420, 280, 311, 141));
        labelToday = new QLabel(TaskManager);
        labelToday->setObjectName("labelToday");
        labelToday->setGeometry(QRect(0, 0, 711, 61));
        label_2 = new QLabel(TaskManager);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(410, 60, 71, 16));
        label_3 = new QLabel(TaskManager);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(410, 122, 71, 20));
        removeButton = new QPushButton(TaskManager);
        removeButton->setObjectName("removeButton");
        removeButton->setGeometry(QRect(630, 220, 121, 51));

        retranslateUi(TaskManager);

        QMetaObject::connectSlotsByName(TaskManager);
    } // setupUi

    void retranslateUi(QWidget *TaskManager)
    {
        TaskManager->setWindowTitle(QCoreApplication::translate("TaskManager", "Form", nullptr));
        lineEdit->setText(QString());
        textEdit->setHtml(QCoreApplication::translate("TaskManager", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Segoe UI'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>", nullptr));
        pushButton->setText(QCoreApplication::translate("TaskManager", "Add Task", nullptr));
        labelToday->setText(QCoreApplication::translate("TaskManager", "TODAY", nullptr));
        label_2->setText(QCoreApplication::translate("TaskManager", "ENTER TASK ", nullptr));
        label_3->setText(QCoreApplication::translate("TaskManager", "ENTER DUE", nullptr));
        removeButton->setText(QCoreApplication::translate("TaskManager", "Remove Task Button", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TaskManager: public Ui_TaskManager {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TASKMANAGER_H
