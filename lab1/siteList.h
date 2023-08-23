#ifndef SITELIST_H
#define SITELIST_H

#include <QDialog>

#include "jsonModel.h"

namespace Ui {
class SiteList;
}

class SiteList : public QDialog {
  Q_OBJECT

 public:
  explicit SiteList(QString key, QWidget *parent = nullptr);
  ~SiteList();
  QString key;

 private slots:
  void showItem(const QString &text);

  void addRow(const JsonModel::Row row);
  void on_addAccBtn_clicked();

  void on_searchButton_clicked();

private:
  Ui::SiteList *ui;
};

#endif  // SITELIST_H
