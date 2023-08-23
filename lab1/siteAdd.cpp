#include "siteAdd.h"

#include "jsonModel.h"
#include "ui_siteAdd.h"

SiteAdd::SiteAdd(QWidget *parent) : QDialog(parent), ui(new Ui::SiteAdd) {
  ui->setupUi(this);
}

SiteAdd::~SiteAdd() { delete ui; }
JsonModel::Row SiteAdd::getInputValues() const {
  QString Url = ui->inputUrl->text();
  QString Login = ui->inputLogin->text();
  QString Pass = ui->inputPass->text();
  JsonModel::Row row = {Url, Login, Pass};

  return row;
}
