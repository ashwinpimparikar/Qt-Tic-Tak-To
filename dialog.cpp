#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    scene = new DiagramScene(this);
    ui->graphicsView->setGeometry(0,0,302,302);
    scene->setSceneRect(QRectF(0, 0, 300, 300));
    connect(scene, SIGNAL(itemInserted(DiagramItem*)),
            this, SLOT(itemInserted(DiagramItem*)));
    connect(scene, SIGNAL(itemSelected(QGraphicsItem*)),
            this, SLOT(itemSelected(QGraphicsItem*)));
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setAlignment(Qt::AlignTop|Qt::AlignLeft);

    //QProcess strt;
    //strt.start("FloatingCloseButton.exe");
 //   ui->graphicsView->setSceneRect(250,250,500,500);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_PB_close_clicked()
{
    this->close();
}

void Dialog::on_PB_reset_clicked()
{
    scene->clear();
    scene->resetScene();
}
