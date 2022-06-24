#ifndef INTERFACE_H
#define INTERFACE_H

#include <QObject>
#include <QWidget>

class interface : public QWidget
{
    Q_OBJECT
public:
    explicit interface(QWidget *parent = nullptr);

signals:

};

#endif // INTERFACE_H
