#ifndef GAME_STATE_CLIENT_H
#define GAME_STATE_CLIENT_H

#include <vector>

class Game_state_client {
public:
    Game_state_client(int numPlayers);

    int getNumPlayers() const;

    const std::vector<bool>& getAliveStatus() const;
    const std::vector<bool>& getConnectedStatus() const;
    const int& getTarget(int ix) const;

    void setAliveStatus(int playerId, bool alive);
    void setConnectedStatus(int playerId, bool connected);
    void setTarget(int playerId, int targetId);
    void deletePlayer(int playerId, Game_state_client ame_state_client);

private:
    int numPlayers;

    std::vector<bool> aliveStatus;
    std::vector<bool> connectedStatus;
};

#endif
