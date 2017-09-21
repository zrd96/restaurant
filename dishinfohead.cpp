#include "dishinfohead.h"
#include "ui_dishinfohead.h"
#include "dish.h"
#include "rateitem.h"
#include "tools.h"
#include "staticdata.h"
#include <QFile>
#include <QFileDialog>

DishInfoHead::DishInfoHead(Dish &dish, bool isEditable, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DishInfoHead),
    imgdir("img/dishes/default.png"),
    dishID(dish.getDishID())
{
    ui->setupUi(this);
    QImage *dishImg = new QImage;
    if(!dishImg->load((dish.getImgDir())))
        dishImg->load("img/dishes/default.png");
    ui->dishImg->setPixmap(QPixmap::fromImage(*dishImg));
    ui->dishImg->setScaledContents(true);
    ui->dishName->setReadOnly(!isEditable);
    ui->dishIntro->setReadOnly(!isEditable);
    if (!isEditable) {
        this->resize(400, 300);
        ui->timeEdit->hide();
        ui->priceEdit->hide();
        ui->changeImgButton->hide();
        ui->submitButton->hide();
        ui->dishName->setPlainText((dish.getName()));
        ui->dishPrice->setText(QString("￥ %1").arg(dish.getPrice()));
        ui->dishIntro->setPlainText(dish.getIntro());
        ui->dishRateInfo->setText(QString("Rated %1/5 from %2 people").arg(dish.getRate()).arg(dish.getRateNum()));
        RateItem *rateItem = new RateItem(this);
        rateItem->setGeometry(130, 250, 150, 30);
        rateItem->setRate(dish.getRate());
        rateItem->show();
    }

    else {
        ui->dishRateInfo->hide();
        ui->changeImgButton->show();
        ui->dishPrice->setText("￥");
        ui->priceEdit->setPlaceholderText("Please input dish price");
        ui->dishName->setPlaceholderText("Please input dish name");
        ui->dishIntro->setPlaceholderText("Please input dish description");
        //ui->dishImg->setCursor(QCursor(Qt::PointingHandCursor));
        connect(ui->changeImgButton, &QPushButton::clicked, this, [this] {setDishImg();});
        connect(ui->submitButton, &QPushButton::clicked, this, [this] {submit();});
    }
    this->show();
}

DishInfoHead::~DishInfoHead()
{
    delete ui;
}

void DishInfoHead::setDishImg() {
    QString path = QFileDialog::getOpenFileName(this, tr("Open Image"), ".", tr("Image Files(*.jpg *.png *.bmp *.tif *.GIF)"));
    if (path.size() == 0)
        viewErrInfo("Empty file");
    else {
        imgdir = "img/dishes/" + dishID + "." + path.section('.', -1);
        QFile::copy(path, imgdir);
        QImage *dishImg = new QImage;
        if(!dishImg->load(imgdir)) {
            dishImg->load("img/dishes/default.png");
            viewErrInfo("Failed loading image, using default");
            imgdir = "img/dishes/default.png";
        }
        ui->dishImg->setPixmap(QPixmap::fromImage(*dishImg));
        ui->dishImg->setScaledContents(true);
    }
}

void DishInfoHead::submit() {

    if (ui->dishName->toPlainText().size() == 0) {
        viewErrInfo("Please input dish name");
        return;
    }
    bool checkNum = true;
    if (ui->priceEdit->text().toInt(&checkNum, 10) < 0 || !checkNum) {
        viewErrInfo("Invalid price");
        return;
    }
    if (ui->timeEdit->text().toDouble(&checkNum) < 0 || !checkNum) {
        viewErrInfo("Invalid time, setting to null");
        checkNum = false;
    }
    StaticData::modifyDish(dishID,
                           Dish(dishID,
                                ui->dishName->toPlainText(),
                                ui->dishIntro->toPlainText(),
                                ui->priceEdit->text().toDouble(),
                                (checkNum ? ui->timeEdit->text().toDouble() : -1), 0, 0,
                                imgdir));
    viewErrInfo(dishID);
    viewErrInfo("Success");
}
