#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "PlotCurvesWithAngle.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Init slider for angle between lines
    ui->angleBetweenCurvesHorizontalSlider->setRange((int)PlotCurves::PlotCurvesWithAngle::MinAngleBetweenCurves,
                                                     (int)PlotCurves::PlotCurvesWithAngle::MaxAngleBetweenCurves);
    QObject::connect(ui->angleBetweenCurvesHorizontalSlider, &QSlider::valueChanged, this, &MainWindow::plotTwoLineCurvesWithAngleOnXAxis);

    // Init slider for rotation angle of the lines
    ui->rotateLineCurvesHorizontalSlider->setRange((int)PlotCurves::PlotCurvesWithAngle::MinAngleRotateCurves,
                                                   (int)PlotCurves::PlotCurvesWithAngle::MaxAngleRotateCurves);
    QObject::connect(ui->rotateLineCurvesHorizontalSlider, &QSlider::valueChanged, this, &MainWindow::plotTwoLineCurvesWithAngle);

    // Init plot
    // Remove the outer axis
    ui->qwtPlot->enableAxis(QwtAxis::YLeft, false);
    ui->qwtPlot->enableAxis(QwtAxis::XBottom, false);
    // Set the axis scale
    ui->qwtPlot->setAxisScale(QwtAxis::YLeft, -90.0, 90.0);
    ui->qwtPlot->setAxisScale(QwtAxis::XBottom, -90.0, 90.0);

    // Add inner axis
    verticalAxisScale = new QwtPlotScaleItem(QwtScaleDraw::RightScale, 0.0);
    verticalAxisScale->attach(ui->qwtPlot);
    horizontalAxisScale = new QwtPlotScaleItem(QwtScaleDraw::BottomScale, 0.0);
    horizontalAxisScale->attach(ui->qwtPlot);

#ifdef SVG_RENDERED
    // Add image
    PlotCurves::PlotCurvesWithAngle::loadSVG(ui->qwtPlot, &svgGraphicItem, "images/battleship-top-side.svg");
    ui->qwtPlot->replot();
    ui->qwtPlot->repaint();
#endif
}

MainWindow::~MainWindow()
{
    delete plotCurve1;
    delete plotCurve2;

    delete verticalAxisScale;
    delete horizontalAxisScale;

    delete ui;
}

void MainWindow::plotTwoLineCurvesWithAngleOnXAxis(int angle)
{
    PlotCurves::PlotCurvesWithAngle::plotTwoLineCurvesWithAngle(ui->qwtPlot, &plotCurve1, &plotCurve2,
                                                                (float)angle, (float)rotateAngleLines);
    angleBetweenLines = angle;

    ui->qwtPlot->replot();
    ui->qwtPlot->repaint();
}

void MainWindow::plotTwoLineCurvesWithAngle(int xAxisAngle)
{
    PlotCurves::PlotCurvesWithAngle::plotTwoLineCurvesWithAngle(ui->qwtPlot, &plotCurve1, &plotCurve2,
                                                                (float)angleBetweenLines, (float)xAxisAngle);
    rotateAngleLines = xAxisAngle;

    ui->qwtPlot->replot();
    ui->qwtPlot->repaint();
}
