#include "mywidget.h"
#include "ui_mywidget.h"
#include <QTextStream>
#include <QFile>
#include <QDebug>
#include <QDir>
#include <QFileDialog>

QString mFilename = "C:/Users/文洋/Desktop/課程or作業/大二/視窗程式設計/contact/contact.txt";

void Write(QString Filename,QString str)
{
    QFileInfo fileInfo(Filename);
    QDir().mkpath(fileInfo.absolutePath());

    QFile mFile(Filename);
    if(!mFile.open(QFile::WriteOnly | QFile::Text)){
        qDebug()<<"could not open file for write";
        return;
    }

    QTextStream out(&mFile);
    out<<str;
    mFile.flush();
    mFile.close();
}

MyWidget::MyWidget(QWidget *parent)
    : QWidget(parent), ui(new Ui::MyWidget)
{
    ui->setupUi(this);
    ui->tableWidget->setColumnCount(4);
    QStringList ColTotle;
    ColTotle<<QStringLiteral("學號")<<QStringLiteral("班級")<<QStringLiteral("姓名")<<QStringLiteral("電話");
    ui->tableWidget->setHorizontalHeaderLabels(ColTotle);
}

MyWidget::~MyWidget()
{
    delete ui;
}


void MyWidget::on_insertButton_clicked()
{
    QTableWidgetItem *inputRow1,*inputRow2,*inputRow3,*inputRow4;
    inputRow1 = new QTableWidgetItem(QString(ui->lineEdit_6->text()));
    inputRow2 = new QTableWidgetItem(QString(ui->lineEdit_7->text()));
    inputRow3 = new QTableWidgetItem(QString(ui->lineEdit_8->text()));
    inputRow4 = new QTableWidgetItem(QString(ui->lineEdit_9->text()));

    ui->tableWidget->insertRow(ui->tableWidget->rowCount());

    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,0,inputRow1);
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,1,inputRow2);
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,2,inputRow3);
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,3,inputRow4);
}


void MyWidget::on_exportButton_clicked()
{
    QString saveFile="";

    for(int i=0;i<ui->tableWidget->rowCount();i++){
        for(int j=0;j<ui->tableWidget->columnCount();j++){
            saveFile+=ui->tableWidget->item(i,j)->text()+",";
        }
        saveFile+="\n";
    }
    Write(mFilename,saveFile);
}
void MyWidget::on_importButton_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(this, "選擇匯入檔案", "C:/Users/文洋/Desktop", "Text Files (*.txt *.csv);;All Files (*.*)");

    if (filePath.isEmpty()) {
        return;
    }

    QFile file(filePath);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        qDebug() << "無法開啟檔案進行讀取";
        return;
    }
    ui->tableWidget->setRowCount(0);
    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        if (line.trimmed().isEmpty()) continue;

        QStringList fields = line.split(",");

        int currentRow = ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(currentRow);

        for (int i = 0; i < fields.size() && i < ui->tableWidget->columnCount(); ++i) {
            ui->tableWidget->setItem(currentRow, i, new QTableWidgetItem(fields[i]));
        }
    }

    file.close();
    qDebug() << "檔案匯入成功！";
}
