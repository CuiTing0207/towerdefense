#ifndef BUTTNEW_H
#define BUTTNEW_H

#include <QWidget>
#include <QPushButton>
#include <QAction>

class buttnew : public QPushButton
{
    Q_OBJECT
public:
    buttnew(QString Pix);

signals:
     void chooseac1();

public slots:
};

#endif // BUTTNEW_H
