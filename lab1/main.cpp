#include "mainwindow.h"

#include <QApplication>

#include <windows.h>
#include <winbase.h>

#include <Tlhelp32.h>
#include <process.h>
#include <stdio.h>
#include <string.h>

#include <QApplication>

#include "QCryptographicHash"
#include "QDebug"
#include "QMessageBox"
#include "QProcess"
#include "QString"
#include "mainwindow.h"

#include <QFile>
typedef unsigned long long QWORD;


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);



    MainWindow w;
    w.show();

    // 1 Определение начала сегмента .text
    QWORD moduleBase = (QWORD)GetModuleHandleW(NULL); //начальный адрес приложения в виртуальной памяти/
    QWORD text_segment_start = moduleBase + 0x1000; //адрес сегмента .text/


    // 2 Определение длины сегмента .text
    PIMAGE_DOS_HEADER pIDH = reinterpret_cast<PIMAGE_DOS_HEADER>(moduleBase);
    PIMAGE_NT_HEADERS pINH = reinterpret_cast<PIMAGE_NT_HEADERS>(moduleBase+pIDH->e_lfanew);
    QWORD size_of_text = pINH->OptionalHeader.SizeOfCode;


    // 3 Подсчет хэша и его шифрование
    QByteArray text_segment_contents = QByteArray((char*)text_segment_start,size_of_text);
    QByteArray hash = QCryptographicHash::hash((text_segment_contents),QCryptographicHash::Sha256).toBase64();
    //qDebug() << "text_segment_contents = " << Qt::hex << text_segment_contents.first(100);
    qInfo() << "hash = " << hash;

    // 4 Сравнение хэша полученного на прошлых этапах с эталонным
    const QByteArray hash0_base64 = QByteArray("1dbHCKaw+sq+V6FUawIXu4r4skaqjoSBy8oDDQU1oRs=");
    bool checkresult =(hash==hash0_base64);


    // 5 Реакция на измененный хэш
    if(!checkresult){
      int result = QMessageBox::critical(nullptr,"Warning!","App has been patched");
      return -1, system("taskkill /im DebugProtector.exe /f");
    }

    return a.exec(), system("taskkill /im /f");
  }
