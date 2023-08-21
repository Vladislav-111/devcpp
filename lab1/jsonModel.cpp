#include "jsonModel.h"

#include <iostream>

#include "QDebug"
#include "QFile"
#include "QJsonArray"
#include "QJsonDocument"
#include "QJsonObject"
//#include "crypt.h"

JsonModel::JsonModel(const QString key) {
  this->key = key;
  this->file = readFile();
  this->json = readJson(key);
}
const QString JsonModel::kFileName = "encoded.json";

QJsonArray JsonModel::readJson(QString key) {  // парсинг json
  auto decodedFile = Crypt::decrypt(this->file, key, key);

  auto start = decodedFile.indexOf("\n");
  auto jsonStr = decodedFile.sliced(start, decodedFile.length() - start);

  QJsonDocument d = QJsonDocument::fromJson(jsonStr.toUtf8());
  QJsonArray json = d.QJsonDocument::array();
  qDebug() << d;
  return json;
}

QByteArray JsonModel::readFile() { // чтение файла
  QFile file(JsonModel::kFileName);

  file.open(QIODevice::ReadWrite | QIODevice::Text);
  auto readedFile = file.readAll();

  file.close();
  return readedFile;
}
