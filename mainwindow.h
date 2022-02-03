#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QString text_;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    //void on_connectPressed();
private slots:


    void on_connectReader_clicked();

    void on_ConnectUID_clicked();

signals:
   //    void connectedReaderChanged(const QString &text);


private:
    Ui::MainWindow *ui;

};
#endif // MAINWINDOW_H
