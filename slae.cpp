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

QString toQString(double value) {
    std::stringstream ss;
    ss << value;
    return QString(ss.str().c_str());
}

void SLAE::CreateSLAE() {
    QWidget *central = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout(central);
    ui->SLAEContainer->setWidget(central);
    ui->SLAEContainer->setWidgetResizable(true);

    for (int i = 0; i < C.rows(); ++i) {
        QWidget *row = new QWidget();
        QHBoxLayout *rowLayout = new QHBoxLayout(row);

        for (int j{0}; j < C.cols(); ++j) {
            C[i][j] = new QSpinBox();
            C[i][j]->setFixedWidth(100);
            C[i][j]->setRange(-100000,100000);

            QString labelText = "X" + toQString(j + 1);
            if (j == C.cols() - 1)
                labelText += " = ";
            else
                labelText += " + ";
            QLabel *label = new QLabel(labelText);

            rowLayout->addWidget(C[i][j]);
            rowLayout->addWidget(label);
        }
        E[i] = new QSpinBox();
        E[i]->setFixedWidth(100);
        E[i]->setRange(-100000,100000);

        rowLayout->addWidget(E[i]);

        layout->addWidget(row);
    }
}

void SLAE::on_resizeButton_clicked()
{
    C.resize(ui->countOfEquation->value(), ui->counOfVariables->value());
    E.resize(ui->countOfEquation->value());
    CreateSLAE();
}

void SLAE::on_Solve_clicked()
{
    //    QMainWindow *w = new QMainWindow;
    //    w->setGeometry(50,50,480,320);
    //    w->setCentralWidget(scroll);
    //    w->show();
}
