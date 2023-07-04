#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QDebug>
#include <QMouseEvent>

#include "PlotCurvesWithAngle.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setMouseTracking(true);

    // Init slider for angle between lines
    ui->angleBetweenCurvesHorizontalSlider->setRange((int)PlotCurves::PlotCurvesWithAngle::MinAngleBetweenCurves,
                                                     (int)PlotCurves::PlotCurvesWithAngle::MaxAngleBetweenCurves);
    QObject::connect(ui->angleBetweenCurvesHorizontalSlider, &QSlider::valueChanged, this, &MainWindow::plotTwoLineCurvesWithAngleOnXAxis);

    // Init slider for rotation angle of the lines
    ui->rotateLineCurvesHorizontalSlider->setRange((int)PlotCurves::PlotCurvesWithAngle::MinAngleRotateCurves,
                                                   (int)PlotCurves::PlotCurvesWithAngle::MaxAngleRotateCurves);
    QObject::connect(ui->rotateLineCurvesHorizontalSlider, &QSlider::valueChanged, this, &MainWindow::plotTwoLineCurvesWithAngle);

#ifdef PLOT_ARC
    plotArc = new Plot::PlotArc(this);
    ui->verticalLayout_2->addWidget(plotArc);
#else
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

    // Load an image, here an SVG, as pixmap
    PlotCurves::PlotCurvesWithAngle::loadImagePixmap(ui->qwtPlot, "images/battleship-top-side.svg");

    // Plot circles
    // Use replot to calculate the axis scale bounds
    ui->qwtPlot->replot();
    auto radius = (float)ui->qwtPlot->axisScaleDiv(QwtAxis::YLeft).upperBound();
    PlotCurves::PlotCurvesWithAngle::plotCircle(ui->qwtPlot, &circleItem, radius);
    PlotCurves::PlotCurvesWithAngle::plotCircle(ui->qwtPlot, &circleItemInner, radius / 2);

    ui->qwtPlot->replot();
    ui->qwtPlot->repaint();
#endif

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

    delete circleItem;
    delete circleItemInner;

    delete arcItem;

    delete ui;
}

void MainWindow::plotTwoLineCurvesWithAngleOnXAxis(int angle)
{
#ifdef PLOT_TWO_LINES_WITH_ANGLE
    PlotCurves::PlotCurvesWithAngle::plotTwoLineCurvesWithAngle(ui->qwtPlot, &plotCurve1, &plotCurve2,
                                                                (float)angle, (float)rotateAngleLines);
#endif
    // The replot here is to calculate the axis bounds.
    // The negative values in the angles is for clockwise rotation
    ui->qwtPlot->replot();
    PlotCurves::PlotCurvesWithAngle::plotArc(ui->qwtPlot, &arcItem, (float)ui->qwtPlot->axisScaleDiv(QwtAxis::YLeft).upperBound(),
                                             rotateAngleLines, angle, true);
    angleBetweenLines = angle;

    ui->qwtPlot->replot();
    ui->qwtPlot->repaint();
}

void MainWindow::plotTwoLineCurvesWithAngle(int xAxisAngle)
{
#ifdef PLOT_TWO_LINES_WITH_ANGLE
    PlotCurves::PlotCurvesWithAngle::plotTwoLineCurvesWithAngle(ui->qwtPlot, &plotCurve1, &plotCurve2,
                                                                (float)angleBetweenLines, (float)xAxisAngle);
#endif
    // The replot here is to calculate the axis bounds.
    ui->qwtPlot->replot();
    PlotCurves::PlotCurvesWithAngle::plotArc(ui->qwtPlot, &arcItem, (float)ui->qwtPlot->axisScaleDiv(QwtAxis::YLeft).upperBound(),
                                             xAxisAngle, angleBetweenLines, true);
    rotateAngleLines = xAxisAngle;

    ui->qwtPlot->replot();
    ui->qwtPlot->repaint();
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    qDebug() << Q_FUNC_INFO << "Event Type: " << event->type() << "Mouse Position: " << event->pos();

    ui->qwtPlot->replot();
    // FIXME: The x and y below are not the correct x, y coordinates on the plot
    auto x = ui->qwtPlot->invTransform(QwtAxis::XBottom, event->pos().x());
    auto y = ui->qwtPlot->invTransform(QwtAxis::YLeft, event->pos().y());

    qDebug() << Q_FUNC_INFO << "Plot X: " << x << "Plot Y: " << y;
}
