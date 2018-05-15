#ifndef WORLD_WIDGET_H
#define WORLD_WIDGET_H

#include <QTableWidget>
#include <QVector>
#include <QSettings>

class WorldWidget : public QTableWidget
{
    Q_OBJECT

public:
    WorldWidget(QWidget* parent = nullptr);
    WorldWidget(int rows, int columns, QWidget* parent = nullptr);

private:
    void init();

signals:
    void initBinaryMap(int rows, int columns);
    void settingsRequest(int rows, int columns);

private slots:
    void switchBackground(int row, int column);
    void getSettings(QSettings &settings);
    void setCellColorByCondition(int row, int column, bool condition);
};

#endif
