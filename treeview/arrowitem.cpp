#include "arrowitem.h"

#include <QPainter>

namespace HeaderIncludeGraph {
namespace Internal {

ArrowItem::ArrowItem(const QPointF &start, const QPointF &end)
    : m_start(start),
      m_end(end)
{
    m_boundingRect = QRectF(m_start, m_end);

//    updateEndArrows();

    m_pen.setColor(Qt::black);
    m_pen.setWidthF(2);
}

QRectF ArrowItem::boundingRect() const
{
    return m_boundingRect;
}

void ArrowItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->setPen(m_pen);
    painter->drawLine(m_start, m_end);
    painter->drawLine(m_firstArrowEnd);
    painter->drawLine(m_secondArrowEnd);
}

void ArrowItem::setStart(const QPointF &pointInSceneCoords)
{
    m_start = mapFromScene(pointInSceneCoords);

//    updateEndArrows();

    m_boundingRect = QRectF(m_start, m_end);
    update(m_boundingRect);
}

void ArrowItem::setEnd(const QPointF &pointInSceneCoords)
{
    m_end = mapFromScene(pointInSceneCoords);

//    updateEndArrows();

    m_boundingRect = QRectF(m_start, m_end);
    update(m_boundingRect);
}

void ArrowItem::updateEndArrows()
{
    m_firstArrowEnd = QLineF(m_end, m_start);
    m_firstArrowEnd.setLength(10);
    m_firstArrowEnd.setAngle(m_firstArrowEnd.angle() + 18);

    m_secondArrowEnd = QLineF(m_end, m_start);
    m_secondArrowEnd.setLength(10);
    m_secondArrowEnd.setAngle(m_secondArrowEnd.angle() - 18);
}

} // namespace Internal
} // namespace HeaderIncludeGraph
