#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <cstring>
#include <string.h>
#include <cmath>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    double first, second;
    bool toClear;
    std::string sign;

private slots:
    void EnterNum();
    void EnterSign();
    void EnterDot();
    void Square();
    void SquareRoot();
    void Equals();
    void Operation(std::string);
    void ClearScreen();
};
#endif // MAINWINDOW_H
