#ifndef HEADERINCLUDEGRAPH_TREEVIEW_H
#define HEADERINCLUDEGRAPH_TREEVIEW_H

#include <QObject>

QT_BEGIN_NAMESPACE
class QGraphicsScene;
class QGraphicsView;
QT_END_NAMESPACE

namespace HeaderIncludeGraph {
namespace Internal {

class TreeViewItem;
class TreeViewWindow;

class TreeView : public QObject
{
public:
    TreeView(QWidget *parent = 0);
    void setRootItem(TreeViewItem *root);
    void showView(bool show);

private:
    TreeViewItem *m_root;
    QGraphicsScene *m_scene;
    QGraphicsView *m_view;
    TreeViewWindow *m_window;
};

} // namespace Internal
} // namespace HeaderIncludeGraph

#endif // HEADERINCLUDEGRAPH_TREEVIEW_H
