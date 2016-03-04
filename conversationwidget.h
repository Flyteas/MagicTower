#ifndef CONVERSATIONWIDGET_H
#define CONVERSATIONWIDGET_H

#include <QWidget>

namespace Ui {
class ConversationWidget;
}

class ConversationWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ConversationWidget(QWidget*,QString);
    ~ConversationWidget();
    bool SetConversationText(QString,bool); //显示对话内容

private:
    Ui::ConversationWidget *ui;
};

#endif // CONVERSATIONWIDGET_H
