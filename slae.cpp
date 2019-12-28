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
    E.resize(countOfEquation);
    S.resize(countOfEquation);
    for (int i = 0; i < countOfEquation; ++i)
        C[i].resize(countOfVariables);
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

    for (int i = 0; i < countOfEquation; ++i) {
        QWidget *row = new QWidget();
        QHBoxLayout *rowLayout = new QHBoxLayout(row);

        for (int j{0}; j < countOfVariables; ++j) {
            C[i][j] = new QSpinBox();
            C[i][j]->setFixedWidth(100);
            C[i][j]->setRange(-100000,100000);

            QString labelText = "X" + toQString(j + 1);
            if (j == countOfVariables - 1)
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
    for (int i = 0; i < countOfEquation; ++i) {
        for (int j = 0; j < countOfVariables; ++j)
            delete C[i][j];
        delete E[i];
    }
    countOfEquation = ui->countOfEquation->value();
    countOfVariables = ui->countOfVariables->value();
    C.resize(countOfEquation);
    for (int i = 0; i < countOfEquation; ++i)
        C[i].resize(countOfVariables);
    E.resize(countOfEquation);
    A.resize(countOfEquation, countOfVariables);
    S.resize(countOfEquation);
    CreateSLAE();
}

void SLAE::on_Solve_clicked()
{
    for (int i = 0; i < countOfEquation; ++i) {
        for (int j = 0; j < countOfVariables; ++j)
            A[i][j] = C[i][j]->value();
        S[i] = E[i]->value();
    }

    QWidget *central = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout(central);
    QScrollArea *scroll = new QScrollArea();
    scroll->setWidget(central);
    scroll->setWidgetResizable(true);

    QLabel *label = new QLabel(solveSLAE(A, S).c_str());
    layout->addWidget(label);

    QMainWindow *w = new QMainWindow;
    w->setGeometry(50,50,480,320);

    w->setCentralWidget(scroll);
    const QFont *font = new QFont("MS Shell Dlg", 12);
    scroll->setFont(*font);
    w->show();
}
