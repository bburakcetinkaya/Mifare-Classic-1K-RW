#include "Headers/mainwindow.h"
#include "Sources/mainwindow.cpp"

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


void MainWindow::on_copyToKeyB_clicked()
{
    ui->keyB0->setPlainText(ui->keyA0->toPlainText());
    ui->keyB1->setPlainText(ui->keyA1->toPlainText());
    ui->keyB2->setPlainText(ui->keyA2->toPlainText());
    ui->keyB3->setPlainText(ui->keyA3->toPlainText());
    ui->keyB4->setPlainText(ui->keyA4->toPlainText());
    ui->keyB5->setPlainText(ui->keyA5->toPlainText());
}


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


void MainWindow::on_copyToKeyA_clicked()
{
    ui->keyA0->setPlainText(ui->keyB0->toPlainText());
    ui->keyA1->setPlainText(ui->keyB1->toPlainText());
    ui->keyA2->setPlainText(ui->keyB2->toPlainText());
    ui->keyA3->setPlainText(ui->keyB3->toPlainText());
    ui->keyA4->setPlainText(ui->keyB4->toPlainText());
    ui->keyA5->setPlainText(ui->keyB5->toPlainText());
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

void MainWindow::on_RWClear_clicked()
{
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
}