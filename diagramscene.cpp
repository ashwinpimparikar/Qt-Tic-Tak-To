/****************************************************************************
**
** Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Digia Plc and its Subsidiary(-ies) nor the names
**     of its contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "diagramscene.h"

#include <QTextCursor>
#include <QGraphicsSceneMouseEvent>

//! [0]
DiagramScene::DiagramScene(QObject *parent)
    : QGraphicsScene(parent)
{
    resetScene();
}
//! [0]

//! [1]

//! [1]

void DiagramScene::resetScene()
{
    myItemColor = Qt::white;
    for(int i=0;i<9;i++)
    {
        DiagramItem *item;
        int x = 100 * i;
        int y = 0;

        item = new DiagramItem();
        item->setBrush(QColor(255,255,255));

        addItem(item);
        item->setData(88,QString("l"));
        item->setData(99,QString::number(i));
        if(i>2 && i<6)
        {
            x = x - 300;
            y=100;
        }
        else if(i>4)
        {
            x = x - 600;
            y=200;
        }
        item->setPos(x, y);

        emit itemInserted(item);
    }
}

//! [3]
void DiagramScene::setItemColor(const QColor &color)
{
    myItemColor = color;
    if (isItemChange(DiagramItem::Type)) {
        DiagramItem *item = qgraphicsitem_cast<DiagramItem *>(selectedItems().first());
        item->setBrush(myItemColor);
    }
}
//! [3]

//! [6]
void DiagramScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    QGraphicsScene::mousePressEvent(mouseEvent);
}
//! [9]

//! [10]

//! [10]

void DiagramScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    foreach (QGraphicsItem *itm, items()) {
        if(itm->isSelected())
        {
            QBrush q;
            DiagramItem *item = qgraphicsitem_cast<DiagramItem *>(itm);
            if(myItemColor == Qt::white)
            {
                q.setTextureImage(QImage(":/x.png"));
                myItemColor = Qt::black;
                item->setData(88,QString("X"));
            }
            else
            {
                q.setTextureImage(QImage(":/o.png"));
                myItemColor = Qt::white;
                item->setData(88,QString("O"));
            }
            item->setBrush(q);
            item->setFlag(QGraphicsItem::ItemIsSelectable, false);
            item->update();
        }
    }
    bool stat = checkMatrix();

    QGraphicsScene::mouseReleaseEvent(mouseEvent);
}

bool DiagramScene::checkMatrix()
{
    QList<QGraphicsItem*>itemList;
    itemList = items(0,0,300,50,Qt::IntersectsItemShape, Qt::AscendingOrder);
    if(getLineStat(itemList))
        return true;

    itemList = items(0,0,50,300,Qt::IntersectsItemBoundingRect, Qt::AscendingOrder);
    if(getLineStat(itemList))
        return true;

    itemList = items(0,110,300,50,Qt::IntersectsItemBoundingRect, Qt::AscendingOrder);
    if(getLineStat(itemList))
        return true;

    itemList = items(110,0,50,300,Qt::IntersectsItemBoundingRect, Qt::AscendingOrder);
    if(getLineStat(itemList))
        return true;

    itemList = items(0,210,300,50,Qt::IntersectsItemBoundingRect, Qt::AscendingOrder);
    if(getLineStat(itemList))
        return true;

    itemList = items(210,0,50,300,Qt::IntersectsItemBoundingRect, Qt::AscendingOrder);
    if(getLineStat(itemList))
        return true;

    itemList.clear();
    itemList << itemAt(QPointF(250,50),QTransform()) << itemAt(QPointF(150,150),QTransform()) << itemAt(QPointF(50,250),QTransform());
    if(getLineStat(itemList))
            return true;

    itemList.clear();
    itemList << itemAt(QPointF(50,50),QTransform()) << itemAt(QPointF(150,150),QTransform()) << itemAt(QPointF(250,250),QTransform());
    if(getLineStat(itemList))
            return true;

    return false;
}

bool DiagramScene::getLineStat(QList<QGraphicsItem*>itemList)
{
    if(itemList.at(0)->data(88).toString() != "l")
    {
        if(itemList.at(0)->data(88) == itemList.at(1)->data(88) && itemList.at(1)->data(88) == itemList.at(2)->data(88))
        {
            itemList.at(0)->setData(77,"Final");
            itemList.at(1)->setData(77,"Final");
            itemList.at(2)->setData(77,"Final");
            update();
            return true;
        }
        else
            return false;
    }
    return false;
}

//! [11]

//! [13]

//! [14]
bool DiagramScene::isItemChange(int type)
{
    foreach (QGraphicsItem *item, selectedItems()) {
        if (item->type() == type)
            return true;
    }
    return false;
}
//! [14]

//! [15]
void DiagramScene::drawBackground(QPainter *painter, const QRectF &rect)
{
    int step = 2;
    int tmp = int(rect.top()) + step /2;
    tmp -= tmp % step;

    int start = tmp;
    if (start > rect.top()) {
        start -= step;
    }

    for (int y = start; y < rect.bottom(); )
    {
        for( int i = rect.left(); i <= rect.right(); i+=2)
        {
            if(y%100 == 0)
            painter->drawPoint( i, y );
            if(i%100==0)
                painter->drawPoint( i, y );
        }
        y+=2;//= 100;
    }

}


//! [15]

