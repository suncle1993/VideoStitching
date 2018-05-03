#ifndef VIDEOSTITCHING_H
#define VIDEOSTITCHING_H

#include <QWidget>
#include "twocamsvideostitching.h"
#include "threecamsviderostitching.h"
#include "fourcamsvideostitching.h"
namespace Ui {
class videoStitching;
}

class videoStitching : public QWidget
{
    Q_OBJECT

public:
    explicit videoStitching(QWidget *parent = 0);
    ~videoStitching();

private slots:

    void on_twoCamsVideoStitchingBtn_clicked();

    void on_threeCamsVideoStitchingBtn_clicked();

    void on_fourCamsVideoStitchingBtn_clicked();

private:
    Ui::videoStitching *ui;
};

#endif // VIDEOSTITCHING_H
