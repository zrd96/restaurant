#include "clerkwindow.h"
#include "ui_clerkwindow.h"

ClerkWindow::ClerkWindow(const QString &user, QWidget *parent) :
    QMainWindow(parent),
    clerk(Clerk("", "")),
    ui(new Ui::ClerkWindow)
{
    ui->setupUi(this);
    StaticData::db->doQuery("person", "name, password", "phone = \"" + user + "\"");
    clerk = Clerk(user,
                  StaticData::db->getResultList()[0][0],
            StaticData::db->getResultList()[0][1]);
    ui->submitTableButton->setEnabled(false);
    aboutMe = new AboutMeWidget(&clerk, this, ui->selfTab);
    aboutMe->show();
//    ui->readyDishList->setColumnWidth(0, 100);//chef
//    ui->readyDishList->setColumnWidth(0, 80);//table
//    ui->readyDishList->setColumnWidth(0, 100);//guest
//    ui->readyDishList->setColumnWidth(0, 180);//ODID
//    ui->readyDishList->setColumnWidth(0, 150);//name
//    ui->readyDishList->setColumnWidth(0, 180);//OD time
//    ui->readyDishList->setColumnWidth(0, 180);//finished time
//    ui->readyDishList->setColumnWidth(0, 60);//served
//    ui->readyDishList->resizeColumnsToContents();
//    ui->msgList->resizeColumnsToContents();
//    ui->msgList->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
//    ui->msgList->setColumnWidth(0, 200);
//    ui->msgList->setColumnWidth(1, 150);
//    ui->msgList->setColumnWidth(2, 550);
//    ui->msgList->setColumnWidth(3, 250);
    viewTableList();
    viewReadyDishList();
    viewMsgList();
}

ClerkWindow::~ClerkWindow()
{
    delete ui;
}

void ClerkWindow::viewTableList() {
    clearPointerList(tableItem);
    checkSelectedTables();
    for(unsigned int i = 0; i < StaticData::getTableList().size(); i ++) {
        if(i % 3 == 0 && ui->tableList->rowCount() <= (int)i/3)
            ui->tableList->setRowCount(ui->tableList->rowCount() + 1);
        int row = i / 3;
        int col = i % 3;
        TableItem* table = new TableItem(StaticData::getTableList()[i], ui->tableList);
        connect(table, SIGNAL(tableSelected(int)), this, SLOT(setSelectedTable(int)));
        ui->tableList->setCellWidget(row, col, table);
        for (unsigned int j = 0; j < clerk.getTableList().size(); j ++)
            if (clerk.getTableList()[j] == StaticData::getTableList()[i].getTableID()) {
                table->setEnabled(false);
                break;
            }
        if (StaticData::getTableList()[i].getSeats() == StaticData::getTableList()[i].getFreeSeats())
            table->setEnabled(false);
        tableItem.push_back(table);
    }
//    ui->tableList->setEnabled(ui->submitTableButton->isEnabled());
}

void ClerkWindow::setSelectedTable(int tableID) {
    ui->submitTableButton->setEnabled(true);
    selectedTable = tableID;
    checkSelectedTables();
    ui->selectedTable->setText(QString("%1 %2, please submit").arg(ui->selectedTable->text()).arg(tableID));
}

void ClerkWindow::on_submitTableButton_clicked()
{
    clerk.takeTable(StaticData::getTableByID(selectedTable));
    viewTableList();
    ui->submitTableButton->setEnabled(false);
}

void ClerkWindow::checkSelectedTables() {
    clerk.checkTable();
    if (clerk.getTableList().empty()) {
        ui->selectedTable->setText("Selected Table(s): None");
        return;
    }
    ui->selectedTable->setText(QString("Selected Table(s): No."));
    for (unsigned int i = 0; i < clerk.getTableList().size(); i ++)
        ui->selectedTable->setText(QString("%1 %2").arg(ui->selectedTable->text()).arg(clerk.getTableList()[i]));
}

void ClerkWindow::viewReadyDishList() {
    clerk.queryMsg();
    ui->readyDishList->setRowCount(0);
    for (unsigned int i = 0; i < clerk.getMsgList().size(); i ++) {
        Msg &cur = clerk.getMsgList()[i];
        if (cur.getMsg().contains("Dish ready")) {
            int row = ui->readyDishList->rowCount();
            ui->readyDishList->setRowCount(row + 1);
            QString orderedDishID = cur.getMsg().mid(11);
            OrderedDish &orderedDish = StaticData::getOrderedDishByID(orderedDishID);
            ui->readyDishList->setItem(row, 0, new QTableWidgetItem((cur.getSender())));
            ui->readyDishList->setItem(row, 1, new QTableWidgetItem(QString("Table %1").arg(orderedDish.getTable())));
            ui->readyDishList->setItem(row, 2, new QTableWidgetItem((orderedDish.getOrderer())));
            ui->readyDishList->setItem(row, 3, new QTableWidgetItem((orderedDish.getOrderedDishID())));
            ui->readyDishList->setItem(row, 4, new QTableWidgetItem((orderedDish.getName())));
            ui->readyDishList->setItem(row, 5, new QTableWidgetItem((orderedDish.getDatetime())));
            ui->readyDishList->setItem(row, 6, new QTableWidgetItem((cur.getDatetime())));
            QPushButton* serveButton = new QPushButton(ui->readyDishList);
            serveButton->setText("Serve");
            serveButton->resize(30, 30);
            if (!cur.getState()) {
                serveButton->setText("Finised");
                serveButton->setEnabled(false);
            }
            connect(serveButton, &QPushButton::clicked, this, [&, serveButton] {
                cur.readMsg();
                StaticData::modifyMsg(cur.getMsgID(), cur);
                orderedDish.setStatus(4);
                StaticData::modifyOrderedDish(orderedDish.getOrderedDishID(), orderedDish);
                serveButton->setText("Finished");
                serveButton->setEnabled(false);
            });
            ui->readyDishList->setCellWidget(row, 7, serveButton);
        }
    }
    ui->readyDishList->resizeColumnsToContents();
}

void ClerkWindow::viewMsgList() {
    clerk.queryMsg();
    ui->msgList->setRowCount(0);
    for (unsigned int i = 0; i < clerk.getMsgList().size(); i ++) {
        Msg &cur = clerk.getMsgList()[i];
        if (!cur.getMsg().contains("Dish ready")) {
            int row = ui->msgList->rowCount();
            ui->msgList->setRowCount(row + 1);
            ui->msgList->setItem(row, 0, new QTableWidgetItem((cur.getSender())));
            ui->msgList->setItem(row, 1, new QTableWidgetItem((cur.getReceiver())));
            ui->msgList->setItem(row, 2, new QTableWidgetItem((cur.getMsg())));
            ui->msgList->setItem(row, 3, new QTableWidgetItem((cur.getDatetime())));
        }
    }
    ui->msgList->resizeColumnsToContents();
}

void ClerkWindow::on_tabWidget_currentChanged(int index)
{
    if (index == 0)
        viewTableList();
    else if (index == 2)
        viewMsgList();
}

void ClerkWindow::on_refreshMsgButton_clicked()
{
    viewMsgList();
}
