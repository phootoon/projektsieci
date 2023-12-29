#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <vector>
#include <chrono>

class Game_state {
public:
    Game_state(int numPlayers);

    int getNumPlayers() const;

    const std::vector<bool>& getAliveStatus() const;
    const std::vector<bool>& getConnectedStatus() const;
    const std::vector<int>& getTargets() const;
    const std::vector<float>& getProbabilities() const;
    const int& getTarget(int ix) const;
    const std::vector<bool>& getReadys() const;
    const std::vector<bool>& getVotes() const;
    const std::chrono::time_point<std::chrono::high_resolution_clock>& getAimTS() const;

    void setAliveStatus(int playerId, bool alive);
    void setConnectedStatus(int playerId, bool connected);
    void setTarget(int playerId, int targetId);
    void setProbability(int playerId, float probability);
    void setReady(int playerId, bool ready);
    void setVote(int playerId, bool vote);
    void setAimTS(int playerId, std::chrono::time_point<std::chrono::high_resolution_clock> ts);

    void deletePlayer(int playerId, Game_state game_state);

private:
    int numPlayers;

    std::vector<bool> aliveStatus;
    std::vector<bool> connectedStatus;
    std::vector<int> targets;
    std::vector<float> probabilities;
    std::vector<bool> readys;
    std::vector<bool> votes;
    std::vector<std::chrono::time_point<std::chrono::high_resolution_clock>> aimTS;
};

#endif
