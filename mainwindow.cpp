#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QDate>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    updateCurrentDateLabel();
    connectSignals();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::updateCurrentDateLabel() {
    QDate currentDate = QDate::currentDate();
    ui->label->setText("Today: " + currentDate.toString("dd MMMM yyyy"));
}

void MainWindow::connectSignals() {
    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::onSaveTaskClicked);
    connect(ui->pushButton_2, &QPushButton::clicked, this, &MainWindow::onViewTaskClicked);
}

void MainWindow::onSaveTaskClicked() {
    QDate selectedDate = ui->calendarWidget->selectedDate();
    QString task = ui->textEdit->toPlainText();
    QString deadline = ui->lineEdit->text();

    taskManager.addTask(selectedDate, task, deadline);

    QMessageBox::information(this, "Saved", "Task saved for " + selectedDate.toString("dd MMM yyyy"));
}

void MainWindow::onViewTaskClicked() {
    QDate selectedDate = ui->calendarWidget->selectedDate();
    QString task = taskManager.getTask(selectedDate);

    QMessageBox::information(this, "Task for " + selectedDate.toString("dd MMM yyyy"), task);
}
