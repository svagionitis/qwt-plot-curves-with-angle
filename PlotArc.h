#pragma once

#include <QwtPlot>
#include <QwtPlotShapeItem>
#include <QwtPlotScaleItem>

namespace Plot
{
    class PlotArc : public QwtPlot
    {
        Q_OBJECT

    public:
        PlotArc(QWidget *parent = nullptr, QPair<float, float> minMaxXAxisScale = {-90.0, 90.0}, QPair<float, float> minMaxYAxisScale = {-90.0, 90.0});
        virtual ~PlotArc();

    private:
        QwtPlotScaleItem *verticalAxisScale = nullptr;
        QwtPlotScaleItem *horizontalAxisScale = nullptr;

        QwtPlotShapeItem *circleItem = nullptr;
        QwtPlotShapeItem *circleItemInner = nullptr;

        void PlotLoadImagePixmap(const QString &fileName, bool doReplot = false);
        void PlotCircle(QwtPlotShapeItem **circleItem, const float &radius, bool doReplot = false);
    };
}
