#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QProcess>
#include "diagramitem.h"
#include "diagramscene.h"

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

private slots:
    void on_PB_close_clicked();

    void on_PB_reset_clicked();

private:
    Ui::Dialog *ui;
    DiagramScene *scene;
};

#endif // DIALOG_H
