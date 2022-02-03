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

private slots:


    void on_connectReader_clicked();
    void on_ConnectUID_clicked();

    void on_authWithKeyA_clicked();

    void on_keyA5_textChanged();

    void on_keyA4_textChanged();

    void on_keyA3_textChanged();

    void on_keyA2_textChanged();

    void on_keyA1_textChanged();

    void on_keyA0_textChanged();

    void on_copyToKeyB_clicked();

    void on_keyB5_textChanged();

    void on_keyB4_textChanged();

    void on_keyB3_textChanged();

    void on_keyB2_textChanged();

    void on_keyB1_textChanged();

    void on_keyB0_textChanged();

    void on_copyToKeyA_clicked();

    void on_factoryKeyA_clicked();

    void on_factoryKeyB_clicked();

    void on_readBlock_clicked();

signals:
   //    void connectedReaderChanged(const QString &text);


private:
    Ui::MainWindow *ui;

};
#endif // MAINWINDOW_H
