#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QwtPlotScaleItem>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Remove the outer axis
    ui->qwtPlot->enableAxis(QwtAxis::YLeft, false);
    ui->qwtPlot->enableAxis(QwtAxis::XBottom, false);
    // Set the axis scale
    ui->qwtPlot->setAxisScale(QwtAxis::YLeft, -90.0, 90.0);
    ui->qwtPlot->setAxisScale(QwtAxis::XBottom, -90.0, 90.0);

    // Add inner axis
    QwtPlotScaleItem *verticalAxisScale = new QwtPlotScaleItem(QwtScaleDraw::RightScale, 0.0);
    verticalAxisScale->attach(ui->qwtPlot);
    QwtPlotScaleItem *horizontalAxisScale = new QwtPlotScaleItem(QwtScaleDraw::BottomScale, 0.0);
    horizontalAxisScale->attach(ui->qwtPlot);
}

MainWindow::~MainWindow()
{
    delete ui;
}
