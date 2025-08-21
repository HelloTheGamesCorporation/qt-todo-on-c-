#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
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

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void changeTheme();
    void addToDo();
    void removeToDo();
private:
    QString darkTheme;
    QString lightTheme;
    QPushButton *changeThemeBtn;
    QListWidget *display;
};
#endif // MAINWINDOW_H
