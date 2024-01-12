#include "game_state_client.h"

// Constructor
Game_state_client::Game_state_client(int numPlayers) : numPlayers(numPlayers) {
    aliveStatus.resize(numPlayers, false);
    connectedStatus.resize(numPlayers, false);
}

int Game_state_client::getNumPlayers() const {
    return numPlayers;
}

const std::vector<bool>& Game_state_client::getAliveStatus() const {
    return aliveStatus;
}

const std::vector<bool>& Game_state_client::getConnectedStatus() const {
    return connectedStatus;
}


void Game_state_client::setAliveStatus(int playerId, bool alive) {
    if (playerId >= 0 && playerId < numPlayers) {
        aliveStatus[playerId] = alive;
    }
}

void Game_state_client::setConnectedStatus(int playerId, bool connected) {
    if (playerId >= 0 && playerId < numPlayers) {
        connectedStatus[playerId] = connected;
    }
}

void Game_state_client::deletePlayer(int PlayerId, Game_state_client game_state){
    game_state.setAliveStatus(PlayerId, true);
    game_state.setConnectedStatus(PlayerId, false);
    // game_state.setTarget(PlayerId, 0);
    // to nie działą
}








