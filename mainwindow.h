#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore>
#include <QVector>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
     QVector<QString> filterData(const QVector<QStringList> &list, const int Col1);
    QVector<double> vectorTOdouble(QVector<double> fa,QVector<QString> fb);

private slots:
    void on_pushButton_clicked();
    void on_label_linkActivated(const QString &link);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
