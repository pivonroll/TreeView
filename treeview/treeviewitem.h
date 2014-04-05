#ifndef HEADERINCLUDEGRAPH_TREEVIEWITEM_H
#define HEADERINCLUDEGRAPH_TREEVIEWITEM_H

#include <QGraphicsItem>
#include <QFont>

namespace HeaderIncludeGraph {
namespace Internal {

class TreeViewLayout;

class TreeViewItem : public QGraphicsItem
{
public:
    TreeViewItem();

    // QGraphicsItem interface
    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void addChildItem(TreeViewItem *item);
    TreeViewLayout *layout() const;

    QString displayText() const;
    void setDisplayText(const QString &displayText);

    // QGraphicsItem interface
protected:
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);

private:
    QString m_displayText;
    QString m_toolTipText;
    QRectF m_boundingRect;
    QFont m_font;
    QPainterPath m_path;
    TreeViewLayout *m_layout;
};

} // namespace Internal
} // namespace HeaderIncludeGraph

#endif // HEADERINCLUDEGRAPH_TREEVIEWITEM_H
