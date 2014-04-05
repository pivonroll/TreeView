#ifndef HEADERINCLUDEGRAPH_TREEITEMCONNECTOR_H
#define HEADERINCLUDEGRAPH_TREEITEMCONNECTOR_H

#include <QtGlobal>

QT_BEGIN_NAMESPACE
class QPointF;
class QRectF;
QT_END_NAMESPACE

namespace HeaderIncludeGraph {
namespace Internal {

class TreeViewItem;
class ArrowItem;

class TreeItemConnector
{
public:
    TreeItemConnector(TreeViewItem *startItem, TreeViewItem *endItem);
    ~TreeItemConnector();

    TreeViewItem *startItem() const;
    TreeViewItem *endItem() const;
    void update();
private:
    void createArrowItem();
    QPointF calculateStartPoint();
    QPointF calculateEndPoint();

    TreeViewItem *m_startItem;
    TreeViewItem *m_endItem;
    ArrowItem *m_arrowItem;
};

} // namespace Internal
} // namespace HeaderIncludeGraph

#endif // HEADERINCLUDEGRAPH_TREEITEMCONNECTOR_H
