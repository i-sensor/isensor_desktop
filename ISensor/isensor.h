#ifndef ISENSOR_H
#define ISENSOR_H

#include <QWidget>

class ISensor : public QWidget
{
    Q_OBJECT

public:
    ISensor(QWidget *parent = nullptr);
    ~ISensor();

private:
};
#endif // ISENSOR_H
