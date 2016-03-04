#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QLabel>
#include <ExternVar.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
public slots:
    bool HeroStateLabelDisplayChange(const HeroState&);
protected:
    void closeEvent(QCloseEvent *);
private slots:
    void keyPressEvent(QKeyEvent*);

    void on_SaveButton_clicked();

    void on_ResetButton_clicked();

private:
    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
