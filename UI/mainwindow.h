#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QStringListModel>
#include <QStringList>
#include <QLabel>
#include <QPixmap>
#include <Logic/ImToQuadTree.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QStringListModel *filepaths;
    QStringListModel *difKeyModel;
    QStringList actualList;
    QStringList *difKeyList;
    QStringList *lastSelection;
    QImage *internalImage;
    QLabel *previewLabel;
    QLabel *compareLabel;
    ///Easier to use then copting the existing QString hash function to work like std::hash
    QHash<QString,ImToQuadTree<cv::Vec3b> *> knownImages;
    QHash<QString,std::vector<std::pair<cv::Point, cv::Point>>>knownDiffs;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void setImage(QString newimg);


private slots:
    void on_LoadSingleImage_clicked();

    void on_SaveSelectedFiles_clicked();

    void on_listView_clicked(const QModelIndex &index);

    void on_compareView_clicked(const QModelIndex &index);

    void on_removeSelected_clicked();

    void on_compareSelection_clicked();

    void on_createComparison_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
