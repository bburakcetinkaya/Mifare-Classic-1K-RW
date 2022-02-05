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
    void setReadOnlyReadBlocks();
    void applyDataToReadBLocks(const QStringList &dataList);


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

    void on_loadTo0A_clicked();

    void on_RWClear_clicked();

    void on_R15_textChanged();

    void on_R14_textChanged();

    void on_R13_textChanged();

    void on_R12_textChanged();

    void on_R11_textChanged();

    void on_R10_textChanged();

    void on_R9_textChanged();

    void on_R8_textChanged();

    void on_R7_textChanged();

    void on_R6_textChanged();

    void on_R5_textChanged();

    void on_R4_textChanged();

    void on_R3_textChanged();

    void on_R2_textChanged();

    void on_R1_textChanged();

    void on_R0_textChanged();


    void on_writeBlock_clicked();

    void on_loadTo1A_clicked();

    void on_loadTo0B_clicked();

    void on_loadTo1B_clicked();

    void on_authWithKeyB_clicked();

    void on_ReleaseUID_clicked();

    void on_rawGO_clicked();

signals:
   //    void connectedReaderChanged(const QString &text);


private:
    Ui::MainWindow *ui;

};
#endif // MAINWINDOW_H
