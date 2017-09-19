#ifndef ABOUTMECLERKPART_H
#define ABOUTMECLERKPART_H

#include <QWidget>
#include "clerk.h"

namespace Ui {
class AboutMeClerkPart;
}

class AboutMeClerkPart : public QWidget
{
    Q_OBJECT

public:
    explicit AboutMeClerkPart(const Clerk &clerk, QWidget *parent = 0);
    ~AboutMeClerkPart();

private:
    Ui::AboutMeClerkPart *ui;
};

#endif // ABOUTMECLERKPART_H
