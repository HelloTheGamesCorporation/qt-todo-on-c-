#include "mainwindow.h"

#include <QPushButton>
#include <QWidget>
#include <QListWidget>
#include <QListWidgetItem>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QInputDialog>
#include <QMessageBox>
#include <QSpacerItem>
#include <QSizePolicy>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{

    setWindowTitle("To-Do List");
    setFixedSize(700, 700);

    darkTheme = R"(QMainWindow {background-color: #333;} QListWidget {background-color: #444; color: white; font-size: 24px; border: 1px solid #666; border-radius: 5px;}
                    QInputDialog {background-color: #333; color: white; border: 1px solid #666; border-radius: 5px;} QLabel {color: white;}
                    QPushButton {background-color: #555; color: white; border: 1px solid #666; padding: 5px; width: 75px; border-radius: 5px;}
                    QPushButton:hover {border: 3px solid #666; border-radius: 7px;}
                    QMessageBox {background-color: #333; color: white;})";
    lightTheme = R"(QMainWindow {background-color: white;} QListWidget {background-color: white; color: black; font-size: 24px; border: 1px solid #666; border-radius: 5px;}
                    QInputDialog {background-color: white; color: black; border: 1px solid #ccc; border-radius: 5px;} QLabel {color: black;}
                    QPushButton {background-color: #f0f0f0; border: 1px solid #ccc; padding: 5px; width: 75px; border-radius: 5px;}
                    QPushButton:hover {border: 3px solid #ccc; border-radius: 7px;}
                    QMessageBox {background-color: white; color: black;})";

    setStyleSheet(darkTheme);

    QVBoxLayout *generalLayout = new QVBoxLayout();
    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(generalLayout);
    setCentralWidget(centralWidget);

    display = new QListWidget();
    display->setFixedHeight(600);

    QHBoxLayout *buttonsLayout = new QHBoxLayout();

    QPushButton *createToDoBtn = new QPushButton("+  New");
    QPushButton *removeToDoBtn = new  QPushButton("-   Remove");
    changeThemeBtn = new QPushButton("☀  Light");

    buttonsLayout->addWidget(createToDoBtn);
    buttonsLayout->addWidget(removeToDoBtn);

    QSpacerItem *spacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);
    buttonsLayout->addItem(spacer);
    buttonsLayout->addWidget(changeThemeBtn);

    generalLayout->addLayout(buttonsLayout);
    generalLayout->addWidget(display);

    connect(changeThemeBtn, &QPushButton::clicked, this, &MainWindow::changeTheme);
    connect(createToDoBtn, &QPushButton::clicked, this, &MainWindow::addToDo);
    connect(removeToDoBtn, &QPushButton::clicked, this, &MainWindow::removeToDo);

}

MainWindow::~MainWindow() {}

void MainWindow::addToDo() {
    bool ok;
    QString text = QInputDialog::getText(this, tr("Adding new To-Do in List"), tr("Enter the new To-Do"), QLineEdit::Normal, "", &ok);
    try {
        if (ok && !text.isEmpty()) {
            QListWidgetItem *item = new QListWidgetItem("• " + text + "\n");
            this->display->addItem(item);
            QMessageBox::information(this, "Done", "Added new To-Do");
        }
    } catch (const std::exception&e) {
        QMessageBox::critical(this, "Failed", QString("Add error:\n%1").arg(e.what()), QMessageBox::StandardButton::Ok);
    }
}

void MainWindow::removeToDo() {
    int selected = display->currentRow();
    if (selected != -1) {
        display->takeItem(selected);
        QMessageBox::information(this, "Done", "Remove is done");
    } else {
        QMessageBox::critical(this, "Failed", "Please select the To-Do", QMessageBox::StandardButton::Ok);
    }

}


void MainWindow::changeTheme() {
    if (this->changeThemeBtn->text() == "☀  Light") {
        setStyleSheet(lightTheme);
        this->changeThemeBtn->setText("☾ Dark");
    } else {
        setStyleSheet(darkTheme);
        this->changeThemeBtn->setText("☀  Light");
    }
}
