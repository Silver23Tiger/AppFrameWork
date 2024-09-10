#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QTextStream>
#include <QCoreApplication>
#include <QDebug>
#include <QPixmap>
#include <QVector>
#include <QLabel>
#include "qcustomplot.h"
QVector<QString> data1;
QVector<QString> data2;
QVector<QString> data3;
QString Conv;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)

{
    ui->setupUi(this);
}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString filePath = QCoreApplication::applicationDirPath() + "/2024-08-29_12-13-43_PFile_HAL.csv";
    qDebug() << "File path:" << filePath;
    QFile csvfile(filePath);
    QTextStream stream(&csvfile);
    QVector<QStringList> data;
    if (csvfile.open(QIODevice::ReadWrite))
    {
        while(stream.atEnd() == false )
        {
            QString line = stream.readLine();
            QStringList fields = line.split(',');  // Split line by comma
            data.append(fields);
        }
    }
    else
    {
        qDebug() << "Failed to open file:" << filePath;
    }

    int Col1 = ui->lineEdit->text().toInt();
    QVector<QString> recData = filterData(data,Col1);
    QVector<double> X(recData.size());
    QVector<double> Y(recData.size());

    QCustomPlot *customPlot = new QCustomPlot(this);
    // qDebug() << recData;
    // initialize with entries 0..100
    X = vectorTOdouble(X,recData);
    for(int i = 0 ; i< X.size();i++)
    {
           Y[i] = i;
    }

    customPlot->addGraph();
    customPlot->graph(0)->setData(Y,X);
    customPlot->graph(0)->setLineStyle(QCPGraph::lsLine);
    // give the axes some labels:
    customPlot->xAxis->setLabel("x");
    customPlot->yAxis->setLabel("y");
    customPlot->xAxis->setRange(*std::min_element(Y.begin(), Y.end()), *std::max_element(Y.begin(), Y.end()));
    customPlot->yAxis->setRange(*std::min_element(X.begin(), X.end()), *std::max_element(X.begin(), X.end()));
    ui->verticalLayout->addWidget(customPlot);

}

QVector<QString> MainWindow::filterData(const QVector<QStringList> &list, const int Col1)
{
    // Collect data from specified columns
    for (int i = 0; i < list.size(); ++i)
    {
        if (list[i].size() > Col1) // Check if columns are available in the row
        {
            data1.append(list[i][Col1]);
        }
    }
 return data1;
}
QVector<double> MainWindow::vectorTOdouble(QVector<double> fa,QVector<QString> fb)
{
    for(int i = 0 ; i < fb.size();i++)
    {
        fa[i] = fb[i].toDouble();

    }
    return fa;
}
void MainWindow::on_label_linkActivated(const QString &link)
{

}
