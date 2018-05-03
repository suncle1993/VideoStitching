#include "videostitching.h"
#include "ui_videostitching.h"

videoStitching::videoStitching(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::videoStitching)
{
    ui->setupUi(this);
}

videoStitching::~videoStitching()
{
    delete ui;
}

void videoStitching::on_twoCamsVideoStitchingBtn_clicked()
{
    twoCamsVideoStitching *twoC=new twoCamsVideoStitching();
    twoC->show();
}

void videoStitching::on_threeCamsVideoStitchingBtn_clicked()
{
    threeCamsVideroStitching *threeC=new threeCamsVideroStitching();
    threeC->show();
}

void videoStitching::on_fourCamsVideoStitchingBtn_clicked()
{
    fourCamsVideoStitching *fourC=new fourCamsVideoStitching();
    fourC->show();
}
