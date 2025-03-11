#ifndef NOTES_H
#define NOTES_H

#include <QWidget>

namespace Ui {
class Notes;
}

class Notes : public QWidget
{
    Q_OBJECT

public:
    explicit Notes(QWidget *parent = nullptr);
    ~Notes();
    void exportNotes();
private slots:
    void onBoldClicked();
    void onBulletClicked();
    void onItalicButtonclicked();        // Italics
    void onStrikethroughButtonclicked(); // Strikethrough

private:
    Ui::Notes *ui;
    bool placeholderActive;
};

#endif // NOTES_H
