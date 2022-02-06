#ifndef TEXTWINDOW_H
#define TEXTWINDOW_H
#include "Headers/mainwindow.h"
#include "Headers/commands.h"
#include <QFrame>
#include <QString>

namespace Ui {
class TextWindow;
}

class TextWindow : public QFrame
{
    Q_OBJECT

public:
    static TextWindow* getInstance();
    //explicit TextWindow(QWidget *parent = nullptr);
    void setInputMaxSize(const int size);
    QStringList getDataList();
    QStringList getKeyA();
    QStringList getKeyB();
    BYTE* getInput();
    int getTextAreaSelect();
    void setTextAreaSelect(int selection);
    void setTextWindowTextReadOnly(const bool choice);
    void setTextAsAscii(const QString &textValue);
    void clearTextWindowText();

    ~TextWindow();


public slots:
    void on_textWindowOK_clicked();

private:
    static TextWindow *instance;
    TextWindow();
    Ui::TextWindow *ui;
    QString m_inputText;
    BYTE* m_inputByte;
    QStringList m_dataList;
    int m_selectArea;
    QStringList m_keyAList;
    QStringList m_keyBList;
    QString m_textValue;



signals:
    void listIsReady();
    void keyAisReady();
    void keyBisReady();

};

#endif // TEXTWINDOW_H
