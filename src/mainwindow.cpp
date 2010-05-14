#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowState(Qt::WindowMaximized);

    initializeLogic();
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

void MainWindow::initializeLogic()
{
    logic = new Logic();
    connect(logic->renderer, SIGNAL(onClick(QMouseEvent*)), this, SLOT(onClick(QMouseEvent*)));
    connect(logic->renderer, SIGNAL(onMouseMove(QMouseEvent*)), this, SLOT(onMouseMove(QMouseEvent*)));

    setCentralWidget(logic->renderer);

    logic->createPlayer("yura", 1);
    logic->createPlayer("vova", 2)->setHealth(5);
}

void MainWindow::onClick(QMouseEvent *event)
{

}

void MainWindow::onMouseMove(QMouseEvent *event)
{
    QPointF pos = logic->renderer->mapToScene(event->pos());
    setWindowTitle( QString("x = %1, y = %2")
                    .arg(pos.x())
                    .arg(pos.y()) );
}

