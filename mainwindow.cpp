#include "mainwindow.h"
#include "ui_mainwindow.h"

//#include "taskmanager.h"
//#include "calendar.h"
//#include "eisenhower.h"
#include "pomodoro.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);  // Setup the UI from designer
    setupTabs();        // Call the setupTabs function to initialize the tabs
}

MainWindow::~MainWindow() {
    delete ui;  // Clean up the UI
}

void MainWindow::setupTabs() {
    // Clear any existing tabs in the QTabWidget
    ui->tabWidget->clear();

    // Create an instance of your Pomodoro widget (QWidget)
    Pomodoro *pomodoroTab = new Pomodoro(this);  // Make sure to pass 'this' as parent

    // Add Pomodoro as a tab to the QTabWidget (the one defined in the .ui file)
    ui->tabWidget->addTab(pomodoroTab, "Pomodoro");

    // Uncomment the following lines to add additional tabs
    // tabWidget->addTab(new TaskManager(this), "Task Manager");
    // tabWidget->addTab(new Calendar(this), "Calendar");
    // tabWidget->addTab(new Eisenhower(this), "Eisenhower Matrix");
}
