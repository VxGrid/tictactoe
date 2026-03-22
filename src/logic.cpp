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

    if (checkWinCondition(states_, CIRCLE))
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

    if (checkWinCondition(states_, CROSS))
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
        {
            switch (std::count(std::begin(states_), std::end(states_), CIRCLE))
            {
                case 1: // first move
                {
                    int field{4};

                    if (states_[field] == NONE)
                    {
                        QQuickItem* buttonItem = gridItem->childItems().at(field);
                        states_[field] = CROSS;
                        buttonItem->setProperty("text", "X");
                        return;
                    }
                    else
                    {
                        field = 0;
                        QQuickItem* buttonItem = gridItem->childItems().at(field);
                        states_[field] = CROSS;
                        buttonItem->setProperty("text", "X");
                        return;
                    }

                    break;
                }

                case 2: // second move
                {
                    // here we need to check if Circle can win in next move
                    for (int i = 0; i < states_.size(); ++i)
                    {
                        if (states_[i] == NONE)
                        {
                            auto states = states_;
                            states[i] = CIRCLE;

                            if (checkWinCondition(states, CIRCLE))
                            {
                                QQuickItem* buttonItem = gridItem->childItems().at(i);
                                states_[i] = CROSS;
                                buttonItem->setProperty("text", "X");
                                return;
                            }
                        }
                    }

                    // can't win - we check if we are in trap
                    if ((states_[0] == CIRCLE && states_[5] == CIRCLE)
                        ||
                        (states_[1] == CIRCLE && states_[8] == CIRCLE))
                    {
                        QQuickItem* buttonItem = gridItem->childItems().at(2);
                        states_[2] = CROSS;
                        buttonItem->setProperty("text", "X");
                        return;
                    }
                    else if ((states_[0] == CIRCLE && states_[7] == CIRCLE)
                        ||
                        (states_[3] == CIRCLE && states_[8] == CIRCLE))
                    {
                        QQuickItem* buttonItem = gridItem->childItems().at(6);
                        states_[6] = CROSS;
                        buttonItem->setProperty("text", "X");
                        return;
                    }
                    else if ((states_[2] == CIRCLE && states_[3] == CIRCLE)
                        ||
                        (states_[1] == CIRCLE && states_[6] == CIRCLE))
                    {
                        QQuickItem* buttonItem = gridItem->childItems().at(0);
                        states_[0] = CROSS;
                        buttonItem->setProperty("text", "X");
                        return;
                    }
                    else if ((states_[2] == CIRCLE && states_[7] == CIRCLE)
                        ||
                        (states_[5] == CIRCLE && states_[6] == CIRCLE))
                    {
                        QQuickItem* buttonItem = gridItem->childItems().at(8);
                        states_[8] = CROSS;
                        buttonItem->setProperty("text", "X");
                        return;
                    }

                    if ((states_[0] == CIRCLE && states_[8] == CIRCLE)
                        ||
                        (states_[2] == CIRCLE && states_[6] == CIRCLE))
                    {
                        QQuickItem* buttonItem = gridItem->childItems().at(1);
                        states_[1] = CROSS;
                        buttonItem->setProperty("text", "X");
                        return;
                    }

                    for (int i : {
                            0, 2, 6, 8
                        })
                    {
                        if (states_[i] == NONE)
                        {
                            QQuickItem* buttonItem = gridItem->childItems().at(i);
                            states_[i] = CROSS;
                            buttonItem->setProperty("text", "X");
                            return;
                        }
                    }
                }

                default:
                {
                    // starting with third move - we need to check for offence, then for defense
                    for (int i = 0; i < states_.size(); ++i)
                    {
                        if (states_[i] == NONE)
                        {
                            auto states = states_;
                            states[i] = CROSS;

                            if (checkWinCondition(states, CROSS))
                            {
                                QQuickItem* buttonItem = gridItem->childItems().at(i);
                                states_[i] = CROSS;
                                buttonItem->setProperty("text", "X");
                                return;
                            }
                        }
                    }

                    for (int i = 0; i < states_.size(); ++i)
                    {
                        if (states_[i] == NONE)
                        {
                            auto states = states_;
                            states[i] = CIRCLE;

                            if (checkWinCondition(states, CIRCLE))
                            {
                                QQuickItem* buttonItem = gridItem->childItems().at(i);
                                states_[i] = CROSS;
                                buttonItem->setProperty("text", "X");
                                return;
                            }
                        }
                    }

                    skill_ = MID;
                    pcAction();
                    skill_ = UNBEATABLE;
                }
                break;
            }

            return;
        }
    }
}


bool Logic::checkWinCondition(const std::vector<STATE> &states, STATE state) const
{
    /// I nix logic, so just handle all 8 winning cases
    // left right
    if (states[0] == state && states[1] == state && states[2] == state) return true;

    if (states[3] == state && states[4] == state && states[5] == state) return true;

    if (states[6] == state && states[7] == state && states[8] == state) return true;

    // top down
    if (states[0] == state && states[3] == state && states[6] == state) return true;

    if (states[1] == state && states[4] == state && states[7] == state) return true;

    if (states[2] == state && states[5] == state && states[8] == state) return true;

    // diagonal
    if (states[0] == state && states[4] == state && states[8] == state) return true;

    if (states[2] == state && states[4] == state && states[6] == state) return true;

    return false;
}
