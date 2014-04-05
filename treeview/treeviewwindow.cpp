#include "treeviewwindow.h"
#include "ui_treeviewwindow.h"

namespace HeaderIncludeGraph {
namespace Internal {

TreeViewWindow::TreeViewWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TreeViewWindow)
{
    ui->setupUi(this);
}

TreeViewWindow::~TreeViewWindow()
{
    delete ui;
}

} // namespace Internal
} // namespace HeaderIncludeGraph
