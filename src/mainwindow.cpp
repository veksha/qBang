#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::AppendLog(const QString &line)
{
    //ui->textEdit->append(line);
    qDebug() << line;
}

MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowState(Qt::WindowMaximized);
    
    connect(engine.renderer, SIGNAL(onClick(QMouseEvent*)), this, SLOT(onClick(QMouseEvent*)));
    connect(engine.renderer, SIGNAL(onMouseMove(QMouseEvent*)), this, SLOT(onMouseMove(QMouseEvent*)));

    setCentralWidget(engine.renderer);    

    this->connect(&engine.pluginSystem, SIGNAL(AppendLog(QString)), SLOT(AppendLog(QString)));
    
    AppendLog("Program Started.\n");
    
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
    connect( dealTheCardsAct, SIGNAL( triggered() ), &engine, SLOT( dealTheCards() ) );
    ui->mainToolBar->addAction(dealTheCardsAct);

    takeAllCardsAct = new QAction("Take all Cards", this);
    connect( takeAllCardsAct, SIGNAL( triggered() ), &engine, SLOT( takeAllCards() ) );
    ui->mainToolBar->addAction(takeAllCardsAct);
}

void MainWindow::onClick(QMouseEvent * event)
{
    QPointF pos = engine.renderer->mapToScene(event->pos());
    engine.SelectCardAt(pos);
}

void MainWindow::onMouseMove(QMouseEvent *event)
{
    QPointF pos = engine.renderer->mapToScene(event->pos());
    setWindowTitle( QString("x = %1, y = %2")
                    .arg(pos.x())
                    .arg(pos.y()) );
}

