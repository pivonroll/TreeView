#ifndef HEADERINCLUDEGRAPH_INTERNAL_TREEVIEWWINDOW_H
#define HEADERINCLUDEGRAPH_INTERNAL_TREEVIEWWINDOW_H

#include <QDialog>

namespace HeaderIncludeGraph {
namespace Internal {

namespace Ui {
class TreeViewWindow;
}

class TreeViewWindow : public QDialog
{
    Q_OBJECT

public:
    explicit TreeViewWindow(QWidget *parent = 0);
    ~TreeViewWindow();

private:
    Ui::TreeViewWindow *ui;
};


} // namespace Internal
} // namespace HeaderIncludeGraph
#endif // HEADERINCLUDEGRAPH_INTERNAL_TREEVIEWWINDOW_H
