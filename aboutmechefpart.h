#ifndef ABOUTMECHEFPART_H
#define ABOUTMECHEFPART_H

#include <QWidget>
#include "chef.h"

namespace Ui {
class AboutMeChefPart;
}

class AboutMeChefPart : public QWidget
{
    Q_OBJECT

public:
    explicit AboutMeChefPart(const Chef &chef, QWidget *parent = 0);
    ~AboutMeChefPart();

private:
    Ui::AboutMeChefPart *ui;
};

#endif // ABOUTMECHEFPART_H
