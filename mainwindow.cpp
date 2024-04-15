#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , first(0)
    , second(0)
    , sign("\0")
{
    ui->setupUi(this);

    connect(ui->button1, SIGNAL(clicked(bool)), this, SLOT(EnterNum()));
    connect(ui->button2, SIGNAL(clicked(bool)), this, SLOT(EnterNum()));
    connect(ui->button3, SIGNAL(clicked(bool)), this, SLOT(EnterNum()));
    connect(ui->button4, SIGNAL(clicked(bool)), this, SLOT(EnterNum()));
    connect(ui->button5, SIGNAL(clicked(bool)), this, SLOT(EnterNum()));
    connect(ui->button6, SIGNAL(clicked(bool)), this, SLOT(EnterNum()));
    connect(ui->button7, SIGNAL(clicked(bool)), this, SLOT(EnterNum()));
    connect(ui->button8, SIGNAL(clicked(bool)), this, SLOT(EnterNum()));
    connect(ui->button9, SIGNAL(clicked(bool)), this, SLOT(EnterNum()));
    connect(ui->button0, SIGNAL(clicked(bool)), this, SLOT(EnterNum()));

    connect(ui->buttonDot, SIGNAL(clicked(bool)), this, SLOT(EnterNum()));
    connect(ui->buttonAdd, SIGNAL(clicked(bool)), this, SLOT(EnterSign()));
    connect(ui->buttonSub, SIGNAL(clicked(bool)), this, SLOT(EnterSign()));
    connect(ui->buttonMult, SIGNAL(clicked(bool)), this, SLOT(EnterSign()));
    connect(ui->buttonDiv, SIGNAL(clicked(bool)), this, SLOT(EnterSign()));
//    connect(ui->buttonPow, SIGNAL(clicked(bool)), this, SLOT(EnterSign()));
//    connect(ui->buttonSqrt, SIGNAL(clicked(bool)), this, SLOT(EnterSign()));

    connect(ui->buttonEq, SIGNAL(clicked(bool)), this, SLOT(Equals()));
    connect(ui->buttonC, SIGNAL(clicked(bool)), this, SLOT(ClearScreen()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::EnterNum()
{
    QPushButton *btn = qobject_cast<QPushButton*>(sender());
    QString currentText = ui->Screen->text();
    currentText += btn->text();
    if(btn)
    {
        ui->Screen->setText(currentText);
    }
}

void MainWindow::EnterSign()
{
    QPushButton *btn = qobject_cast<QPushButton*>(sender());
    QString currentText = ui->Screen->text();
    first = std::stof(currentText.toStdString().c_str());

    QString enteredSign = btn->text();
    sign = enteredSign.toStdString().c_str();

    currentText += enteredSign;
    if(btn)
    {
        ui->Screen->setText(currentText);
    }
}

void MainWindow::ClearScreen()
{
    ui->Screen->setText("");
}

void MainWindow::Equals()
{
    QString currentText = ui->Screen->text();
    std::string equation = currentText.toStdString().c_str();
    std::string secondNumber;

    size_t found;

    equation.find(sign);
// TO FIX
    if(found != std::string::npos)
    {
        secondNumber = equation.substr(found+1, equation.back());
        second = std::stof(secondNumber);
    }

    ClearScreen();

    ui->Screen->setText(QString::number(first + second));
}
