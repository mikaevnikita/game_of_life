#include "mainwindow.h"

#include <QHeaderView>
#include <QChar>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    :QMainWindow(parent)
{
    resize(1000, 600);

    setWindowTitle("Conways game of Life by Mikaev");

    cWidget = new QWidget;
    cLayout = new QHBoxLayout(cWidget);

    mainWidget = new QWidget;
    cLayout->addWidget(mainWidget);
    mainLayout = new QGridLayout(mainWidget);

    game = new Game;
    connect(game, SIGNAL(gameConditionSwitched(Game::GameCondition)), this, SLOT(switchStartButtonTextByGameCondition(Game::GameCondition)));

    worldWidget = new WorldWidget;
    connect(worldWidget, SIGNAL(cellClicked(int,int)), game, SLOT(switchCellCondition(int,int)));
    connect(game, SIGNAL(cellClicked(int,int)), worldWidget, SLOT(switchBackground(int,int)));
    connect(worldWidget, SIGNAL(initBinaryMap(int,int)), game, SLOT(initBinaryMap(int,int)));
    connect(game, SIGNAL(setCellColorByCondition(int,int,bool)), worldWidget, SLOT(setCellColorByCondition(int,int,bool)));
    mainLayout->addWidget(worldWidget, 0, 0, 1, mainLayout->columnCount());

    buttonsLayout = new QHBoxLayout;

    firstGenerationButton = new QPushButton("First generation");
    firstGenerationButton->setMinimumSize(50, 50);
    connect(firstGenerationButton, SIGNAL(clicked(bool)), game, SLOT(firstSnapshot()));
    buttonsLayout->addWidget(firstGenerationButton);

    previousGenerationButton = new QPushButton("Previous generation");
    previousGenerationButton->setMinimumSize(50, 50);
    connect(previousGenerationButton, SIGNAL(clicked(bool)), game, SLOT(prevSnapshot()));
    buttonsLayout->addWidget(previousGenerationButton);

    startGameButton = new QPushButton("Start game");
    startGameButton->setMinimumSize(50, 50);
    connect(startGameButton, SIGNAL(clicked(bool)), game, SLOT(switchGameConditon())); // start/pause game
    buttonsLayout->addWidget(startGameButton);

    nextGenerationButton = new QPushButton("Next generation");
    nextGenerationButton->setMinimumSize(50, 50);
    connect(nextGenerationButton, SIGNAL(clicked(bool)), game, SLOT(nextSnapshot()));
    buttonsLayout->addWidget(nextGenerationButton);

    clearButton = new QPushButton("Clear");
    clearButton->setMinimumSize(50, 50);
    connect(clearButton, SIGNAL(clicked(bool)), worldWidget, SLOT(clear()));
    connect(clearButton, SIGNAL(clicked(bool)), game, SLOT(clear()));
    buttonsLayout->addWidget(clearButton);

    settingsButton = new QPushButton("Settings");
    settingsButton->setMinimumSize(50, 50);
    connect(settingsButton, SIGNAL(clicked(bool)), SLOT(openSettings()));
    buttonsLayout->addWidget(settingsButton);

    mainLayout->addLayout(buttonsLayout, mainLayout->rowCount() , 0);

    settingsWidget = new SettingsWidget;
    settingsWidget->hide();
    connect(this, SIGNAL(settingsRequest()), settingsWidget, SLOT(getSettingsRequest()));
    connect(settingsWidget, SIGNAL(sendSettings(QSettings&)), game, SLOT(getSettings(QSettings&)));
    connect(settingsWidget, SIGNAL(sendSettings(QSettings&)), worldWidget, SLOT(getSettings(QSettings&)));
    connect(settingsWidget, SIGNAL(close()), this, SLOT(closeSettings()));
    cLayout->addWidget(settingsWidget);

    setCentralWidget(cWidget);

    emit settingsRequest();
}

MainWindow::~MainWindow()
{

}

void MainWindow::openSettings()
{
    mainWidget->hide();
    settingsWidget->setHidden(false);
}

void MainWindow::closeSettings()
{
    settingsWidget->hide();
    mainWidget->setHidden(false);
}

void MainWindow::switchStartButtonTextByGameCondition(Game::GameCondition condition)
{
    if(condition == Game::GameCondition::BEFOTRE_GAME)
        startGameButton->setText("Start");
    else
        startGameButton->setText("Pause");
}
