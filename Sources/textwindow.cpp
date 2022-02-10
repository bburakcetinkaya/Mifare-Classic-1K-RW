#include "Headers/textwindow.h"
#include "Headers/mainwindow.h"
#include "ui_textwindow.h"


#include <QDebug>
#include <QList>
#include <QString>

TextWindow* TextWindow::instance = NULL;
TextWindow* TextWindow::getInstance()
{
   if (instance == NULL) {
       instance = new TextWindow();
   }
   return(instance);
}
TextWindow::TextWindow() :
    //QFrame(parent),
    ui(new Ui::TextWindow)
{
    ui->setupUi(this);

}

TextWindow::~TextWindow()
{
    delete ui;
}
void TextWindow::setInputMaxSize(const int size)
{
    ui->textWindowText->setMaxLength(size);
}
BYTE* TextWindow::getInput()
{

    return m_inputByte;
}
void TextWindow::on_textWindowApply_clicked()
{
    QString inputText = ((ui->textWindowText->text()).toLocal8Bit());

    QByteArray hexText = QByteArray::fromHex((inputText.toLatin1()).toHex());

    BYTE hexTextByte[ui->textWindowText->maxLength()];
    for( int i=0 ; i<static_cast<int>(ui->textWindowText->maxLength()) ; i++ )
    {
        hexTextByte[i] = hexText[i];
    }
    hexText =  QByteArray(reinterpret_cast<char*>(hexTextByte), sizeof(hexTextByte)).toHex(' ').toUpper();
    inputText = QString(hexText);
    QStringList dataList = inputText.split(' ');
    switch (m_selectArea)
    {
        case 0:
            m_keyAList = dataList;
            emit keyAIsReady();

            break;
        case 1:
            m_keyBList = dataList;
            emit keyBIsReady();

            break;
        case 2:
            m_dataList = dataList;
            emit listIsReady();

            break;
        case 3:
            m_utilityKey = dataList;
            emit utilityKeyIsReady();

            break;

    }
    this->close();
    ui->textWindowText->clear();

}
QStringList TextWindow::getDataList()
{
    return m_dataList;
}
void TextWindow::setTextAreaSelect(int selection)
{
    m_selectArea = selection;
}
int TextWindow::getTextAreaSelect()
{
  return 0;
}
QStringList TextWindow::getKeyA()
{
    return m_keyAList;
}
QStringList TextWindow::getKeyB()
{
    return m_keyBList;
}
QStringList TextWindow::getUtilityKey()
{
    return m_utilityKey;
}
void TextWindow::setTextWindowTextReadOnly(const bool choice)
{
    ui->textWindowText->setReadOnly(choice);
}
void TextWindow::setTextAsAscii(const QString &textValue)
{
    m_textValue = textValue;
    ui->textWindowText->setText(m_textValue);

}
void TextWindow::clearTextWindowText()
{
    ui->textWindowText->clear();
}

void TextWindow::on_textWindowCancel_clicked()
{
    ui->textWindowText->clear();
    this->close();
}

