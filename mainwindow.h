#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <math.h>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

struct DronData{
    int size;
    QVector<double> x;
    QVector<double> y;
    QVector<double> t;
    QVector<double> b;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    struct DronData data;
    void readfile();
public slots:
    void plot();
    void compute();
    void determinate();
};
#endif // MAINWINDOW_H
