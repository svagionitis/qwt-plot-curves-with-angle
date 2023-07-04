#include "PlotArc.h"

#include <QDebug>
#include <QPainterPath>

#include <QwtPlotMarker>
#include <QwtSymbol>

namespace Plot
{
    PlotArc::PlotArc(QWidget *parent, QPair<float, float> minMaxXAxisScale, QPair<float, float> minMaxYAxisScale)
        : QwtPlot(parent)
    {
        // Remove the outer axis
        enableAxis(QwtAxis::XBottom, false);
        enableAxis(QwtAxis::YLeft, false);

        // Set the axis scale
        setAxisScale(QwtAxis::XBottom, minMaxXAxisScale.first, minMaxXAxisScale.second);
        setAxisScale(QwtAxis::YLeft, minMaxYAxisScale.first, minMaxYAxisScale.second);

        // Add inner axis
        verticalAxisScale = new QwtPlotScaleItem(QwtScaleDraw::RightScale, 0.0);
        verticalAxisScale->attach(this);
        horizontalAxisScale = new QwtPlotScaleItem(QwtScaleDraw::BottomScale, 0.0);
        horizontalAxisScale->attach(this);

        // Load an image, here an SVG, as pixmap
        PlotLoadImagePixmap("images/battleship-top-side.svg");

        // Plot circles
        // Use replot to calculate the axis scale bounds
        this->replot();
        auto radius = (float)this->axisScaleDiv(QwtAxis::YLeft).upperBound();
        PlotCircle(&circleItem, radius);
        PlotCircle(&circleItemInner, radius / 2);

        this->replot();
        this->repaint();
    }

    PlotArc::~PlotArc()
    {
        delete verticalAxisScale;
        delete horizontalAxisScale;

        delete circleItem;
        delete circleItemInner;
    }

    void PlotArc::PlotLoadImagePixmap(const QString &fileName, bool doReplot)
    {
        qDebug() << Q_FUNC_INFO << "fileName: " << fileName;

        QPixmap svgPixmap(fileName);
        QwtSymbol *svgSymbol = new QwtSymbol();
        svgSymbol->setPixmap(svgPixmap);
        svgSymbol->setPinPoint(QPointF(svgPixmap.width() / 2,
                                       svgPixmap.height() / 2));

        QwtPlotMarker *marker = new QwtPlotMarker();
        marker->setSymbol(svgSymbol);
        marker->attach(this);

        if (doReplot)
        {
            this->replot();
            this->repaint();
        }
    }

    void PlotArc::PlotCircle(QwtPlotShapeItem **circleItem, const float &radius, bool doReplot)
    {
        qDebug() << Q_FUNC_INFO << "radius: " << radius;

        if (*circleItem == nullptr)
        {
            *circleItem = new QwtPlotShapeItem();
        }

        QPainterPath circlePainterPath;
        const QRectF circleRect(-radius,
                                -radius,
                                2 * radius,
                                2 * radius);

        circlePainterPath.addEllipse(circleRect);
        (*circleItem)->setShape(circlePainterPath);
        (*circleItem)->setRenderHint(QwtPlotItem::RenderAntialiased);
        (*circleItem)->attach(this);

        if (doReplot)
        {
            this->replot();
            this->repaint();
        }
    }
}
