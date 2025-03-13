#include "mainwindow.h"
#include "database.h"
#include "ui_mainwindow.h"
#include <QMessageBox>


//#include "taskmanager.h"
//#include "calendar.h"
//include "eisenhower.h"
#include "pomodoro.h"

Database db;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);  // Setup the UI from designer

    if (!db.connectDatabase()) {
        QMessageBox::critical(this, "Database Error", "Failed to connect to the database.");
    }
    setupTabs();        // Call the setupTabs function to initialize the tabs

}

MainWindow::~MainWindow() {
    delete ui;  // Clean up the UI
}

void MainWindow::setupTabs() {
    // Clear any existing tabs in the QTabWidget
    ui->tabWidget->clear();

    // Create an instance of your Pomodoro widget (QWidget)
    Pomodoro *pomodoroTab = new Pomodoro(&db, this);    //Eisenhower *eisenhowerMatrix = new Eisenhower(this);
    // Add Pomodoro as a tab to the QTabWidget (the one defined in the .ui file)
    ui->tabWidget->addTab(pomodoroTab, "Pomodoro");
    //ui->tabWidget->addTab(eisenhowerMatrix, "Eisenhower Matrix");
    // Uncomment the following lines to add additional tabs
    // tabWidget->addTab(new TaskManager(this), "Task Manager");
    // tabWidget->addTab(new Calendar(this), "Calendar");
    // tabWidget->addTab(new Eisenhower(this), "Eisenhower Matrix");
}
