#include "treeviewitem.h"

#include <QToolTip>
#include <QPainter>
#include <QFontMetricsF>
#include <QFileInfo>
#include <QGraphicsSceneHoverEvent>
#include <QApplication>

#include "arrowitem.h"
#include "treeviewlayout.h"

namespace HeaderIncludeGraph {
namespace Internal {

int ROUND_ITEM_X = 5;
int ROUND_ITEM_Y = 5;
int HEIGHT_ADDITION = 10;
int WIDTH_ADDITION = 10;
int TOOLTIP_GAP = 5;

TreeViewItem::TreeViewItem()
{
    setAcceptHoverEvents(true);

    m_layout = new TreeViewLayout(this);

    m_font = QApplication::font();
    m_font.setPixelSize(16);
}

QRectF TreeViewItem::boundingRect() const
{
    return m_boundingRect;
}

QPainterPath TreeViewItem::shape() const
{
    return m_path;
}

void TreeViewItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing, true);
    painter->fillPath(m_path, QColor(Qt::yellow));

    QPen pen;
    pen.setWidth(3);
    pen.setColor(Qt::black);
    painter->setPen(pen);
    painter->drawPath(m_path);

    painter->setPen(pen);
    painter->setFont(m_font);
    painter->drawText(m_boundingRect, Qt::AlignHCenter | Qt::AlignVCenter, m_displayText);
}

void TreeViewItem::addChildItem(TreeViewItem *item)
{
    if (!item)
        return;

    if (item == this)
        return;

    item->setParentItem(this);

    if (m_layout) {
        m_layout->addItemConnection(item);
        m_layout->updateLayout();
    }
}

TreeViewLayout *TreeViewItem::layout() const
{
    return m_layout;
}

QString TreeViewItem::displayText() const
{
    return m_displayText;
}

void TreeViewItem::setDisplayText(const QString &displayText)
{
    m_displayText = displayText;
    QFontMetricsF fm(m_font);
    m_boundingRect = QRectF(0, 0 , fm.width(m_displayText) + WIDTH_ADDITION, fm.height() + HEIGHT_ADDITION);

    m_path = QPainterPath();
    m_path.addRoundedRect(m_boundingRect, ROUND_ITEM_X, ROUND_ITEM_Y);
}

void TreeViewItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    if (sceneBoundingRect().contains(event->scenePos()))
        QToolTip::showText(event->screenPos(), toolTip(), event->widget());
}

} // namespace Internal
} // namespace HeaderIncludeGraph
