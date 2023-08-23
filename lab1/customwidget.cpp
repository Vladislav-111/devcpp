#include "customwidget.h"

#include "jsonModel.h"
#include "ui_customwidget.h"

CustomWidget::CustomWidget(QString pass, QWidget *parent)
    : QWidget(parent), ui(new Ui::CustomWidget) {
  ui->setupUi(this);

  this->pass = pass;

}

CustomWidget::~CustomWidget() { delete ui; }

void CustomWidget::setText(const JsonModel::Row row) {
  ui->labelURL->setText(row.url);
  ui->labelLogin->setText(row.login);
  ui->labelPass->setText(row.pass);
}

void CustomWidget::on_toolButton_clicked() {

  JsonModel db(this->pass);
  JsonModel::Row row = {ui->labelURL->text(), ui->labelLogin->text(),
                      ui->labelPass->text()};

  if (!CustomWidget::show) {
    ui->labelLogin->setEchoMode(QLineEdit::Normal);
    ui->labelPass->setEchoMode(QLineEdit::Normal);
    JsonModel::Row dRow = db.decrypt(row);
    ui->labelLogin->setText(dRow.login);
    ui->labelPass->setText(dRow.pass);

    CustomWidget::show = true;
  } else {
    ui->labelLogin->setEchoMode(QLineEdit::Password);
    ui->labelPass->setEchoMode(QLineEdit::Password);

    JsonModel::Row eRow = db.encrypt(row);
    ui->labelLogin->setText(eRow.login);

    ui->labelPass->setText(eRow.pass);

    CustomWidget::show = false;
  }
}

JsonModel::Row CustomWidget::getRow() {
  JsonModel::Row row;
  row.login = ui->labelLogin->text();
  row.url = ui->labelURL->text();
  row.pass = ui->labelPass->text();
  return row;
}
