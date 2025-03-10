// MainWindow.cpp

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Connect checkboxes to slots
    connect(ui->checkBox1, &QCheckBox::stateChanged, this, &MainWindow::on_checkBox1_stateChanged);
    connect(ui->checkBox2, &QCheckBox::stateChanged, this, &MainWindow::on_checkBox2_stateChanged);
    connect(ui->checkBox3, &QCheckBox::stateChanged, this, &MainWindow::on_checkBox3_stateChanged);

    // Connect "Mark All as Done" button to the corresponding slot
    connect(ui->markAllButton, &QPushButton::clicked, this, &MainWindow::on_markAllButton_clicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// Handle state change for Task 1 checkbox
void MainWindow::on_checkBox1_stateChanged(int state)
{
    if (state == Qt::Checked)
        qDebug() << "Task 1 checked";
    else
        qDebug() << "Task 1 unchecked";
}

// Handle state change for Task 2 checkbox
void MainWindow::on_checkBox2_stateChanged(int state)
{
    if (state == Qt::Checked)
        qDebug() << "Task 2 checked";
    else
        qDebug() << "Task 2 unchecked";
}

// Handle state change for Task 3 checkbox
void MainWindow::
