#include "PlotCurvesWithAngle.h"

#include <QDebug>

#include <QwtPlot>
#include <QwtPlotDirectPainter>
#include <QwtScaleDiv>
#include <QwtSymbol>

namespace PlotCurves
{
    void PlotCurvesWithAngle::plotLineCurveSinglePoint(QwtPlot *plot, QwtPlotCurve **plotCurve,
                                                       const QPointF &positionCoordinates,
                                                       QwtSymbol *symbol, Qt::GlobalColor color, bool doReplot)
    {
        qDebug() << "positionCoordinates: " << positionCoordinates;

        QPointF zeroCoordinates(0.0, 0.0);

        if (*plotCurve == nullptr)
        {
            *plotCurve = new QwtPlotCurve();
        }
        else
        {
            // Clean up previous plot
            (*plotCurve)->setSamples(nullptr);
        }

        (*plotCurve)->setSymbol(symbol);
        (*plotCurve)->setPen(color);
        (*plotCurve)->setStyle(QwtPlotCurve::Lines);
        (*plotCurve)->setCurveAttribute(QwtPlotCurve::Fitted);
        (*plotCurve)->setPaintAttribute(QwtPlotCurve::ClipPolygons);
        (*plotCurve)->setRenderHint(QwtPlotItem::RenderAntialiased);

        QPolygonF positionPoints;
        positionPoints << zeroCoordinates << positionCoordinates;
        (*plotCurve)->setSamples(positionPoints);

        (*plotCurve)->attach(plot);

        auto positionDirectPainter = new QwtPlotDirectPainter(plot);
        positionDirectPainter->drawSeries(*plotCurve, positionPoints.size() - 1, positionPoints.size() - 1);

        if (doReplot)
        {
            plot->replot();
            plot->repaint();
        }
    }

    void PlotCurvesWithAngle::plotTwoLineCurvesTwoPoints(QwtPlot *plot, QwtPlotCurve **plotCurve1, QwtPlotCurve **plotCurve2,
                                                         const QPointF &point1Coordinates, const QPointF &point2Coordinates,
                                                         QwtSymbol *symbol1, QwtSymbol *symbol2,
                                                         Qt::GlobalColor color1, Qt::GlobalColor color2,
                                                         bool doReplot)
    {
        qDebug() << "point1Coordinates: " << point1Coordinates << "point2Coordinates: " << point2Coordinates;

        QPointF zeroCoordinates(0.0, 0.0);

        if (*plotCurve1 == nullptr)
        {
            *plotCurve1 = new QwtPlotCurve();
        }
        else
        {
            // Clean up previous plot
            (*plotCurve1)->setSamples(nullptr);
        }

        if (*plotCurve2 == nullptr)
        {
            *plotCurve2 = new QwtPlotCurve();
        }
        else
        {
            // Clean up previous plot
            (*plotCurve2)->setSamples(nullptr);
        }

        (*plotCurve1)->setSymbol(symbol1);
        (*plotCurve1)->setPen(color1);
        (*plotCurve1)->setStyle(QwtPlotCurve::Lines);
        (*plotCurve1)->setCurveAttribute(QwtPlotCurve::Fitted);
        (*plotCurve1)->setPaintAttribute(QwtPlotCurve::ClipPolygons);
        (*plotCurve1)->setRenderHint(QwtPlotItem::RenderAntialiased);

        QPolygonF point1PositionPoints;
        point1PositionPoints << zeroCoordinates << point1Coordinates;
        (*plotCurve1)->setSamples(point1PositionPoints);
        (*plotCurve1)->attach(plot);
        auto point1DirectPainter = new QwtPlotDirectPainter(plot);
        point1DirectPainter->drawSeries(*plotCurve1, point1PositionPoints.size() - 1, point1PositionPoints.size() - 1);

        (*plotCurve2)->setSymbol(symbol2);
        (*plotCurve2)->setPen(color2);
        (*plotCurve2)->setStyle(QwtPlotCurve::Lines);
        (*plotCurve2)->setCurveAttribute(QwtPlotCurve::Fitted);
        (*plotCurve2)->setPaintAttribute(QwtPlotCurve::ClipPolygons);
        (*plotCurve2)->setRenderHint(QwtPlotItem::RenderAntialiased);

        QPolygonF point2PositionPoints;
        point2PositionPoints << zeroCoordinates << point2Coordinates;
        (*plotCurve2)->setSamples(point2PositionPoints);
        (*plotCurve2)->attach(plot);
        auto point2DirectPainter = new QwtPlotDirectPainter(plot);
        point2DirectPainter->drawSeries(*plotCurve2, point2PositionPoints.size() - 1, point2PositionPoints.size() - 1);

        if (doReplot)
        {
            plot->replot();
            plot->repaint();
        }
    }

    void PlotCurvesWithAngle::plotLineCurveDegreesFromXAxis(QwtPlot *plot, QwtPlotCurve **plotCurve,
                                                            const float &degreesFromXAxis, const float &distance,
                                                            QwtSymbol *symbol, Qt::GlobalColor color, bool doReplot)

    {
        qDebug() << "degreesFromXAxis: " << degreesFromXAxis;
        qDebug() << "distance: " << distance;

        QPointF zeroCoordinates(0.0, 0.0);
        // The coordinates in a xy axis of a point, with given angle and distance is calculated
        // by the following formula
        // X= distance * cos(angle) + x0
        // Y= distance * sin(angle) + y0
        // Where (x0, y0) is another point. In our case that point is (0, 0)
        QPointF positionCoordinates(distance * cos(degreesFromXAxis * (M_PI / 180)),
                                    distance * sin(degreesFromXAxis * (M_PI / 180)));

        if (*plotCurve == nullptr)
        {
            *plotCurve = new QwtPlotCurve();
        }
        else
        {
            // Clean up previous plot
            (*plotCurve)->setSamples(nullptr);
        }

        (*plotCurve)->setSymbol(symbol);
        (*plotCurve)->setPen(color);
        (*plotCurve)->setStyle(QwtPlotCurve::Lines);
        (*plotCurve)->setCurveAttribute(QwtPlotCurve::Fitted);
        (*plotCurve)->setPaintAttribute(QwtPlotCurve::ClipPolygons);
        (*plotCurve)->setRenderHint(QwtPlotItem::RenderAntialiased);

        QPolygonF positionPoints;
        positionPoints << zeroCoordinates << positionCoordinates;
        (*plotCurve)->setSamples(positionPoints);

        (*plotCurve)->attach(plot);

        auto positionDirectPainter = new QwtPlotDirectPainter(plot);
        positionDirectPainter->drawSeries(*plotCurve, positionPoints.size() - 1, positionPoints.size() - 1);

        if (doReplot)
        {
            plot->replot();
            plot->repaint();
        }
    }

    void PlotCurvesWithAngle::plotTwoLineCurvesWithAngle(QwtPlot *plot, QwtPlotCurve **plotCurve1, QwtPlotCurve **plotCurve2,
                                                         const float &angle, const float &xAxisAngle)
    {
        qDebug() << "angle: " << angle << " xAxisAngle: " << xAxisAngle;
        float distance = (float)plot->size().width() / 2.0f;
        qDebug() << "distance: " << distance;
        float halfAngle = angle / 2;

        QPointF positionNorthCoordinates(distance * cos((xAxisAngle + halfAngle) * (M_PI / 180)),
                                         distance * sin((xAxisAngle + halfAngle) * (M_PI / 180)));
        QPointF positionSouthCoordinates(distance * cos((xAxisAngle - halfAngle) * (M_PI / 180)),
                                         distance * sin((xAxisAngle - halfAngle) * (M_PI / 180)));

        plotTwoLineCurvesTwoPoints(plot, plotCurve1, plotCurve2,
                                   positionNorthCoordinates, positionSouthCoordinates,
                                   new QwtSymbol(QwtSymbol::Cross, Qt::gray, QPen(Qt::black), QSize(5, 5)),
                                   new QwtSymbol(QwtSymbol::Cross, Qt::gray, QPen(Qt::black), QSize(5, 5)),
                                   Qt::darkMagenta,
                                   Qt::darkRed);
    }
}
