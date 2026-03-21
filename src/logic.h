#ifndef LOGIC_H
#define LOGIC_H

#include <QObject>
#include <qqmlapplicationengine.h>

class Logic : public QObject
{
    Q_OBJECT
public:
    explicit Logic(QObject *parent = nullptr);

    void setEngine(QQmlApplicationEngine *newEngine);

    void setupGUI();

signals:

private:
    enum STATE
    {
        NONE,
        CIRCLE,
        CROSS,
    };
    enum PCSKILL
    {
        DUMB,
        MID,
        UNBEATABLE,
    };

private slots:
    void receiveAction(QString button);

private:
    void pcAction();
    bool checkWinCondition(STATE state);
    QQmlApplicationEngine* engine_;
    std::vector<STATE> states_;
    PCSKILL skill_{MID};
    bool player_{true};

};

#endif // LOGIC_H
