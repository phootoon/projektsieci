#include "game_state.h"

Game_state::Game_state(int numPlayers) : numPlayers(numPlayers) {
    aliveStatus.resize(numPlayers, false);
    connectedStatus.resize(numPlayers, false);
    targets.resize(numPlayers, -1);
    aimTS.resize(numPlayers,std::chrono::high_resolution_clock::time_point::max());
}

int Game_state::getNumPlayers() const {
    return numPlayers;
}

const std::vector<bool>& Game_state::getAliveStatus() const {
    return aliveStatus;
}

const std::vector<bool>& Game_state::getConnectedStatus() const {
    return connectedStatus;
}

const std::vector<int>& Game_state::getTargets() const {
    return targets;
}

const int& Game_state::getTarget(int ix) const {
    return targets[ix];
}

const std::vector<float>& Game_state::getProbabilities() const {
    return probabilities;
}

const std::vector<bool>& Game_state::getReadys() const {
    return readys;
}

const std::vector<bool>& Game_state::getVotes() const {
    return votes;
}

const std::chrono::time_point<std::chrono::high_resolution_clock>& Game_state::getAimTS(int playerId) const {
    return aimTS[playerId];
}

void Game_state::setAliveStatus(int playerId, bool alive) {
    if (playerId >= 0 && playerId < numPlayers) {
        aliveStatus[playerId] = alive;
    }
}

void Game_state::setReady(int playerId, bool ready) {
    if (playerId >= 0 && playerId < numPlayers) {
        readys[playerId] = ready;
    }
}

void Game_state::setVote(int playerId, bool vote) {
    if (playerId >= 0 && playerId < numPlayers) {
        aliveStatus[playerId] = vote;
    }
}

void Game_state::setConnectedStatus(int playerId, bool connected) {
    if (playerId >= 0 && playerId < numPlayers) {
        connectedStatus[playerId] = connected;
    }
}

void Game_state::setTarget(int playerId, int targetId) {
    if (playerId >= 0 && playerId < numPlayers && targetId >= 0 && targetId < numPlayers) {
        targets[playerId] = targetId;
    }
}

void Game_state::setProbability(int playerId, float probability) {
    if (playerId >= 0 && playerId < numPlayers) {
        probabilities[playerId] = probability;
    }
}

void Game_state::setAimTS(int playerId, std::chrono::time_point<std::chrono::high_resolution_clock> ts) {
    if (playerId >= 0 && playerId < numPlayers) {
        aimTS[playerId] = ts;
    }
}

void Game_state::deletePlayer(int PlayerId){
    this->setAliveStatus(PlayerId, false);
    this->setConnectedStatus(PlayerId, false);
    this->setTarget(PlayerId, -1);

}








