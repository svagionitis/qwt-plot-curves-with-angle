#pragma once

#include <QMainWindow>

#include <QwtPlotCurve>
#include <QwtPlotGraphicItem>
#include <QwtPlotScaleItem>
#include <QwtPlotShapeItem>

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

    void mousePressEvent(QMouseEvent *event);

public slots:
    void plotTwoLineCurvesWithAngleOnXAxis(int angle);
    void plotTwoLineCurvesWithAngle(int xAxisAngle);

private:
    Ui::MainWindow *ui;

    QwtPlotScaleItem *verticalAxisScale = nullptr;
    QwtPlotScaleItem *horizontalAxisScale = nullptr;

    QwtPlotCurve *plotCurve1 = nullptr;
    QwtPlotCurve *plotCurve2 = nullptr;

    QwtPlotGraphicItem *svgGraphicItem = nullptr;

    QwtPlotShapeItem *circleItem = nullptr;
    QwtPlotShapeItem *circleItemInner = nullptr;
    QwtPlotShapeItem *arcItem = nullptr;

    int angleBetweenLines = 0;
    int rotateAngleLines = 0;
};
