#include "worldwidget.h"

#include <QHeaderView>

WorldWidget::WorldWidget(QWidget* parent)
    :QTableWidget(parent)
{
    init();
}

WorldWidget::WorldWidget(int rows, int columns, QWidget *parent)
    :QTableWidget(rows, columns, parent)
{
    emit initBinaryMap(rows, columns);

    for(int i = 0; i < rows; ++i)
    {
        for(int j = 0; j < columns; ++j)
        {
            QTableWidgetItem* item = new QTableWidgetItem;
            item->setBackgroundColor(Qt::white);
            setItem(i, j, item);
        }
    }
    init();
}

void WorldWidget::init()
{
    setSelectionMode(QAbstractItemView::NoSelection);
    setEditTriggers(QAbstractItemView::NoEditTriggers);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    verticalHeader()->hide();
    horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    horizontalHeader()->hide();
}

void WorldWidget::switchBackground(int row, int column)
{
    QTableWidgetItem* currItem = item(row, column);

    if(currItem->backgroundColor() == Qt::white)
        currItem->setBackgroundColor(Qt::red);
    else
        currItem->setBackgroundColor(Qt::white);
}

void WorldWidget::getSettings(QSettings &settings)
{
    settings.beginGroup("/Settings");
    int rows = settings.value("/rows", rowCount()).toInt();
    int columns = settings.value("/columns", columnCount()).toInt();
    settings.endGroup();

    if(rowCount() != rows || columnCount() != columns)
    {
        setRowCount(rows);
        setColumnCount(columns);

        for(int i = 0; i < rows; ++i)
        {
            for(int j = 0; j < columns; ++j)
            {
                if(item(i, j) == nullptr)
                {
                    QTableWidgetItem* item = new QTableWidgetItem;
                    item->setBackgroundColor(Qt::white);
                    setItem(i, j, item);
                }
            }
        }
    }
}

void WorldWidget::setCellColorByCondition(int row, int column, bool condition)
{
    QTableWidgetItem* tempItem = item(row, column);
    if(condition == false)
        tempItem->setBackgroundColor(Qt::white);
    else tempItem->setBackgroundColor(Qt::red);
}
