#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QMouseEvent>

#include "src/cardgameengine.h"
#include "pluginsystem.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    PluginSystem pluginSystem;
    CardGameEngine *engine;

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

private slots:
    void AppendLog(const QString &line);
};

#endif // MAINWINDOW_H
