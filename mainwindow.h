#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>
#include "Pieza.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT



public:
    MainWindow(QWidget *parent = nullptr);
    std::vector<Pieza> vp;
    int c_piezas = 0;
    void resetValues();
    ~MainWindow();

private slots:
    void on_newP_clicked();

    void on_calculate_clicked();


    void on_pushButton_clicked();


    void on_lot_select_activated(int index);

    void on_newP_2_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
