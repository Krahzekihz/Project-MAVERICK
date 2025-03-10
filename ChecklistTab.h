// MainWindow.h

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCheckBox>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_checkBox1_stateChanged(int state);
    void on_checkBox2_stateChanged(int state);
    void on_checkBox3_stateChanged(int state);
    void on_markDoneButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
