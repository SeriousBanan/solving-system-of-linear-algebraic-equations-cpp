#ifndef SLAE_H
#define SLAE_H

#include <QMainWindow>
#include "solvingSLAE/solveSLAE.h"
#include "ui_slae.h"
#include <QMatrix>
#include <vector>

QT_BEGIN_NAMESPACE
namespace Ui { class SLAE; }
QT_END_NAMESPACE

class SLAE : public QMainWindow
{
    Q_OBJECT

public:
    SLAE(QWidget *parent = nullptr);
    ~SLAE();

private slots:
    void on_resizeButton_clicked();

    void on_Solve_clicked();

private:
    Ui::SLAE *ui;
    void CreateSLAE();
    int countOfVariables = 3;
    int countOfEquation = 3;
    std::vector<std::vector<QSpinBox*>> C{3};
    std::vector<QSpinBox*> E;
    Matrix<int> A{ 3, 3 };
    std::vector<int> S;
};
#endif // SLAE_H
