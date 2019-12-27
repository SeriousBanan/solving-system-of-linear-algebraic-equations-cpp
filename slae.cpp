#include "slae.h"
#include "ui_slae.h"
#include "QDebug"
#include "QScrollArea"
#include <sstream>

SLAE::SLAE(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SLAE)
{
    ui->setupUi(this);
    CreateSLAE();
}

SLAE::~SLAE()
{
    delete ui;
}

QString toString(double value) {
    std::stringstream ss;
    ss << value;
    return QString(ss.str().c_str());
}

void SLAE::CreateSLAE() {
    QWidget *central = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout(central);
    ui->SLAEContainer->setWidget(central);
    ui->SLAEContainer->setWidgetResizable(true);

    for (int i = 0; i < countOfEquations; ++i) {
        QWidget *row = new QWidget();
        QHBoxLayout *rowLayout = new QHBoxLayout(row);
        //Добавить заполнение матрицы

        for (int j{0}; j < countOfVariables; ++j) {
            QDoubleSpinBox *coefficient = new QDoubleSpinBox();
            coefficient->setFixedWidth(100);
            coefficient->setRange(-100000,100000);

            QString labelText = "X" + toString(j + 1);
            if (j == countOfVariables - 1)
                labelText += " = ";
            else
                labelText += " + ";
            QLabel *label = new QLabel(labelText);

            rowLayout->addWidget(coefficient);
            rowLayout->addWidget(label);
        }
        QDoubleSpinBox *freeCoefficient = new QDoubleSpinBox();
        freeCoefficient->setFixedWidth(100);
        freeCoefficient->setRange(-100000,100000);
        rowLayout->addWidget(freeCoefficient);

        layout->addWidget(row);
    }
}

void SLAE::on_resizeButton_clicked()
{
    //Добавить генерацию матрицы
    countOfEquations = ui->countOfEquation->value();
    countOfVariables = ui->counOfVariables->value();
    CreateSLAE();
}

void SLAE::on_Solve_clicked()
{
    //    QMainWindow *w = new QMainWindow;
    //    w->setGeometry(50,50,480,320);
    //    w->setCentralWidget(scroll);
    //    w->show();
}
