#ifndef COMMENT_H
#define COMMENT_H

#include <QWidget>
#include "rate.h"

namespace Ui {
class Comment;
}

class Comment : public QWidget
{
    Q_OBJECT

public:
    explicit Comment(const Rate& rate, QWidget *parent = 0);
    ~Comment();

private:
    Ui::Comment *ui;
};

#endif // COMMENT_H
