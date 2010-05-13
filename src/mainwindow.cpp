#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowState(Qt::WindowMaximized);

    Initialize();
    createActions();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void MainWindow::createActions()
{
    dealTheCardsAct = new QAction("Deal the Cards", this);
    connect( dealTheCardsAct, SIGNAL( triggered() ), logic, SLOT( dealTheCards() ) );
    ui->mainToolBar->addAction(dealTheCardsAct);

    takeAllCardsAct = new QAction("Take all Cards", this);
    connect( takeAllCardsAct, SIGNAL( triggered() ), logic, SLOT( takeAllCards() ) );
    ui->mainToolBar->addAction(takeAllCardsAct);
}

void MainWindow::Initialize()
{
    logic = new Logic();
    connect(logic->renderer, SIGNAL(onClick()), this, SLOT(onClick()));
    setCentralWidget(logic->renderer);

    logic->createPlayer("yura", 1);
    logic->createPlayer("vova", 2);
    //logic->DealTheCards();
}

void MainWindow::onClick()
{
    logic->takeAllCards();
}
