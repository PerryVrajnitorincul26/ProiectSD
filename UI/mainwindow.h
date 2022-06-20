#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QStringListModel>
#include <QStringList>
#include <QLabel>
#include <QPixmap>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QStringListModel *filepaths;
    QStringList actualList;
    QStringList *toCompare;
    QModelIndex lastSelection;
    QImage *internalImage;
    QLabel *previewLabel;
    QLabel *compareLabel;

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

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
