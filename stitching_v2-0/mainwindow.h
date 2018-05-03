#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "imagestitching.h"
#include "videostitching.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_imageStitchingBtn_clicked();

    void on_videoStitchingBtn_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
