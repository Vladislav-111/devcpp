#include "siteList.h"

#include <QListWidget>
#include <QListWidgetItem>

#include "QFile"
#include "QJsonArray"
#include "QJsonDocument"
#include "QJsonObject"
#include "jsonModel.h"
//#include "siteAdd.h"
//#include "customwidget.h"
//#include "qaesencryption.h"
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

}

void SiteList::on_addAccBtn_clicked() {  // добавление записей в файл json

}

void SiteList::on_searchButton_clicked() { // поиск

}
