#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    tabWidget = new QTabWidget(this);
    setCentralWidget(tabWidget);

    setupTabs();  // Initialize tabs
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::setupTabs() {
    eisenhowerMatrix = new Eisenhower(this);
    pomodoroTimer = new Pomodoro(this);

    tabWidget->addTab(eisenhowerMatrix, "Eisenhower Matrix");
    tabWidget->addTab(pomodoroTimer, "Pomodoro Timer");
}
