#ifndef PLAYER_H
#define PLAYER_H

class Player {
public:
    Player();

    ~Player();

    bool isAlive() const;
    bool isConnected() const;
    int getTargetIndex() const;

    void setAlive(bool alive);
    void setConnected(bool connected);
    void setTargetIndex(int targetIndex);

private:
    bool alive;
    bool connected;
    int targetIndex;
};

#endif
