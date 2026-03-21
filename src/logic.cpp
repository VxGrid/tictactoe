#include "logic.h"
#include <random>
#include <QQuickItem>

Logic::Logic(QObject *parent)
    : QObject{parent}
{
    states_ = std::vector<STATE>(9, NONE);
}


void Logic::setEngine(QQmlApplicationEngine *newEngine)
{
    engine_ = newEngine;
}


void Logic::setupGUI()
{
    QList<QObject*> rootObj = engine_->rootObjects();

    for (auto&obj : rootObj)
    {
        auto theGrid = obj->findChild<QObject*>("grid");
        connect(theGrid, SIGNAL(buttonClicked(QString)), this, SLOT(receiveAction(QString)));
        // for (int i = 0; i < 9; ++i)
        // {
        //     QObject *pb = obj->findChild<QObject*>(QString::fromStdString(std::to_string(i)));
        //     if (pb)
        //     {
        //         qDebug() << "connect now" << Qt::endl;
        //         connect(pb, SIGNAL(buttonClicked(QString)), this, SLOT(receiveAction(QString)));
        //     }
        // }
    }
}


void Logic::receiveAction(QString button)
{
    int index = button.toInt();
    QObject* rootObj = engine_->rootObjects().first();
    auto theGrid = rootObj->findChild<QObject*>("grid");
    QQuickItem* gridItem = qobject_cast<QQuickItem*>(theGrid);
    QQuickItem* buttonItem = gridItem->childItems().at(index);

    switch (states_[index])
    {
        case NONE:
            states_[index] = CIRCLE;
            buttonItem->setProperty("text", "O");
            break;

        case CIRCLE:
            break;

        case CROSS:
            break;

        default:
            break;
    }

    if (checkWinCondition(CIRCLE))
    {
        qDebug() << "Gratz you won" << Qt::endl;
        return;
    }

    if (std::none_of(std::begin(states_), std::end(states_), std::bind(std::equal_to<int>(),
                std::placeholders::_1, NONE)))
    {
        qWarning() << "Game over";
        return;
    }

    pcAction();

    if (checkWinCondition(CROSS))
    {
        qWarning() << "PC won - you looser";
        QObject* rootObj = engine_->rootObjects().first();
        auto theGrid = rootObj->findChild<QObject*>("grid");
        QQuickItem* gridItem = qobject_cast<QQuickItem*>(theGrid);
        gridItem->setEnabled(false);
    }
}


void Logic::pcAction()
{
    QObject* rootObj = engine_->rootObjects().first();
    auto theGrid = rootObj->findChild<QObject*>("grid");
    QQuickItem* gridItem = qobject_cast<QQuickItem*>(theGrid);

    switch (skill_)
    {
        case DUMB:
            for (int i = 0; i < states_.size(); ++i)
            {
                if (states_[i] == NONE)
                {
                    QQuickItem* buttonItem = gridItem->childItems().at(i);
                    states_[i] = CROSS;
                    buttonItem->setProperty("text", "X");
                    return;
                }
            }

        case MID:
        {
            std::random_device rd;
            std::mt19937 g(rd());

            while (true) {
                int field = g() % 9;
                qInfo() << "field: " << field;

                if (states_[field] == NONE)
                {
                    QQuickItem* buttonItem = gridItem->childItems().at(field);
                    states_[field] = CROSS;
                    buttonItem->setProperty("text", "X");
                    return;
                }
            }
        }

        case UNBEATABLE:
            /// FIXME: implement
            qWarning() << "FIXME" << Qt::endl;
            return;
    }
}


bool Logic::checkWinCondition(STATE state)
{
    /// I nix logic, so just handle all 8 winning cases
    // left right
    if (states_[0] == state && states_[1] == state && states_[2] == state) return true;

    if (states_[3] == state && states_[4] == state && states_[5] == state) return true;

    if (states_[6] == state && states_[7] == state && states_[8] == state) return true;

    // top down
    if (states_[0] == state && states_[3] == state && states_[6] == state) return true;

    if (states_[1] == state && states_[4] == state && states_[7] == state) return true;

    if (states_[2] == state && states_[5] == state && states_[8] == state) return true;

    // diagonal
    if (states_[0] == state && states_[4] == state && states_[8] == state) return true;

    if (states_[2] == state && states_[4] == state && states_[6] == state) return true;

    return false;
}
