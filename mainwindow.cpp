#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , first(0.0)
    , second(0.0)
    , toClear(false)
    , sign("\0")
{
    ui->setupUi(this);

    setFixedSize(260, 270);

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

    connect(ui->buttonDot, SIGNAL(clicked(bool)), this, SLOT(EnterDot()));
    connect(ui->buttonAdd, SIGNAL(clicked(bool)), this, SLOT(EnterSign()));
    connect(ui->buttonSub, SIGNAL(clicked(bool)), this, SLOT(EnterSign()));
    connect(ui->buttonMult, SIGNAL(clicked(bool)), this, SLOT(EnterSign()));
    connect(ui->buttonDiv, SIGNAL(clicked(bool)), this, SLOT(EnterSign()));
    connect(ui->buttonPow, SIGNAL(clicked(bool)), this, SLOT(Square()));
    connect(ui->buttonSqrt, SIGNAL(clicked(bool)), this, SLOT(SquareRoot()));

    connect(ui->buttonEq, SIGNAL(clicked(bool)), this, SLOT(Equals()));
    connect(ui->buttonC, SIGNAL(clicked(bool)), this, SLOT(ClearScreen()));

    std::setlocale(LC_ALL, "C"); // changing locale to make std::stod work correctly with Qt (to not delete decimal parts while converting)
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::EnterNum()
{
    if(toClear)
    {
        ClearScreen();
        toClear = false;
    }

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

    if(!(currentText.contains("+")) && !(currentText.contains("-")) && !(currentText.contains("*")) && !(currentText.contains("/")) && !(toClear) && !(currentText.isEmpty()))
    {
        first = std::stod(currentText.toStdString().c_str());

        QString enteredSign = btn->text();
        sign = enteredSign.toStdString().c_str();

        currentText += enteredSign;
        if(btn)
        {
            ui->Screen->setText(currentText);
        }
    }
}

void MainWindow::EnterDot()
{
    QString currentText = ui->Screen->text();

    if(currentText.contains("+") || currentText.contains("-") || currentText.contains("*") || currentText.contains("/"))
    {
        if(!(currentText.back() == '.') && !(currentText.count('.') > 1) && !(currentText.back() == '+') && !(currentText.back() == '-') && !(currentText.back() == '*') && !(currentText.back() == '/'))
        {
            currentText += ".";
            ui->Screen->setText(currentText);
        }
    }
    else
    {
        if(!(currentText.isEmpty()) && (currentText.count('.') == 0))
        {
            currentText += ".";
            ui->Screen->setText(currentText);
        }
    }
}

void MainWindow::Square()
{
    QString currentText = ui->Screen->text();

    if(!(currentText.contains("+")) && !(currentText.contains("-")) && !(currentText.contains("*")) && !(currentText.contains("/")) && !(toClear) && !(currentText.isEmpty()))
    {
        first = std::stod(currentText.toStdString().c_str());
        sign = "sq";
        Operation(sign);
    }
}

void MainWindow::SquareRoot()
{
    QString currentText = ui->Screen->text();

    if(!(currentText.contains("+")) && !(currentText.contains("-")) && !(currentText.contains("*")) && !(currentText.contains("/")) && !(toClear) && !(currentText.isEmpty()))
    {
        first = std::stod(currentText.toStdString().c_str());
        sign = "sqrt";
        Operation(sign);
    }
}

void MainWindow::ClearScreen()
{
    ui->Screen->setText("");
}

void MainWindow::Operation(std::string sign_in)
{
    QString textResult;
    if(sign_in == "+")
    {
        textResult = QString::number((first+second), 'f', 2);
        ui->Screen->setText(textResult);
    }
    else if(sign_in == "-")
    {
        textResult = QString::number((first-second), 'f', 2);
        ui->Screen->setText(textResult);
    }
    else if(sign_in == "*")
    {
        textResult = QString::number((first*second), 'f', 2);
        ui->Screen->setText(textResult);
    }
    else if(sign_in == "/")
    {
        if(!second)
        {
            ui->Screen->setText("Can't divide by 0!");
        }
        else
        {
            textResult = QString::number((first/second), 'f', 2);
            ui->Screen->setText(textResult);
        }
    }
    else if(sign_in == "sq")
    {
        textResult = QString::number((first*first), 'f', 2);
        ui->Screen->setText(textResult);
    }
    else if(sign_in == "sqrt")
    {
        textResult = QString::number(sqrt(first), 'f', 2);
        ui->Screen->setText(textResult);
    }
}

void MainWindow::Equals()
{
    QString currentText = ui->Screen->text();
    std::string equation = currentText.toStdString().c_str();
    std::string secondNumber;

    size_t found = equation.find(sign);
    if(sign == "\0")
    {
        found = -1;
    }

    if((found != std::string::npos) && (equation.back() != sign[0]))
    {
        secondNumber = equation.substr(found+1);
        second = std::stod(secondNumber);
        ClearScreen();
        Operation(sign);
        toClear = true;
    }
}
