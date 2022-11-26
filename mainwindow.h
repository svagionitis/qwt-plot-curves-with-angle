#pragma once

#include <QMainWindow>

#include <QwtPlotCurve>
#include <QwtPlotScaleItem>

QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void plotTwoLineCurvesWithAngleOnXAxis(int angle);
    void plotTwoLineCurvesWithAngle(int xAxisAngle);

private:
    Ui::MainWindow *ui;

    QwtPlotCurve *plotCurve1 = nullptr;
    QwtPlotCurve *plotCurve2 = nullptr;
    int angleBetweenLines = 0;
};
