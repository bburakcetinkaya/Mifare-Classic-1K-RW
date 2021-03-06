#include "Headers/mainwindow.h"
#include "Sources/mainwindow.cpp"
#include "Headers/commands.h"
// get input
QString MainWindow::getKeyA()
{

    return m_keyA;
}
QString MainWindow::getKeyB()
{

    return m_keyB;
}
void MainWindow::setKeyA()
{
    QString _keyA;
    _keyA.append ( (ui->keyA5->toPlainText()).toUtf8() );
    _keyA.append ( (ui->keyA4->toPlainText()).toUtf8() );
    _keyA.append ( (ui->keyA3->toPlainText()).toUtf8() );
    _keyA.append ( (ui->keyA2->toPlainText()).toUtf8() );
    _keyA.append ( (ui->keyA1->toPlainText()).toUtf8() );
    _keyA.append ( (ui->keyA0->toPlainText()).toUtf8() );
    m_keyA = _keyA;
}
void MainWindow::setKeyB()
{
    QString _keyB;
    _keyB.append ( (ui->keyB5->toPlainText()).toUtf8() );
    _keyB.append ( (ui->keyB4->toPlainText()).toUtf8() );
    _keyB.append ( (ui->keyB3->toPlainText()).toUtf8() );
    _keyB.append ( (ui->keyB2->toPlainText()).toUtf8() );
    _keyB.append ( (ui->keyB1->toPlainText()).toUtf8() );
    _keyB.append ( (ui->keyB0->toPlainText()).toUtf8() );
    m_keyB = _keyB;
}
void MainWindow::setUtilityKey()
{
    QString _key;
    _key.append ( (ui->utilityKC5->toPlainText()).toUtf8() );
    _key.append ( (ui->utilityKC4->toPlainText()).toUtf8() );
    _key.append ( (ui->utilityKC3->toPlainText()).toUtf8() );
    _key.append ( (ui->utilityKC2->toPlainText()).toUtf8() );
    _key.append ( (ui->utilityKC1->toPlainText()).toUtf8() );
    _key.append ( (ui->utilityKC0->toPlainText()).toUtf8() );
     m_utilityKey = _key;
}
QString MainWindow::getUtilityKey()
{
    return m_utilityKey;
}
QString MainWindow::getWriteBlocks()
{
    QString _writeBlock;
    _writeBlock.append ( (ui->R15->toPlainText()).toUtf8() );
    _writeBlock.append ( (ui->R14->toPlainText()).toUtf8() );
    _writeBlock.append ( (ui->R13->toPlainText()).toUtf8() );
    _writeBlock.append ( (ui->R12->toPlainText()).toUtf8() );
    _writeBlock.append ( (ui->R11->toPlainText()).toUtf8() );
    _writeBlock.append ( (ui->R10->toPlainText()).toUtf8() );
    _writeBlock.append ( (ui->R9 ->toPlainText()).toUtf8() );
    _writeBlock.append ( (ui->R8 ->toPlainText()).toUtf8() );
    _writeBlock.append ( (ui->R7 ->toPlainText()).toUtf8() );
    _writeBlock.append ( (ui->R6 ->toPlainText()).toUtf8() );
    _writeBlock.append ( (ui->R5 ->toPlainText()).toUtf8() );
    _writeBlock.append ( (ui->R4 ->toPlainText()).toUtf8() );
    _writeBlock.append ( (ui->R3 ->toPlainText()).toUtf8() );
    _writeBlock.append ( (ui->R2 ->toPlainText()).toUtf8() );
    _writeBlock.append ( (ui->R1 ->toPlainText()).toUtf8() );
    _writeBlock.append ( (ui->R0 ->toPlainText()).toUtf8() );
    return _writeBlock;
}
// key ops
void MainWindow::on_copyToKeyA_clicked()
{
    ui->keyA0->setPlainText(ui->keyB0->toPlainText());
    ui->keyA1->setPlainText(ui->keyB1->toPlainText());
    ui->keyA2->setPlainText(ui->keyB2->toPlainText());
    ui->keyA3->setPlainText(ui->keyB3->toPlainText());
    ui->keyA4->setPlainText(ui->keyB4->toPlainText());
    ui->keyA5->setPlainText(ui->keyB5->toPlainText());
}
void MainWindow::on_copyToKeyB_clicked()
{
    ui->keyB0->setPlainText(ui->keyA0->toPlainText());
    ui->keyB1->setPlainText(ui->keyA1->toPlainText());
    ui->keyB2->setPlainText(ui->keyA2->toPlainText());
    ui->keyB3->setPlainText(ui->keyA3->toPlainText());
    ui->keyB4->setPlainText(ui->keyA4->toPlainText());
    ui->keyB5->setPlainText(ui->keyA5->toPlainText());
}
void MainWindow::on_factoryKeyA_clicked()
{
    ui->keyA0->setPlainText("FF");
    ui->keyA1->setPlainText("FF");
    ui->keyA2->setPlainText("FF");
    ui->keyA3->setPlainText("FF");
    ui->keyA4->setPlainText("FF");
    ui->keyA5->setPlainText("FF");
}
void MainWindow::on_factoryKeyB_clicked()
{
    ui->keyB0->setPlainText("FF");
    ui->keyB1->setPlainText("FF");
    ui->keyB2->setPlainText("FF");
    ui->keyB3->setPlainText("FF");
    ui->keyB4->setPlainText("FF");
    ui->keyB5->setPlainText("FF");
}
// input manip keyA
void MainWindow::on_keyA5_textChanged()
{
      QString text = ui->keyA5->toPlainText().toUpper();
      text.replace(QRegExp("[^0-F]"), "") ;
      QStringList tokens;
          for(int i = 0; i < text.length(); i += 2)
          {
            tokens << text.mid(i, 2);
          }
      ui->keyA5->blockSignals(true);
      ui->keyA5->setText(tokens.join(" "));
      ui->keyA5->moveCursor(QTextCursor::EndOfBlock);
      ui->keyA5->blockSignals(false);

      if(ui->keyA5->toPlainText().length() > 2)
          {
          int diff = ui->keyA5->toPlainText().length() - 2; //m_maxTextEditLength - just an integer
          QString newStr = ui->keyA5->toPlainText();
          newStr.chop(diff);
          ui->keyA5->setText(newStr);
          QTextCursor cursor(ui->keyA5->textCursor());
          cursor.movePosition(QTextCursor::End, QTextCursor::MoveAnchor);
          ui->keyA5->setTextCursor(cursor);
          }
}
void MainWindow::on_keyA4_textChanged()
{
    QString text = ui->keyA4->toPlainText().toUpper();
    text.replace(QRegExp("[^0-F]"), "") ;
    QStringList tokens;
        for(int i = 0; i < text.length(); i += 2)
        {
          tokens << text.mid(i, 2);
        }
    ui->keyA4->blockSignals(true);
    ui->keyA4->setText(tokens.join(" "));
    ui->keyA4->moveCursor(QTextCursor::EndOfBlock);
    ui->keyA4->blockSignals(false);

    if(ui->keyA4->toPlainText().length() > 2)
        {
        int diff = ui->keyA4->toPlainText().length() - 2; //m_maxTextEditLength - just an integer
        QString newStr = ui->keyA4->toPlainText();
        newStr.chop(diff);
        ui->keyA4->setText(newStr);
        QTextCursor cursor(ui->keyA4->textCursor());
        cursor.movePosition(QTextCursor::End, QTextCursor::MoveAnchor);
        ui->keyA4->setTextCursor(cursor);
        }
}
void MainWindow::on_keyA3_textChanged()
{
    QString text = ui->keyA3->toPlainText().toUpper();
    text.replace(QRegExp("[^0-F]"), "") ;
    QStringList tokens;
        for(int i = 0; i < text.length(); i += 2)
        {
          tokens << text.mid(i, 2);
        }
    ui->keyA3->blockSignals(true);
    ui->keyA3->setText(tokens.join(" "));
    ui->keyA3->moveCursor(QTextCursor::EndOfBlock);
    ui->keyA3->blockSignals(false);

    if(ui->keyA3->toPlainText().length() > 2)
        {
        int diff = ui->keyA3->toPlainText().length() - 2; //m_maxTextEditLength - just an integer
        QString newStr = ui->keyA3->toPlainText();
        newStr.chop(diff);
        ui->keyA3->setText(newStr);
        QTextCursor cursor(ui->keyA3->textCursor());
        cursor.movePosition(QTextCursor::End, QTextCursor::MoveAnchor);
        ui->keyA3->setTextCursor(cursor);
        }
}
void MainWindow::on_keyA2_textChanged()
{
    QString text = ui->keyA2->toPlainText().toUpper();
    text.replace(QRegExp("[^0-F]"), "") ;
    QStringList tokens;
        for(int i = 0; i < text.length(); i += 2)
        {
          tokens << text.mid(i, 2);
        }
    ui->keyA2->blockSignals(true);
    ui->keyA2->setText(tokens.join(" "));
    ui->keyA2->moveCursor(QTextCursor::EndOfBlock);
    ui->keyA2->blockSignals(false);

    if(ui->keyA2->toPlainText().length() > 2)
        {
        int diff = ui->keyA2->toPlainText().length() - 2; //m_maxTextEditLength - just an integer
        QString newStr = ui->keyA2->toPlainText();
        newStr.chop(diff);
        ui->keyA2->setText(newStr);
        QTextCursor cursor(ui->keyA2->textCursor());
        cursor.movePosition(QTextCursor::End, QTextCursor::MoveAnchor);
        ui->keyA2->setTextCursor(cursor);
        }
}
void MainWindow::on_keyA1_textChanged()
{
    QString text = ui->keyA1->toPlainText().toUpper();
    text.replace(QRegExp("[^0-F]"), "") ;
    QStringList tokens;
        for(int i = 0; i < text.length(); i += 2)
        {
          tokens << text.mid(i, 2);
        }
    ui->keyA1->blockSignals(true);
    ui->keyA1->setText(tokens.join(" "));
    ui->keyA1->moveCursor(QTextCursor::EndOfBlock);
    ui->keyA1->blockSignals(false);

    if(ui->keyA1->toPlainText().length() > 2)
        {
        int diff = ui->keyA1->toPlainText().length() - 2; //m_maxTextEditLength - just an integer
        QString newStr = ui->keyA1->toPlainText();
        newStr.chop(diff);
        ui->keyA1->setText(newStr);
        QTextCursor cursor(ui->keyA1->textCursor());
        cursor.movePosition(QTextCursor::End, QTextCursor::MoveAnchor);
        ui->keyA1->setTextCursor(cursor);
        }
}
void MainWindow::on_keyA0_textChanged()
{
    QString text = ui->keyA0->toPlainText().toUpper();
    text.replace(QRegExp("[^0-F]"), "") ;
    QStringList tokens;
        for(int i = 0; i < text.length(); i += 2)
        {
          tokens << text.mid(i, 2);
        }
    ui->keyA0->blockSignals(true);
    ui->keyA0->setText(tokens.join(" "));
    ui->keyA0->moveCursor(QTextCursor::EndOfBlock);
    ui->keyA0->blockSignals(false);

    if(ui->keyA0->toPlainText().length() > 2)
        {
        int diff = ui->keyA0->toPlainText().length() - 2; //m_maxTextEditLength - just an integer
        QString newStr = ui->keyA0->toPlainText();
        newStr.chop(diff);
        ui->keyA0->setText(newStr);
        QTextCursor cursor(ui->keyA0->textCursor());
        cursor.movePosition(QTextCursor::End, QTextCursor::MoveAnchor);
        ui->keyA0->setTextCursor(cursor);
        }
}
// input manip keyB
void MainWindow::on_keyB5_textChanged()
{
    QString text = ui->keyB5->toPlainText().toUpper();
    text.replace(QRegExp("[^0-F]"), "") ;
    QStringList tokens;
        for(int i = 0; i < text.length(); i += 2)
        {
          tokens << text.mid(i, 2);
        }
    ui->keyB5->blockSignals(true);
    ui->keyB5->setText(tokens.join(" "));
    ui->keyB5->moveCursor(QTextCursor::EndOfBlock);
    ui->keyB5->blockSignals(false);

    if(ui->keyB5->toPlainText().length() > 2)
        {
        int diff = ui->keyB5->toPlainText().length() - 2; //m_maxTextEditLength - just an integer
        QString newStr = ui->keyB5->toPlainText();
        newStr.chop(diff);
        ui->keyB5->setText(newStr);
        QTextCursor cursor(ui->keyB5->textCursor());
        cursor.movePosition(QTextCursor::End, QTextCursor::MoveAnchor);
        ui->keyB5->setTextCursor(cursor);
        }
}
void MainWindow::on_keyB4_textChanged()
{
    QString text = ui->keyB4->toPlainText().toUpper();
    text.replace(QRegExp("[^0-F]"), "") ;
    QStringList tokens;
        for(int i = 0; i < text.length(); i += 2)
        {
          tokens << text.mid(i, 2);
        }
    ui->keyB4->blockSignals(true);
    ui->keyB4->setText(tokens.join(" "));
    ui->keyB4->moveCursor(QTextCursor::EndOfBlock);
    ui->keyB4->blockSignals(false);

    if(ui->keyB4->toPlainText().length() > 2)
        {
        int diff = ui->keyB4->toPlainText().length() - 2; //m_maxTextEditLength - just an integer
        QString newStr = ui->keyB4->toPlainText();
        newStr.chop(diff);
        ui->keyB4->setText(newStr);
        QTextCursor cursor(ui->keyB4->textCursor());
        cursor.movePosition(QTextCursor::End, QTextCursor::MoveAnchor);
        ui->keyB4->setTextCursor(cursor);
        }
}
void MainWindow::on_keyB3_textChanged()
{
    QString text = ui->keyB3->toPlainText().toUpper();
    text.replace(QRegExp("[^0-F]"), "") ;
    QStringList tokens;
        for(int i = 0; i < text.length(); i += 2)
        {
          tokens << text.mid(i, 2);
        }
    ui->keyB3->blockSignals(true);
    ui->keyB3->setText(tokens.join(" "));
    ui->keyB3->moveCursor(QTextCursor::EndOfBlock);
    ui->keyB3->blockSignals(false);

    if(ui->keyB3->toPlainText().length() > 2)
        {
        int diff = ui->keyB3->toPlainText().length() - 2; //m_maxTextEditLength - just an integer
        QString newStr = ui->keyB3->toPlainText();
        newStr.chop(diff);
        ui->keyB3->setText(newStr);
        QTextCursor cursor(ui->keyB3->textCursor());
        cursor.movePosition(QTextCursor::End, QTextCursor::MoveAnchor);
        ui->keyB3->setTextCursor(cursor);
        }
}
void MainWindow::on_keyB2_textChanged()
{
    QString text = ui->keyB2->toPlainText().toUpper();
    text.replace(QRegExp("[^0-F]"), "") ;
    QStringList tokens;
        for(int i = 0; i < text.length(); i += 2)
        {
          tokens << text.mid(i, 2);
        }
    ui->keyB2->blockSignals(true);
    ui->keyB2->setText(tokens.join(" "));
    ui->keyB2->moveCursor(QTextCursor::EndOfBlock);
    ui->keyB2->blockSignals(false);

    if(ui->keyB2->toPlainText().length() > 2)
        {
        int diff = ui->keyB2->toPlainText().length() - 2; //m_maxTextEditLength - just an integer
        QString newStr = ui->keyB2->toPlainText();
        newStr.chop(diff);
        ui->keyB2->setText(newStr);
        QTextCursor cursor(ui->keyB2->textCursor());
        cursor.movePosition(QTextCursor::End, QTextCursor::MoveAnchor);
        ui->keyB2->setTextCursor(cursor);
        }
}
void MainWindow::on_keyB1_textChanged()
{
    QString text = ui->keyB1->toPlainText().toUpper();
    text.replace(QRegExp("[^0-F]"), "") ;
    QStringList tokens;
        for(int i = 0; i < text.length(); i += 2)
        {
          tokens << text.mid(i, 2);
        }
    ui->keyB1->blockSignals(true);
    ui->keyB1->setText(tokens.join(" "));
    ui->keyB1->moveCursor(QTextCursor::EndOfBlock);
    ui->keyB1->blockSignals(false);

    if(ui->keyB1->toPlainText().length() > 2)
        {
        int diff = ui->keyB1->toPlainText().length() - 2; //m_maxTextEditLength - just an integer
        QString newStr = ui->keyB1->toPlainText();
        newStr.chop(diff);
        ui->keyB1->setText(newStr);
        QTextCursor cursor(ui->keyB1->textCursor());
        cursor.movePosition(QTextCursor::End, QTextCursor::MoveAnchor);
        ui->keyB1->setTextCursor(cursor);
        }
}
void MainWindow::on_keyB0_textChanged()
{
    QString text = ui->keyB0->toPlainText().toUpper();
    text.replace(QRegExp("[^0-F]"), "") ;
    QStringList tokens;
        for(int i = 0; i < text.length(); i += 2)
        {
          tokens << text.mid(i, 2);
        }
    ui->keyB0->blockSignals(true);
    ui->keyB0->setText(tokens.join(" "));
    ui->keyB0->moveCursor(QTextCursor::EndOfBlock);
    ui->keyB0->blockSignals(false);

    if(ui->keyB0->toPlainText().length() > 2)
        {
        int diff = ui->keyB1->toPlainText().length() - 2; //m_maxTextEditLength - just an integer
        QString newStr = ui->keyB0->toPlainText();
        newStr.chop(diff);
        ui->keyB0->setText(newStr);
        QTextCursor cursor(ui->keyB0->textCursor());
        cursor.movePosition(QTextCursor::End, QTextCursor::MoveAnchor);
        ui->keyB0->setTextCursor(cursor);
        }
}
//input manip RW
void MainWindow::on_R15_textChanged()
{
    QString text = ui->R15->toPlainText().toUpper();
    text.replace(QRegExp("[^0-F]"), "") ;
    QStringList tokens;
        for(int i = 0; i < text.length(); i += 2)
        {
          tokens << text.mid(i, 2);
        }
    ui->R15->blockSignals(true);
    ui->R15->setText(tokens.join(" "));
    ui->R15->moveCursor(QTextCursor::EndOfBlock);
    ui->R15->blockSignals(false);

    if(ui->R15->toPlainText().length() > 2)
        {
        int diff = ui->R15->toPlainText().length() - 2; //m_maxTextEditLength - just an integer
        QString newStr = ui->R15->toPlainText();
        newStr.chop(diff);
        ui->R15->setText(newStr);
        QTextCursor cursor(ui->R15->textCursor());
        cursor.movePosition(QTextCursor::End, QTextCursor::MoveAnchor);
        ui->R15->setTextCursor(cursor);
        }
}
void MainWindow::on_R14_textChanged()
{
    QString text = ui->R14->toPlainText().toUpper();
    text.replace(QRegExp("[^0-F]"), "") ;
    QStringList tokens;
        for(int i = 0; i < text.length(); i += 2)
        {
          tokens << text.mid(i, 2);
        }
    ui->R14->blockSignals(true);
    ui->R14->setText(tokens.join(" "));
    ui->R14->moveCursor(QTextCursor::EndOfBlock);
    ui->R14->blockSignals(false);

    if(ui->R14->toPlainText().length() > 2)
        {
        int diff = ui->R14->toPlainText().length() - 2; //m_maxTextEditLength - just an integer
        QString newStr = ui->R14->toPlainText();
        newStr.chop(diff);
        ui->R14->setText(newStr);
        QTextCursor cursor(ui->R14->textCursor());
        cursor.movePosition(QTextCursor::End, QTextCursor::MoveAnchor);
        ui->R14->setTextCursor(cursor);
        }
}
void MainWindow::on_R13_textChanged()
{
    QString text = ui->R13->toPlainText().toUpper();
    text.replace(QRegExp("[^0-F]"), "") ;
    QStringList tokens;
        for(int i = 0; i < text.length(); i += 2)
        {
          tokens << text.mid(i, 2);
        }
    ui->R13->blockSignals(true);
    ui->R13->setText(tokens.join(" "));
    ui->R13->moveCursor(QTextCursor::EndOfBlock);
    ui->R13->blockSignals(false);

    if(ui->R13->toPlainText().length() > 2)
        {
        int diff = ui->R13->toPlainText().length() - 2; //m_maxTextEditLength - just an integer
        QString newStr = ui->R13->toPlainText();
        newStr.chop(diff);
        ui->R13->setText(newStr);
        QTextCursor cursor(ui->R13->textCursor());
        cursor.movePosition(QTextCursor::End, QTextCursor::MoveAnchor);
        ui->R13->setTextCursor(cursor);
        }
}
void MainWindow::on_R12_textChanged()
{
    QString text = ui->R12->toPlainText().toUpper();
    text.replace(QRegExp("[^0-F]"), "") ;
    QStringList tokens;
        for(int i = 0; i < text.length(); i += 2)
        {
          tokens << text.mid(i, 2);
        }
    ui->R12->blockSignals(true);
    ui->R12->setText(tokens.join(" "));
    ui->R12->moveCursor(QTextCursor::EndOfBlock);
    ui->R12->blockSignals(false);

    if(ui->R12->toPlainText().length() > 2)
        {
        int diff = ui->R12->toPlainText().length() - 2; //m_maxTextEditLength - just an integer
        QString newStr = ui->R12->toPlainText();
        newStr.chop(diff);
        ui->R12->setText(newStr);
        QTextCursor cursor(ui->R12->textCursor());
        cursor.movePosition(QTextCursor::End, QTextCursor::MoveAnchor);
        ui->R12->setTextCursor(cursor);
        }
}
void MainWindow::on_R11_textChanged()
{
    QString text = ui->R11->toPlainText().toUpper();
    text.replace(QRegExp("[^0-F]"), "") ;
    QStringList tokens;
        for(int i = 0; i < text.length(); i += 2)
        {
          tokens << text.mid(i, 2);
        }
    ui->R11->blockSignals(true);
    ui->R11->setText(tokens.join(" "));
    ui->R11->moveCursor(QTextCursor::EndOfBlock);
    ui->R11->blockSignals(false);

    if(ui->R11->toPlainText().length() > 2)
        {
        int diff = ui->R11->toPlainText().length() - 2; //m_maxTextEditLength - just an integer
        QString newStr = ui->R11->toPlainText();
        newStr.chop(diff);
        ui->R11->setText(newStr);
        QTextCursor cursor(ui->R11->textCursor());
        cursor.movePosition(QTextCursor::End, QTextCursor::MoveAnchor);
        ui->R11->setTextCursor(cursor);
        }
}
void MainWindow::on_R10_textChanged()
{
    QString text = ui->R10->toPlainText().toUpper();
    text.replace(QRegExp("[^0-F]"), "") ;
    QStringList tokens;
        for(int i = 0; i < text.length(); i += 2)
        {
          tokens << text.mid(i, 2);
        }
    ui->R10->blockSignals(true);
    ui->R10->setText(tokens.join(" "));
    ui->R10->moveCursor(QTextCursor::EndOfBlock);
    ui->R10->blockSignals(false);

    if(ui->R10->toPlainText().length() > 2)
        {
        int diff = ui->R10->toPlainText().length() - 2; //m_maxTextEditLength - just an integer
        QString newStr = ui->R10->toPlainText();
        newStr.chop(diff);
        ui->R10->setText(newStr);
        QTextCursor cursor(ui->R10->textCursor());
        cursor.movePosition(QTextCursor::End, QTextCursor::MoveAnchor);
        ui->R10->setTextCursor(cursor);
        }
}
void MainWindow::on_R9_textChanged()
{
    QString text = ui->R9->toPlainText().toUpper();
    text.replace(QRegExp("[^0-F]"), "") ;
    QStringList tokens;
        for(int i = 0; i < text.length(); i += 2)
        {
          tokens << text.mid(i, 2);
        }
    ui->R9->blockSignals(true);
    ui->R9->setText(tokens.join(" "));
    ui->R9->moveCursor(QTextCursor::EndOfBlock);
    ui->R9->blockSignals(false);

    if(ui->R9->toPlainText().length() > 2)
        {
        int diff = ui->R9->toPlainText().length() - 2; //m_maxTextEditLength - just an integer
        QString newStr = ui->R9->toPlainText();
        newStr.chop(diff);
        ui->R9->setText(newStr);
        QTextCursor cursor(ui->R9->textCursor());
        cursor.movePosition(QTextCursor::End, QTextCursor::MoveAnchor);
        ui->R9->setTextCursor(cursor);
        }
}
void MainWindow::on_R8_textChanged()
{
    QString text = ui->R8->toPlainText().toUpper();
    text.replace(QRegExp("[^0-F]"), "") ;
    QStringList tokens;
        for(int i = 0; i < text.length(); i += 2)
        {
          tokens << text.mid(i, 2);
        }
    ui->R8->blockSignals(true);
    ui->R8->setText(tokens.join(" "));
    ui->R8->moveCursor(QTextCursor::EndOfBlock);
    ui->R8->blockSignals(false);

    if(ui->R8->toPlainText().length() > 2)
        {
        int diff = ui->R8->toPlainText().length() - 2; //m_maxTextEditLength - just an integer
        QString newStr = ui->R8->toPlainText();
        newStr.chop(diff);
        ui->R8->setText(newStr);
        QTextCursor cursor(ui->R8->textCursor());
        cursor.movePosition(QTextCursor::End, QTextCursor::MoveAnchor);
        ui->R8->setTextCursor(cursor);
        }
}
void MainWindow::on_R7_textChanged()
{
    QString text = ui->R7->toPlainText().toUpper();
    text.replace(QRegExp("[^0-F]"), "") ;
    QStringList tokens;
        for(int i = 0; i < text.length(); i += 2)
        {
          tokens << text.mid(i, 2);
        }
    ui->R7->blockSignals(true);
    ui->R7->setText(tokens.join(" "));
    ui->R7->moveCursor(QTextCursor::EndOfBlock);
    ui->R7->blockSignals(false);

    if(ui->R7->toPlainText().length() > 2)
        {
        int diff = ui->R7->toPlainText().length() - 2; //m_maxTextEditLength - just an integer
        QString newStr = ui->R7->toPlainText();
        newStr.chop(diff);
        ui->R7->setText(newStr);
        QTextCursor cursor(ui->R7->textCursor());
        cursor.movePosition(QTextCursor::End, QTextCursor::MoveAnchor);
        ui->R7->setTextCursor(cursor);
        }
}
void MainWindow::on_R6_textChanged()
{
    QString text = ui->R6->toPlainText().toUpper();
    text.replace(QRegExp("[^0-F]"), "") ;
    QStringList tokens;
        for(int i = 0; i < text.length(); i += 2)
        {
          tokens << text.mid(i, 2);
        }
    ui->R6->blockSignals(true);
    ui->R6->setText(tokens.join(" "));
    ui->R6->moveCursor(QTextCursor::EndOfBlock);
    ui->R6->blockSignals(false);

    if(ui->R6->toPlainText().length() > 2)
        {
        int diff = ui->R6->toPlainText().length() - 2; //m_maxTextEditLength - just an integer
        QString newStr = ui->R6->toPlainText();
        newStr.chop(diff);
        ui->R6->setText(newStr);
        QTextCursor cursor(ui->R6->textCursor());
        cursor.movePosition(QTextCursor::End, QTextCursor::MoveAnchor);
        ui->R6->setTextCursor(cursor);
        }
}
void MainWindow::on_R5_textChanged()
{
    QString text = ui->R5->toPlainText().toUpper();
    text.replace(QRegExp("[^0-F]"), "") ;
    QStringList tokens;
        for(int i = 0; i < text.length(); i += 2)
        {
          tokens << text.mid(i, 2);
        }
    ui->R5->blockSignals(true);
    ui->R5->setText(tokens.join(" "));
    ui->R5->moveCursor(QTextCursor::EndOfBlock);
    ui->R5->blockSignals(false);

    if(ui->R5->toPlainText().length() > 2)
        {
        int diff = ui->R5->toPlainText().length() - 2; //m_maxTextEditLength - just an integer
        QString newStr = ui->R5->toPlainText();
        newStr.chop(diff);
        ui->R5->setText(newStr);
        QTextCursor cursor(ui->R5->textCursor());
        cursor.movePosition(QTextCursor::End, QTextCursor::MoveAnchor);
        ui->R5->setTextCursor(cursor);
        }
}
void MainWindow::on_R4_textChanged()
{
    QString text = ui->R4->toPlainText().toUpper();
    text.replace(QRegExp("[^0-F]"), "") ;
    QStringList tokens;
        for(int i = 0; i < text.length(); i += 2)
        {
          tokens << text.mid(i, 2);
        }
    ui->R4->blockSignals(true);
    ui->R4->setText(tokens.join(" "));
    ui->R4->moveCursor(QTextCursor::EndOfBlock);
    ui->R4->blockSignals(false);

    if(ui->R4->toPlainText().length() > 2)
        {
        int diff = ui->R4->toPlainText().length() - 2; //m_maxTextEditLength - just an integer
        QString newStr = ui->R4->toPlainText();
        newStr.chop(diff);
        ui->R4->setText(newStr);
        QTextCursor cursor(ui->R4->textCursor());
        cursor.movePosition(QTextCursor::End, QTextCursor::MoveAnchor);
        ui->R4->setTextCursor(cursor);
        }
}
void MainWindow::on_R3_textChanged()
{
    QString text = ui->R3->toPlainText().toUpper();
    text.replace(QRegExp("[^0-F]"), "") ;
    QStringList tokens;
        for(int i = 0; i < text.length(); i += 2)
        {
          tokens << text.mid(i, 2);
        }
    ui->R3->blockSignals(true);
    ui->R3->setText(tokens.join(" "));
    ui->R3->moveCursor(QTextCursor::EndOfBlock);
    ui->R3->blockSignals(false);

    if(ui->R3->toPlainText().length() > 2)
        {
        int diff = ui->R3->toPlainText().length() - 2; //m_maxTextEditLength - just an integer
        QString newStr = ui->R3->toPlainText();
        newStr.chop(diff);
        ui->R3->setText(newStr);
        QTextCursor cursor(ui->R3->textCursor());
        cursor.movePosition(QTextCursor::End, QTextCursor::MoveAnchor);
        ui->R3->setTextCursor(cursor);
        }
}
void MainWindow::on_R2_textChanged()
{
    QString text = ui->R2->toPlainText().toUpper();
    text.replace(QRegExp("[^0-F]"), "") ;
    QStringList tokens;
        for(int i = 0; i < text.length(); i += 2)
        {
          tokens << text.mid(i, 2);
        }
    ui->R2->blockSignals(true);
    ui->R2->setText(tokens.join(" "));
    ui->R2->moveCursor(QTextCursor::EndOfBlock);
    ui->R2->blockSignals(false);

    if(ui->R2->toPlainText().length() > 2)
        {
        int diff = ui->R2->toPlainText().length() - 2; //m_maxTextEditLength - just an integer
        QString newStr = ui->R2->toPlainText();
        newStr.chop(diff);
        ui->R2->setText(newStr);
        QTextCursor cursor(ui->R2->textCursor());
        cursor.movePosition(QTextCursor::End, QTextCursor::MoveAnchor);
        ui->R2->setTextCursor(cursor);
        }
}
void MainWindow::on_R1_textChanged()
{
    QString text = ui->R1->toPlainText().toUpper();
    text.replace(QRegExp("[^0-F]"), "") ;
    QStringList tokens;
        for(int i = 0; i < text.length(); i += 2)
        {
          tokens << text.mid(i, 2);
        }
    ui->R1->blockSignals(true);
    ui->R1->setText(tokens.join(" "));
    ui->R1->moveCursor(QTextCursor::EndOfBlock);
    ui->R1->blockSignals(false);

    if(ui->R1->toPlainText().length() > 2)
        {
        int diff = ui->R1->toPlainText().length() - 2; //m_maxTextEditLength - just an integer
        QString newStr = ui->R1->toPlainText();
        newStr.chop(diff);
        ui->R1->setText(newStr);
        QTextCursor cursor(ui->R1->textCursor());
        cursor.movePosition(QTextCursor::End, QTextCursor::MoveAnchor);
        ui->R1->setTextCursor(cursor);
        }
}
void MainWindow::on_R0_textChanged()
{
    QString text = ui->R0->toPlainText().toUpper();
    text.replace(QRegExp("[^0-F]"), "") ;
    QStringList tokens;
        for(int i = 0; i < text.length(); i += 2)
        {
          tokens << text.mid(i, 2);
        }
    ui->R0->blockSignals(true);
    ui->R0->setText(tokens.join(" "));
    ui->R0->moveCursor(QTextCursor::EndOfBlock);
    ui->R0->blockSignals(false);

    if(ui->R0->toPlainText().length() > 2)
        {
        int diff = ui->R0->toPlainText().length() - 2; //m_maxTextEditLength - just an integer
        QString newStr = ui->R0->toPlainText();
        newStr.chop(diff);
        ui->R0->setText(newStr);
        QTextCursor cursor(ui->R0->textCursor());
        cursor.movePosition(QTextCursor::End, QTextCursor::MoveAnchor);
        ui->R0->setTextCursor(cursor);
        }
}

void MainWindow::on_utilityKC5_textChanged()
{
    QString text = ui->utilityKC5->toPlainText().toUpper();
    text.replace(QRegExp("[^0-F]"), "") ;
    QStringList tokens;
        for(int i = 0; i < text.length(); i += 2)
        {
          tokens << text.mid(i, 2);
        }
    ui->utilityKC5->blockSignals(true);
    ui->utilityKC5->setText(tokens.join(" "));
    ui->utilityKC5->moveCursor(QTextCursor::EndOfBlock);
    ui->utilityKC5->blockSignals(false);

    if(ui->utilityKC5->toPlainText().length() > 2)
        {
        int diff = ui->utilityKC5->toPlainText().length() - 2; //m_maxTextEditLength - just an integer
        QString newStr = ui->utilityKC5->toPlainText();
        newStr.chop(diff);
        ui->utilityKC5->setText(newStr);
        QTextCursor cursor(ui->utilityKC5->textCursor());
        cursor.movePosition(QTextCursor::End, QTextCursor::MoveAnchor);
        ui->utilityKC5->setTextCursor(cursor);
        }
}
void MainWindow::on_utilityKC4_textChanged()
{
    QString text = ui->utilityKC4->toPlainText().toUpper();
    text.replace(QRegExp("[^0-F]"), "") ;
    QStringList tokens;
        for(int i = 0; i < text.length(); i += 2)
        {
          tokens << text.mid(i, 2);
        }
    ui->utilityKC4->blockSignals(true);
    ui->utilityKC4->setText(tokens.join(" "));
    ui->utilityKC4->moveCursor(QTextCursor::EndOfBlock);
    ui->utilityKC4->blockSignals(false);

    if(ui->utilityKC4->toPlainText().length() > 2)
        {
        int diff = ui->utilityKC4->toPlainText().length() - 2; //m_maxTextEditLength - just an integer
        QString newStr = ui->utilityKC4->toPlainText();
        newStr.chop(diff);
        ui->utilityKC4->setText(newStr);
        QTextCursor cursor(ui->utilityKC4->textCursor());
        cursor.movePosition(QTextCursor::End, QTextCursor::MoveAnchor);
        ui->utilityKC4->setTextCursor(cursor);
        }
}
void MainWindow::on_utilityKC3_textChanged()
{
    QString text = ui->utilityKC3->toPlainText().toUpper();
    text.replace(QRegExp("[^0-F]"), "") ;
    QStringList tokens;
        for(int i = 0; i < text.length(); i += 2)
        {
          tokens << text.mid(i, 2);
        }
    ui->utilityKC3->blockSignals(true);
    ui->utilityKC3->setText(tokens.join(" "));
    ui->utilityKC3->moveCursor(QTextCursor::EndOfBlock);
    ui->utilityKC3->blockSignals(false);

    if(ui->utilityKC3->toPlainText().length() > 2)
        {
        int diff = ui->utilityKC3->toPlainText().length() - 2; //m_maxTextEditLength - just an integer
        QString newStr = ui->utilityKC3->toPlainText();
        newStr.chop(diff);
        ui->utilityKC3->setText(newStr);
        QTextCursor cursor(ui->utilityKC3->textCursor());
        cursor.movePosition(QTextCursor::End, QTextCursor::MoveAnchor);
        ui->utilityKC3->setTextCursor(cursor);
        }
}
void MainWindow::on_utilityKC2_textChanged()
{
    QString text = ui->utilityKC2->toPlainText().toUpper();
    text.replace(QRegExp("[^0-F]"), "") ;
    QStringList tokens;
        for(int i = 0; i < text.length(); i += 2)
        {
          tokens << text.mid(i, 2);
        }
    ui->utilityKC2->blockSignals(true);
    ui->utilityKC2->setText(tokens.join(" "));
    ui->utilityKC2->moveCursor(QTextCursor::EndOfBlock);
    ui->utilityKC2->blockSignals(false);

    if(ui->utilityKC2->toPlainText().length() > 2)
        {
        int diff = ui->utilityKC2->toPlainText().length() - 2; //m_maxTextEditLength - just an integer
        QString newStr = ui->utilityKC2->toPlainText();
        newStr.chop(diff);
        ui->utilityKC2->setText(newStr);
        QTextCursor cursor(ui->utilityKC2->textCursor());
        cursor.movePosition(QTextCursor::End, QTextCursor::MoveAnchor);
        ui->utilityKC2->setTextCursor(cursor);
        }
}
void MainWindow::on_utilityKC1_textChanged()
{
    QString text = ui->utilityKC1->toPlainText().toUpper();
    text.replace(QRegExp("[^0-F]"), "") ;
    QStringList tokens;
        for(int i = 0; i < text.length(); i += 2)
        {
          tokens << text.mid(i, 2);
        }
    ui->utilityKC1->blockSignals(true);
    ui->utilityKC1->setText(tokens.join(" "));
    ui->utilityKC1->moveCursor(QTextCursor::EndOfBlock);
    ui->utilityKC1->blockSignals(false);

    if(ui->utilityKC1->toPlainText().length() > 2)
        {
        int diff = ui->utilityKC1->toPlainText().length() - 2; //m_maxTextEditLength - just an integer
        QString newStr = ui->utilityKC1->toPlainText();
        newStr.chop(diff);
        ui->utilityKC1->setText(newStr);
        QTextCursor cursor(ui->utilityKC1->textCursor());
        cursor.movePosition(QTextCursor::End, QTextCursor::MoveAnchor);
        ui->utilityKC1->setTextCursor(cursor);
        }
}
void MainWindow::on_utilityKC0_textChanged()
{
    QString text = ui->utilityKC0->toPlainText().toUpper();
    text.replace(QRegExp("[^0-F]"), "") ;
    QStringList tokens;
        for(int i = 0; i < text.length(); i += 2)
        {
          tokens << text.mid(i, 2);
        }
    ui->utilityKC0->blockSignals(true);
    ui->utilityKC0->setText(tokens.join(" "));
    ui->utilityKC0->moveCursor(QTextCursor::EndOfBlock);
    ui->utilityKC0->blockSignals(false);

    if(ui->utilityKC0->toPlainText().length() > 2)
        {
        int diff = ui->utilityKC0->toPlainText().length() - 2; //m_maxTextEditLength - just an integer
        QString newStr = ui->utilityKC0->toPlainText();
        newStr.chop(diff);
        ui->utilityKC0->setText(newStr);
        QTextCursor cursor(ui->utilityKC0->textCursor());
        cursor.movePosition(QTextCursor::End, QTextCursor::MoveAnchor);
        ui->utilityKC0->setTextCursor(cursor);
        }
}

void MainWindow::on_valueBlockInit_textChanged()
{
    QString text = ui->R0->toPlainText().toUpper();
    text.replace(QRegExp("[^0-9]"), "") ;
    QStringList tokens;
        for(int i = 0; i < text.length(); i += 2)
        {
          tokens << text.mid(i, 2);
        }
    ui->R0->blockSignals(true);
    ui->R0->setText(tokens.join(" "));
    ui->R0->moveCursor(QTextCursor::EndOfBlock);
    ui->R0->blockSignals(false);

    if(ui->R0->toPlainText().length() > 2)
        {
        int diff = ui->R0->toPlainText().length() - 2; //m_maxTextEditLength - just an integer
        QString newStr = ui->R0->toPlainText();
        newStr.chop(diff);
        ui->R0->setText(newStr);
        QTextCursor cursor(ui->R0->textCursor());
        cursor.movePosition(QTextCursor::End, QTextCursor::MoveAnchor);
        ui->R0->setTextCursor(cursor);
        }
}

void MainWindow::setReadOnlyReadBlocks()
{

    ui->R15->setReadOnly(choice::set);
    ui->R14->setReadOnly(choice::set);
    ui->R13->setReadOnly(choice::set);
    ui->R12->setReadOnly(choice::set);
    ui->R11->setReadOnly(choice::set);
    ui->R10->setReadOnly(choice::set);
    ui->R9 ->setReadOnly(choice::set);
    ui->R8 ->setReadOnly(choice::set);
    ui->R7 ->setReadOnly(choice::set);
    ui->R6 ->setReadOnly(choice::set);
    ui->R5 ->setReadOnly(choice::set);
    ui->R4 ->setReadOnly(choice::set);
    ui->R3 ->setReadOnly(choice::set);
    ui->R2 ->setReadOnly(choice::set);
    ui->R1 ->setReadOnly(choice::set);
    ui->R0 ->setReadOnly(choice::set);

}
void MainWindow::applyDataToReadBLocks(const QStringList &dataList)
{
    TextWindow* txtwnd = TextWindow::getInstance();
    ui->R15->setText(dataList.at(0));
    ui->R14->setText(dataList.at(1));
    ui->R13->setText(dataList.at(2));
    ui->R12->setText(dataList.at(3));
    ui->R11->setText(dataList.at(4));
    ui->R10->setText(dataList.at(5));
    ui->R9 ->setText(dataList.at(6));
    ui->R8 ->setText(dataList.at(7));
    ui->R7 ->setText(dataList.at(8));
    ui->R6 ->setText(dataList.at(9));
    ui->R5 ->setText(dataList.at(10));
    ui->R4 ->setText(dataList.at(11));
    ui->R3 ->setText(dataList.at(12));
    ui->R2 ->setText(dataList.at(13));
    ui->R1 ->setText(dataList.at(14));
    ui->R0 ->setText(dataList.at(15));
    QString dataStr = dataList.join(' ');
    QString textValue = QString::fromLocal8Bit(QByteArray::fromHex(dataStr.toLatin1()));
    txtwnd->setTextAsAscii(textValue);

}
void MainWindow::applyDataFromTextWindowToKeyA()
{
    TextWindow* txtwnd = TextWindow::getInstance();
    QStringList dataList = txtwnd->getKeyA();
    ui->keyA5->setText(dataList.at(0));
    ui->keyA4->setText(dataList.at(1));
    ui->keyA3->setText(dataList.at(2));
    ui->keyA2->setText(dataList.at(3));
    ui->keyA1->setText(dataList.at(4));
    ui->keyA0->setText(dataList.at(5));
}
void MainWindow::applyDataFromTextWindowToKeyB()
{
    TextWindow* txtwnd = TextWindow::getInstance();
    QStringList dataList = txtwnd->getKeyB();
    ui->keyB5->setText(dataList.at(0));
    ui->keyB4->setText(dataList.at(1));
    ui->keyB3->setText(dataList.at(2));
    ui->keyB2->setText(dataList.at(3));
    ui->keyB1->setText(dataList.at(4));
    ui->keyB0->setText(dataList.at(5));
}
void MainWindow::applyDataFromTextWindow()
{
    TextWindow* txtwnd = TextWindow::getInstance();
    QStringList dataList = txtwnd->getDataList();
    ui->R15->setText(dataList.at(0));
    ui->R14->setText(dataList.at(1));
    ui->R13->setText(dataList.at(2));
    ui->R12->setText(dataList.at(3));
    ui->R11->setText(dataList.at(4));
    ui->R10->setText(dataList.at(5));
    ui->R9 ->setText(dataList.at(6));
    ui->R8 ->setText(dataList.at(7));
    ui->R7 ->setText(dataList.at(8));
    ui->R6 ->setText(dataList.at(9));
    ui->R5 ->setText(dataList.at(10));
    ui->R4 ->setText(dataList.at(11));
    ui->R3 ->setText(dataList.at(12));
    ui->R2 ->setText(dataList.at(13));
    ui->R1 ->setText(dataList.at(14));
    ui->R0 ->setText(dataList.at(15));

}
void MainWindow::applyDataFromTextWindowToUtilityKey()
{
    TextWindow* txtwnd = TextWindow::getInstance();
    QStringList dataList = txtwnd->getUtilityKey();
    ui->utilityKC5->setText(dataList.at(0));
    ui->utilityKC4->setText(dataList.at(1));
    ui->utilityKC3->setText(dataList.at(2));
    ui->utilityKC2->setText(dataList.at(3));
    ui->utilityKC1->setText(dataList.at(4));
    ui->utilityKC0->setText(dataList.at(5));
}

void MainWindow::on_blockSelect_valueChanged(int arg1)
{
     ui->sectorSelect->setValue(arg1/4);
     ui->utilitySector->setText(QString::number(arg1/4));
     ui->utilityBlock->setText(QString::number(arg1));
}

void MainWindow::on_sectorBegin_valueChanged(int arg1)
{

    if((ui->sectorBegin->value())>=(ui->sectorEnd->value()))
        ui->sectorEnd->setValue(arg1);
}
void MainWindow::on_sectorEnd_valueChanged(int arg1)
{

    if((ui->sectorBegin->value())>=(ui->sectorEnd->value()))
        ui->sectorBegin->setValue(arg1);
}

void MainWindow::on_RWClear_clicked()
{
    TextWindow* txtwnd = TextWindow::getInstance();
    ui->R15->clear(); ui->R15->setReadOnly(choice::clear);
    ui->R14->clear(); ui->R14->setReadOnly(choice::clear);
    ui->R13->clear(); ui->R13->setReadOnly(choice::clear);
    ui->R12->clear(); ui->R12->setReadOnly(choice::clear);
    ui->R11->clear(); ui->R11->setReadOnly(choice::clear);
    ui->R10->clear(); ui->R10->setReadOnly(choice::clear);
    ui->R9 ->clear(); ui->R9 ->setReadOnly(choice::clear);
    ui->R8 ->clear(); ui->R8 ->setReadOnly(choice::clear);
    ui->R7 ->clear(); ui->R7 ->setReadOnly(choice::clear);
    ui->R6 ->clear(); ui->R6 ->setReadOnly(choice::clear);
    ui->R5 ->clear(); ui->R5 ->setReadOnly(choice::clear);
    ui->R4 ->clear(); ui->R4 ->setReadOnly(choice::clear);
    ui->R3 ->clear(); ui->R3 ->setReadOnly(choice::clear);
    ui->R2 ->clear(); ui->R2 ->setReadOnly(choice::clear);
    ui->R1 ->clear(); ui->R1 ->setReadOnly(choice::clear);
    ui->R0 ->clear(); ui->R0 ->setReadOnly(choice::clear);
    txtwnd->setTextWindowTextReadOnly(false);
    txtwnd->clearTextWindowText();
}
void MainWindow::on_decVB_clicked()
{
    APDUCommand apdu{};
    SCardConnection* connect = SCardConnection::getInstance();
    QString blockString = (ui->blockSelect->text());

    connect->setBlockNum(blockString);
    apdu.setReadValueBlockCommand(connect->getBlockNum());

    QString valueStr;
    LONG lRet = connect->readValueBlock(apdu.getReadCommand());
    BYTE *response = connect->getResponse();
    if(((lRet != SCARD_S_SUCCESS) || (*(response) != SUCCESS_RESPONSE[0]) || (*(response+1) != SUCCESS_RESPONSE[1])))
        {
            ui->statusVB->setText("Failed to decrement!");
            ui->statusVB->setStyleSheet("QLabel#statusVB {font-weight: bold; color : red; }");
            return;
        }
    else
       {
        int receivedData = (connect->getValue()-1);
        qDebug() << receivedData;
        valueStr = QString::number(receivedData);
        ui->textVB->setText(valueStr);

        }
    QString valueHexStr;
    valueHexStr.setNum(valueStr.toInt(),16);
    if(valueHexStr.length() %2)   valueHexStr.insert(0,QLatin1String("0"));
    valueHexStr = valueHexStr.toUpper();
    QByteArray blockHexByteArray = QByteArray::fromHex(valueHexStr.toLatin1());
    BYTE valueNum[4]{0x00, 0x00, 0x00, 0x00};
    std::reverse(blockHexByteArray.begin(),blockHexByteArray.end());
    qDebug() << blockHexByteArray;
    qDebug() << blockHexByteArray.length();
//    qDebug() <<
    for( int i = 0; i<blockHexByteArray.length();i++)
    {
        valueNum[i] |= (BYTE)blockHexByteArray[i];

    }


    connect->setBlockNum(blockString);

    apdu.setValueBlockCommand(connect->getBlockNum(),valueNum);
    lRet = connect->writeDataBlock(apdu.getWriteCommand());
    response = connect->getResponse();
    if(((lRet != SCARD_S_SUCCESS) || (*(response) != SUCCESS_RESPONSE[0]) || (*(response+1) != SUCCESS_RESPONSE[1])))
    {
      ui->statusVB->setText("Failed to decrement and write value block!");
      ui->statusVB->setStyleSheet("QLabel#statusVB {font-weight: bold; color : red; }");
      ui->commandTextWindow->append("FormatAsValueBlockWAndIncrement()");
      return;
    }
    ui->statusVB->setText("Succesfully decremented and written as value block.");
    ui->statusVB->setStyleSheet("QLabel#statusVB {font-weight: bold; color : green; }");
    ui->commandTextWindow->append("FormatAsValueBlockWAndIncrement()");

}
void MainWindow::on_incVB_clicked()
{
    APDUCommand apdu{};
    SCardConnection* connect = SCardConnection::getInstance();
    QString blockString = (ui->blockSelect->text());

    connect->setBlockNum(blockString);
    apdu.setReadValueBlockCommand(connect->getBlockNum());

    QString valueStr;
    LONG lRet = connect->readValueBlock(apdu.getReadCommand());
    BYTE *response = connect->getResponse();
    if(((lRet != SCARD_S_SUCCESS) || (*(response) != SUCCESS_RESPONSE[0]) || (*(response+1) != SUCCESS_RESPONSE[1])))
        {
            ui->statusVB->setText("Failed to increment!");
            ui->statusVB->setStyleSheet("QLabel#statusVB {font-weight: bold; color : red; }");
            return;
        }
    else
       {
        int receivedData = (connect->getValue()+1);
        qDebug() << receivedData;
        valueStr = QString::number(receivedData);
        ui->textVB->setText(valueStr);

        }
    QString valueHexStr;
    valueHexStr.setNum(valueStr.toInt(),16);
    if(valueHexStr.length() %2)   valueHexStr.insert(0,QLatin1String("0"));
    valueHexStr = valueHexStr.toUpper();
    QByteArray blockHexByteArray = QByteArray::fromHex(valueHexStr.toLatin1());
    BYTE valueNum[4]{0x00, 0x00, 0x00, 0x00};
    std::reverse(blockHexByteArray.begin(),blockHexByteArray.end());
    qDebug() << blockHexByteArray;
    qDebug() << blockHexByteArray.length();
//    qDebug() <<
    for( int i = 0; i<blockHexByteArray.length();i++)
    {
        valueNum[i] |= (BYTE)blockHexByteArray[i];

    }


    connect->setBlockNum(blockString);

    apdu.setValueBlockCommand(connect->getBlockNum(),valueNum);
    lRet = connect->writeDataBlock(apdu.getWriteCommand());
    response = connect->getResponse();
    if(((lRet != SCARD_S_SUCCESS) || (*(response) != SUCCESS_RESPONSE[0]) || (*(response+1) != SUCCESS_RESPONSE[1])))
    {
      ui->statusVB->setText("Failed to increment and write value block!");
      ui->statusVB->setStyleSheet("QLabel#statusVB {font-weight: bold; color : red; }");
      ui->commandTextWindow->append("FormatAsValueBlockWAndIncrement()");
      return;
    }
    ui->statusVB->setText("Succesfully incremented and written as value block.");
    ui->statusVB->setStyleSheet("QLabel#statusVB {font-weight: bold; color : green; }");
    ui->commandTextWindow->append("FormatAsValueBlockWAndIncrement()");

}
void MainWindow::on_utilityKCText_clicked()
{
    TextWindow* txtwnd = TextWindow::getInstance();
    txtwnd->show();
    txtwnd->setTextAreaSelect(3);
    txtwnd->setInputMaxSize(KEY_SIZE);
}
void MainWindow::on_utilityKCFactory_clicked()
{
    ui->utilityKC0->setText("FF");
    ui->utilityKC1->setText("FF");
    ui->utilityKC2->setText("FF");
    ui->utilityKC3->setText("FF");
    ui->utilityKC4->setText("FF");
    ui->utilityKC5->setText("FF");
}
void MainWindow::on_utilityKCTextClear_clicked()
{
    ui->utilityKC0->clear();
    ui->utilityKC1->clear();
    ui->utilityKC2->clear();
    ui->utilityKC3->clear();
    ui->utilityKC4->clear();
    ui->utilityKC5->clear();
}

void MainWindow::constructKeys(const BYTE select)
{
    BYTE keyA[KEY_SIZE];
    BYTE keyB[KEY_SIZE];
    if(select == KEYA_SELECT)
    {
        MainWindow::setUtilityKey();
        QString _keyA = MainWindow::getUtilityKey();
        QByteArray _keyBytes = QByteArray::fromHex(_keyA.toLatin1());
            for( int i=0 ; i<static_cast<int>(KEY_SIZE) ; i++ )
            {
                keyA[i] = _keyBytes[i];
                m_sectorTrailer[i] = keyA[i];
            }
    }
    if(select == KEYB_SELECT)
    {
        MainWindow::setUtilityKey();
        QString _keyB = MainWindow::getUtilityKey();
        QByteArray _keyBytes = QByteArray::fromHex(_keyB.toLatin1());
            for( int i=0 ; i<=static_cast<int>(KEY_SIZE) ; i++ )
            {
                keyB[i] = _keyBytes[i];
            }
            for( int i=0 ; i<=static_cast<int>(KEY_SIZE) ; i++ )
            {
                m_sectorTrailer[i+10] = keyB[i];
            }
    }
}
void MainWindow::availability(uint8_t RCframe,uint8_t UIDframe, uint8_t tabs,
                  uint8_t keyAframe, uint8_t keyBframe, uint8_t RWframe, uint8_t VBframe,
                  uint8_t ACframe, uint8_t utilityChangeKeyFrame)
{
    ui->RCframe->setEnabled(RCframe & mask7);
            ui->connectReader->setEnabled(RCframe & mask6);
            ui->disconnectReader->setEnabled(RCframe & mask5);

        ui->UIDframe->setEnabled(UIDframe & mask7);
            ui->ConnectUID->setEnabled(UIDframe & mask6);
            ui->disconnectUID->setEnabled(UIDframe & mask5);

        ui->tabs->setEnabled(tabs & mask7);
            ui->Operations->setEnabled(tabs & mask6);
                ui->keyAframe->setEnabled(keyAframe & mask7);
                    ui->authWithKeyA->setEnabled(keyAframe & mask6);
                    ui->copyToKeyB->setEnabled(keyAframe & mask5);
                    ui->factoryKeyA->setEnabled(keyAframe & mask4);
                    ui->loadTo0A->setEnabled(keyAframe & mask3);
                    ui->loadTo1A->setEnabled(keyAframe & mask2);
                    ui->textKeyA->setEnabled(keyAframe & mask1);
                ui->keyBframe->setEnabled(keyBframe & mask7);
                    ui->authWithKeyB->setEnabled(keyBframe & mask6);
                    ui->copyToKeyA->setEnabled(keyBframe & mask5);
                    ui->factoryKeyB->setEnabled(keyBframe & mask4);
                    ui->loadTo0B->setEnabled(keyBframe & mask3);
                    ui->loadTo1B->setEnabled(keyBframe & mask2);
                    ui->textKeyB->setEnabled(keyBframe & mask1);
                ui->RWframe->setEnabled(RWframe & mask7);
                    ui->RWClear->setEnabled(RWframe & mask6);
                    ui->readBlock->setEnabled(RWframe & mask5);
                    ui->textRWblocks->setEnabled(RWframe & mask4);
                    ui->writeBlock->setEnabled(RWframe & mask3);
                ui->SBframe->setEnabled(tabs & mask2);
                ui->VBframe->setEnabled(VBframe & mask7);
                    ui->decVB->setEnabled(VBframe & mask6);
                    ui->incVB->setEnabled(VBframe & mask5);
                    ui->destinationBlockSelect->setEnabled(VBframe & mask4);
                    ui->restoreVB->setEnabled(VBframe & mask3);
                    ui->transferVB->setEnabled(VBframe & mask2);
                    ui->writeVB->setEnabled(VBframe & mask1);

            ui->RAW->setEnabled(tabs & mask5);

            ui->Utility->setEnabled(tabs & mask4);
                ui->utilityBlockFrame->setEnabled(tabs & mask1);
                    ui->readAccessConditions->setEnabled(tabs & mask0);

                ui->ACframe->setEnabled(ACframe & mask7);
                    ui->accessCondition->setEnabled(ACframe & mask6);
                    ui->accessConditionDB->setEnabled(ACframe & mask5);
                    ui->accessConditionDBChange->setEnabled(ACframe & mask4);
                    ui->accessConditionST->setEnabled(ACframe & mask3);
                    ui->accessConditionSTChange->setEnabled(ACframe & mask2);
                    ui->accessConditionSTRead->setEnabled(ACframe & mask1);
                ui->utilityChangeKeyFrame->setEnabled(utilityChangeKeyFrame & mask7);
                    ui->utilityKCTextClear->setEnabled(utilityChangeKeyFrame & mask6);
                    ui->utilityKCChange->setEnabled(utilityChangeKeyFrame & mask5);
               ui->utilityKeySelectFrame->setEnabled(utilityChangeKeyFrame & mask4);
            ui->Commands->setEnabled(tabs & mask3);
}




