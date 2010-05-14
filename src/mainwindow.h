#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QMouseEvent>

#include "logic.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    Logic *logic;

protected:
    void changeEvent(QEvent *e);

private:
    Ui::MainWindow *ui;

    void createActions();
    QAction *dealTheCardsAct;
    QAction *takeAllCardsAct;

public slots:
    void initializeLogic();
    void onClick(QMouseEvent *);
    void onMouseMove(QMouseEvent *);

};

#endif // MAINWINDOW_H
