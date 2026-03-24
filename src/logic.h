#ifndef LOGIC_H
#define LOGIC_H

#include <QObject>
#include <qqmlapplicationengine.h>
#include <qquickitem.h>

class Logic : public QObject
{
    Q_OBJECT
public:
    explicit Logic(QObject *parent = nullptr);

    void setEngine(QQmlApplicationEngine *newEngine);

    void setupGUI();

public slots:
    void reset();
    void setSkill(QString button);

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
    QQuickItem* getItem(const QString&name);
    void pcAction();
    bool checkWinCondition(const std::vector<STATE>&states, STATE state) const;
    QQmlApplicationEngine* engine_;
    std::vector<STATE> states_;
    QStringList stupidTexts_;
    PCSKILL skill_{DUMB};
    uint8_t stupidTextPos_{};
    bool player_{true};

};

#endif // LOGIC_H
