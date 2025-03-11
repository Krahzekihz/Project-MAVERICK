#include "notes.h"
#include "ui_notes.h"
#include <QFileDialog>
#include <QDateTime>
#include <QFile>
#include <QIODevice>
#include <QMessageBox>
#include <QTextStream>


Notes::Notes(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Notes)
    , placeholderActive(true)
{
    ui->setupUi(this);

    // Disable the custom scrollbar completely
    ui->verticalScrollBar->setEnabled(false);
    ui->verticalScrollBar->hide();  // Make it invisible

    // Connect vertical scrollbar to the text area
    ui->scrollArea->verticalScrollBar()->setRange(0, ui->textEdit->verticalScrollBar()->maximum());
    connect(ui->textEdit->verticalScrollBar(), &QScrollBar::valueChanged, ui->scrollArea->verticalScrollBar(), &QScrollBar::setValue);
    connect(ui->scrollArea->verticalScrollBar(), &QScrollBar::valueChanged, ui->textEdit->verticalScrollBar(), &QScrollBar::setValue);


    // Placeholder text setup
    ui->textEdit->setPlaceholderText("Write your notes here...");
    // Enable Word Wrap
    ui->textEdit->setWordWrapMode(QTextOption::WordWrap);

    // Smooth scrolling
    ui->textEdit->verticalScrollBar()->setSingleStep(10); // Adjust speed
    ui->scrollArea->verticalScrollBar()->setSingleStep(10);

    connect(ui->textEdit, &QTextEdit::textChanged, this, [this]() {
        ui->textEdit->verticalScrollBar()->setValue(ui->textEdit->verticalScrollBar()->maximum());
    });

    connect(ui->textEdit, &QTextEdit::textChanged, this, [this]() {
        if (ui->textEdit->toPlainText().isEmpty()) {
            ui->textEdit->setPlaceholderText("Write your notes here...");
            placeholderActive = true;
        } else {
            placeholderActive = false;
        }
    });

    // Connect buttons
    connect(ui->BoldButton, &QPushButton::clicked, this, &Notes::onBoldClicked);
    connect(ui->BulletButton, &QPushButton::clicked, this, &Notes::onBulletClicked);
    // Connect Italics Button
    connect(ui->ItalicButton, &QPushButton::clicked, this, &Notes::onItalicButtonclicked);
    // Connect Strikethrough Button
    connect(ui->StrikethroughButton, &QPushButton::clicked, this, &Notes::onStrikethroughButtonclicked);
    connect(ui->ExportButton, &QPushButton::clicked, this, &Notes::exportNotes);



}

Notes::~Notes()
{
    delete ui;
}

void Notes::onBoldClicked()
{
    QTextCursor cursor = ui->textEdit->textCursor();
    QTextCharFormat format;

    if (cursor.charFormat().fontWeight() == QFont::Bold) {
        format.setFontWeight(QFont::Normal);
    } else {
        format.setFontWeight(QFont::Bold);
    }

    cursor.mergeCharFormat(format);
    ui->textEdit->mergeCurrentCharFormat(format);
}

void Notes::onBulletClicked()
{
    QTextCursor cursor = ui->textEdit->textCursor();

    if (cursor.hasSelection()) {
        QString selectedText = cursor.selectedText(); // Get highlighted text
        QStringList lines = selectedText.split(QChar::ParagraphSeparator); // Split text by lines

        QString result;
        for (const QString &line : lines) {
            if (!line.isEmpty()) {
                result += "• " + line + "\n"; // Add bullet points
            }
        }

        cursor.insertText(result.trimmed()); // Replace selection with bullet points
    }
    else {
        cursor.insertText("• "); // Default action if nothing is selected
    }
}

void Notes::onItalicButtonclicked()
{
    QTextCursor cursor = ui->textEdit->textCursor();
    QTextCharFormat fmt;
    fmt.setFontItalic(!cursor.charFormat().fontItalic()); // Toggle Italics on/off

    if (cursor.hasSelection()) {
        cursor.mergeCharFormat(fmt);
    }
}


void Notes::onStrikethroughButtonclicked()
{
    QTextCursor cursor = ui->textEdit->textCursor();
    QTextCharFormat fmt;
    fmt.setFontStrikeOut(!cursor.charFormat().fontStrikeOut()); // Toggle Strikethrough on/off

    if (cursor.hasSelection()) {
        cursor.mergeCharFormat(fmt);
    }
}


void Notes::exportNotes()
{
    QString filename = QFileDialog::getSaveFileName(this, "Export Notes", "MAVERICK_Session_" + QDateTime::currentDateTime().toString("yyyy-MM-dd_HH-mm") + ".txt", "Text Files (*.txt)");

    if (filename.isEmpty()) {
        qDebug() << "Export cancelled";
        return;
    }

    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Export Failed", "Cannot save file.");
        return;
    }

    QTextStream out(&file);
    out << "MAVERICK SESSION REPORT\n\n";
    out << ui->textEdit->toPlainText();
    file.close();

    QMessageBox::information(this, "Export Success", "Notes exported successfully!");
}

