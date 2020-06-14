#include "buttnew.h"
#include <QPixmap>
buttnew::buttnew(QString pix):QPushButton (0){
    QPixmap pixmap(pix);
    this->setFixedSize(pixmap.width(),pixmap.height());
    this->setStyleSheet("QPushButton{border:Opx;}");
    this->setIcon(pixmap);
    this->setIconSize(QSize(pixmap.width(),pixmap.height()));
    this->setContextMenuPolicy(Qt::ActionsContextMenu);//×¢²á²Ëµ¥
    QAction *action1=new QAction(this);
    action1->setText("new tower");
    this->addAction(action1);
    connect(action1,&QAction::triggered,this,[=](){
        emit chooseac1();
    });
}
