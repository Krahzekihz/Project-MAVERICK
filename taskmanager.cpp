#include "taskmanager.h"
#include "ui_taskmanager.h"
#include <QDate>
#include <QListWidgetItem>
#include <QMessageBox>

TaskManager::TaskManager(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TaskManager)
{
    ui->setupUi(this);

    // Set today’s date on label
    ui->labelToday->setText("Today: " + QDate::currentDate().toString("dddd, MMMM d, yyyy"));

    // Connect buttons
    connect(ui->pushButton, &QPushButton::clicked, this, &TaskManager::addTask);
    connect(ui->removeButton, &QPushButton::clicked, this, &TaskManager::removeTask);

    // Update label when calendar date changes
    connect(ui->calendarWidget, &QCalendarWidget::selectionChanged, this, &TaskManager::updateDateLabel);
}

TaskManager::~TaskManager() {
    delete ui;
}

void TaskManager::addTask() {
    QDate selectedDate = ui->calendarWidget->selectedDate();
    QString taskText = ui->lineEdit->text();
    QString dueText = ui->textEdit->toPlainText();

    if (taskText.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Please enter a task.");
        return;
    }

    TaskData task(selectedDate, taskText, dueText);
    taskList.append(task);

    QString itemText = selectedDate.toString("yyyy-MM-dd") + ": " + taskText;
    if (!dueText.isEmpty()) {
        itemText += " (Due: " + dueText + ")";
    }

    ui->listWidget->addItem(itemText);

    // Clear input fields
    ui->lineEdit->clear();
    ui->textEdit->clear();
}

void TaskManager::removeTask() {
    int row = ui->listWidget->currentRow();
    if (row >= 0 && row < taskList.size()) {
        taskList.removeAt(row);
        delete ui->listWidget->takeItem(row);
    } else {
        QMessageBox::information(this, "Remove Task", "Please select a task to remove.");
    }
}

void TaskManager::updateDateLabel() {
    QDate selectedDate = ui->calendarWidget->selectedDate();
    ui->labelToday->setText("Selected Date: " + selectedDate.toString("dddd, MMMM d, yyyy"));
}
