#include "mainwindow.h"
#include "ui_mainwindow.h"

double stNum;
bool ndNumberIsTyping = false;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->pushButton_0,SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_1,SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_2,SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_3,SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_4,SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_5,SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_6,SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_7,SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_8,SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_9,SIGNAL(released()),this,SLOT(digit_pressed()));

    connect(ui->pushButton_plusminus,SIGNAL(released()),this,SLOT(unary_operation_pressed()));
    connect(ui->pushButton_per,SIGNAL(released()),this,SLOT(unary_operation_pressed()));

    connect(ui->pushButton_add,SIGNAL(released()),this,SLOT(binary_operation_pressed()));
    connect(ui->pushButton_substr,SIGNAL(released()),this,SLOT(binary_operation_pressed()));
    connect(ui->pushButton_multi,SIGNAL(released()),this,SLOT(binary_operation_pressed()));
    connect(ui->pushButton_div,SIGNAL(released()),this,SLOT(binary_operation_pressed()));

    ui->pushButton_add->setCheckable(true);
    ui->pushButton_substr->setCheckable(true);
    ui->pushButton_multi->setCheckable(true);
    ui->pushButton_div->setCheckable(true);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::digit_pressed()
{
   QPushButton * button = (QPushButton*) sender();

   double labelNum;
   QString newLabel;

   if ((ui->pushButton_add->isChecked() || ui->pushButton_substr->isChecked()
           || ui->pushButton_multi->isChecked() || ui->pushButton_div->isChecked())
           && (!ndNumberIsTyping))
   {
       labelNum = button->text().toDouble();
       ndNumberIsTyping = true;
       newLabel = QString::number(labelNum, 'g', 13);
   }
   else
   {
      if (ui->label->text().contains('.') && button->text() == "0")
      {
          newLabel = ui->label->text() + button->text();
      }
      else
      {
         labelNum = (ui->label->text() + button->text()).toDouble();
         newLabel = QString::number(labelNum, 'g', 13);
      }
   }
   ui->label->setText(newLabel);
}

void MainWindow::on_pushButton_dec_released()
{
    ui->label->setText(ui->label->text() + ".");
}

void MainWindow::unary_operation_pressed()
{
    double labelNum;
    QString newLabel;
    QPushButton * button = (QPushButton*) sender();

    if (button->text() == "+/-")
    {
       labelNum = ui->label->text().toDouble();
       labelNum = labelNum * -1;
       newLabel = QString::number(labelNum, 'g', 13);
       ui->label->setText(newLabel);
    }

    if (button->text() == "%")
    {
       labelNum = ui->label->text().toDouble();
       labelNum = labelNum * 0.01;
       newLabel = QString::number(labelNum, 'g', 13);
       ui->label->setText(newLabel);
    }
}

void MainWindow::on_pushButton_clear_released()
{
    ui->pushButton_add->setChecked(false);
    ui->pushButton_substr->setChecked(false);
    ui->pushButton_multi->setChecked(false);
    ui->pushButton_div->setChecked(false);

    ndNumberIsTyping = false;

    ui->label->setText("0");

}

void MainWindow::on_pushButton_equal_released()
{
    double labelNum, ndNum;
    QString newLabel;

    ndNum = ui->label->text().toDouble();

    if (ui->pushButton_add->isChecked())
    {
        labelNum = stNum + ndNum;
        newLabel = QString::number(labelNum, 'g', 13);
        ui->label->setText(newLabel);
        ui->pushButton_add->setChecked(false);
    }

    else if (ui->pushButton_substr->isChecked())
    {
        labelNum = stNum - ndNum;
        newLabel = QString::number(labelNum, 'g', 13);
        ui->label->setText(newLabel);
        ui->pushButton_substr->setChecked(false);
    }

    else if (ui->pushButton_multi->isChecked())
    {
        labelNum = stNum * ndNum;
        newLabel = QString::number(labelNum, 'g', 13);
        ui->label->setText(newLabel);
        ui->pushButton_multi->setChecked(false);
    }

    else if (ui->pushButton_div->isChecked())
    {
        labelNum = stNum / ndNum;
        newLabel = QString::number(labelNum, 'g', 13);
        ui->label->setText(newLabel);
        ui->pushButton_div->setChecked(false);
    }

    ndNumberIsTyping = false;
}

void MainWindow::binary_operation_pressed()
{
   QPushButton * button = (QPushButton*) sender();

   stNum = ui->label->text().toDouble();

   button->setChecked(true);
}
