#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "taskmanager.h"
#include "calendar.h"
#include "eisenhower.h"
#include "pomodoro.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    setupTabs();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::setupTabs() {
    tabWidget = new QTabWidget(this);
    setCentralWidget(tabWidget);

    tabWidget->addTab(new TaskManager(this), "Task Manager");
    tabWidget->addTab(new Calendar(this), "Calendar");
    tabWidget->addTab(new Eisenhower(this), "Eisenhower Matrix");
    tabWidget->addTab(new Pomodoro(this), "Pomodoro Timer");
}
