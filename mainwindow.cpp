#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QFileDialog>
#include <QDir>
#include <QTextStream>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->textEdit);
    ui->actionNew->setIcon(QIcon::fromTheme("document-new"));
    ui->actionOpen->setIcon(QIcon::fromTheme("document-open"));
    ui->actionSave->setIcon(QIcon::fromTheme("document-save"));
    ui->actionSave_as->setIcon(QIcon::fromTheme("document-save-as"));
    ui->actionCut->setIcon(QIcon::fromTheme("edit-cut"));
    ui->actionCopy->setIcon(QIcon::fromTheme("edit-copy"));
    ui->actionPaste->setIcon(QIcon::fromTheme("edit-paste"));
    ui->actionUndo->setIcon(QIcon::fromTheme("edit-undo"));
    ui->actionRedo->setIcon(QIcon::fromTheme("edit-redo"));
    ui->actionAbout_Notepad->setIcon(QIcon::fromTheme("help-about"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionNew_triggered()
{
    file_path_ = "";
    ui->textEdit->setText("");
}

void MainWindow::on_actionOpen_triggered()
{
    QString filter = "All File (*.*, *) ;; Text File (*.txt) ;; XML File (*.xml)";
    QString file_name = QFileDialog::getOpenFileName(this, "Open the file", QDir::homePath(), filter);
    QFile file(file_name);
    file_path_ = file_name;
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, QApplication::applicationName(), "File not opened");
        return;
    }
    QTextStream in(&file);
    QString text = in.readAll();
    ui->textEdit->setText(text);
    file.close();
}

void MainWindow::on_actionSave_triggered()
{
    if (!file_path_.isEmpty()) {
        QFile file(file_path_);
        if (!file.open(QFile::WriteOnly | QFile::Text)) {
            QMessageBox::warning(this, QApplication::applicationName(), "File not saved");
            return;
        }
        QTextStream out(&file);
        QString text = ui->textEdit->toPlainText();
        out << text;
        file.flush();
        file.close();
    } else {
        on_actionSave_as_triggered();
    }
}

void MainWindow::on_actionSave_as_triggered()
{
    QString filter = "All File (*.*, *)";
    QString file_name = QFileDialog::getSaveFileName(this, "Save the file", QDir::homePath(), filter);
    QFile file(file_name);
    file_path_ = file_name;
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, QApplication::applicationName(), "File not saved");
        return;
    }
    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out << text;
    file.flush();
    file.close();
}

void MainWindow::on_actionCut_triggered()
{
    ui->textEdit->cut();
}

void MainWindow::on_actionCopy_triggered()
{
    ui->textEdit->copy();
}

void MainWindow::on_actionPaste_triggered()
{
    ui->textEdit->paste();
}

void MainWindow::on_actionRedo_triggered()
{
    ui->textEdit->redo();
}

void MainWindow::on_actionUndo_triggered()
{
    ui->textEdit->undo();
}

void MainWindow::on_actionAbout_Notepad_triggered()
{
    QString about_text = "Author: Demetrius Veras\n";
    about_text += "Date: 17/03/2017\n";
    about_text += "App: Notepad Sample Qt (R)";
    QMessageBox::information(this, "About", about_text);
}
