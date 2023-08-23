#ifndef SITEADD_H
#define SITEADD_H
#include <QDialog>

#include "QAbstractButton"
#include "jsonModel.h"

namespace Ui {
class SiteAdd;
}

class SiteAdd : public QDialog {
  Q_OBJECT

 public:
  explicit SiteAdd(QWidget *parent = nullptr);
  ~SiteAdd();
  JsonModel::Row getInputValues() const;


 private:
  Ui::SiteAdd *ui;
};

#endif  // SITEADD_H
