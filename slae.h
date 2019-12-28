#ifndef SLAE_H
#define SLAE_H

#include <QMainWindow>
#include "solvingSLAE/solveSLAE.h"
#include "ui_slae.h"

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
    Matrix<QSpinBox*> C{ 3, 3 };
    std::vector<QSpinBox*> E{3};
};
#endif // SLAE_H
