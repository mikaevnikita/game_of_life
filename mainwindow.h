#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "worldwidget.h"
#include "settingswidget.h"
#include "game.h"

#include <QMainWindow>
#include <QGridLayout>
#include <QPushButton>

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    QWidget* cWidget;
    QHBoxLayout* cLayout;

    QWidget* mainWidget;
    QGridLayout* mainLayout;

    WorldWidget* worldWidget;
    SettingsWidget* settingsWidget;

    QHBoxLayout* buttonsLayout;
    QPushButton* startGameButton;
    QPushButton* nextGenerationButton;
    QPushButton* previousGenerationButton;
    QPushButton* firstGenerationButton;
    QPushButton* clearButton;
    QPushButton* settingsButton;

    Game* game; // Логика игры

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:
    void settingsRequest();

private slots:
    void openSettings();
    void closeSettings();
    void switchStartButtonTextByGameCondition(Game::GameCondition condition);
};

#endif // MAINWINDOW_H
