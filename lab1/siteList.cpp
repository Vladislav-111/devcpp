#include "siteList.h"

#include <QListWidget>
#include <QListWidgetItem>

#include "QFile"
#include "QJsonArray"
#include "QJsonDocument"
#include "QJsonObject"
#include "siteAdd.h"
#include "customwidget.h"
#include "jsonModel.h"
#include "qaesencryption.h"
#include "ui_siteList.h"

SiteList::SiteList(QString key, QWidget *parent)  // передаем ключ в это окно
    : QDialog(parent), ui(new Ui::SiteList) {
  ui->setupUi(this);
  this->key = key;
  qInfo() << "key in acclist" << this->key;
  JsonModel db(this->key);
  auto json = db.json;
  for (int i = 0; i < json.size(); ++i) { // добовляем запись построчно
    this->addRow(db.getRow(i));
  }
}

SiteList::~SiteList() { delete ui; }

void SiteList::showItem(const QString &text) {

}

void SiteList::addRow(const JsonModel::Row row) {  // добавление записей в GUI
  auto item = new QListWidgetItem();
  auto widget = new CustomWidget(key, this);
  widget->setText(row);
  item->setSizeHint(widget->sizeHint());
  ui->listWidget->addItem(item);
  ui->listWidget->setItemWidget(item, widget);
}

void SiteList::on_addAccBtn_clicked() {  // добавление записей в json
  SiteAdd NewWindow;
  NewWindow.setModal(true);
  if (NewWindow.exec() == QDialog::Accepted) {
    auto row = NewWindow.getInputValues();

    JsonModel db(this->key);
    auto eRow = db.encrypt(row);
    this->addRow(eRow);

    db.writeRowToJSON(eRow);
  }
}

void SiteList::on_searchButton_clicked() { // поиск
  auto searchText = ui->searchInput->text();

  auto listWidget = this->ui->listWidget;

  for (auto i = 0; i < listWidget->count(); i++) {
    auto item = listWidget->item(i);
    auto itemWidget =
        dynamic_cast<CustomWidget *>(ui->listWidget->itemWidget(item));
    if (itemWidget->getRow().url.startsWith(searchText)) {
      item->setHidden(false);
    } else {
      item->setHidden(true);
    }
  }
}
