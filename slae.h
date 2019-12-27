#ifndef SLAE_H
#define SLAE_H

#include <QMainWindow>

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
    int countOfEquations{3};
    int countOfVariables{3};
    void CreateSLAE();
};
#endif // SLAE_H
