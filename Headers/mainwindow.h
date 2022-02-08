#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <winscard.h>
#include <Headers/commands.h>

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
    void printRawTable(const QVector<QStringList> &dataList, const bool formatSelect);
    QVector<QStringList> authAndReadAllData(const QByteArray &_keyBytes,const BYTE &storageSelect,
                                                                        const BYTE &keySelect);

private slots:

    void on_connectReader_clicked();
    void on_disconnectReader_clicked();
    void on_ConnectUID_clicked();
    void on_disconnectUID_clicked();

    void on_loadTo0A_clicked();
    void on_loadTo1A_clicked();
    void on_loadTo0B_clicked();
    void on_loadTo1B_clicked();

    void on_authWithKeyA_clicked();
    void on_authWithKeyB_clicked();

    void on_keyA5_textChanged();
    void on_keyA4_textChanged();
    void on_keyA3_textChanged();
    void on_keyA2_textChanged();
    void on_keyA1_textChanged();
    void on_keyA0_textChanged();

    void on_keyB5_textChanged();
    void on_keyB4_textChanged();
    void on_keyB3_textChanged();
    void on_keyB2_textChanged();
    void on_keyB1_textChanged();
    void on_keyB0_textChanged();

    void on_copyToKeyA_clicked();
    void on_copyToKeyB_clicked();

    void on_textKeyA_clicked();
    void on_textKeyB_clicked();

    void on_factoryKeyA_clicked();
    void on_factoryKeyB_clicked();

    void on_readBlock_clicked();
    void on_writeBlock_clicked();
    void on_RWClear_clicked();
    void on_textRWblocks_clicked();

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

    void on_rawGO_clicked();

    void applyDataFromTextWindow();
    void applyDataFromTextWindowToKeyB();
    void applyDataFromTextWindowToKeyA();
    void applyDataFromTextWindowToUtilityKey();

    void on_valueBlockWrite_clicked();
    void on_valueBlockInit_textChanged();

    void on_readVB_clicked();
    void on_decVB_clicked();
    void on_incVB_clicked();

    void on_utilityKCText_clicked();
    void on_utilityKCFactory_clicked();

    void on_utilityKC0_textChanged();
    void on_utilityKC1_textChanged();
    void on_utilityKC2_textChanged();
    void on_utilityKC3_textChanged();
    void on_utilityKC4_textChanged();
    void on_utilityKC5_textChanged();

    void on_utilityKCChange_clicked();

    void on_blockSelect_valueChanged(int arg1);
    void on_sectorSelect_valueChanged(int arg1);

    void on_sectorBegin_valueChanged(int arg1);

    void on_sectorEnd_valueChanged(int arg1);



    void on_commandsClear_clicked();

signals:
    //void listFromTextWindow(QStringList dataList);

private:
    Ui::MainWindow *ui;
    QString getKeyA();
    void setKeyA();

    QString getKeyB();
    void setKeyB();

    QString getUtilityKey();
    void setUtilityKey();


    QString getWriteBlocks();
    QString m_keyA;
    QString m_keyB;
    QString m_utilityKey;

};
#endif // MAINWINDOW_H
