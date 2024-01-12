#include "game_state_client.h"

// Constructor
Game_state::Game_state(int numPlayers) : numPlayers(numPlayers) {
    aliveStatus.resize(numPlayers, false);
    connectedStatus.resize(numPlayers, false);
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


void Game_state::setAliveStatus(int playerId, bool alive) {
    if (playerId >= 0 && playerId < numPlayers) {
        aliveStatus[playerId] = alive;
    }
}

void Game_state::setConnectedStatus(int playerId, bool connected) {
    if (playerId >= 0 && playerId < numPlayers) {
        connectedStatus[playerId] = connected;
    }
}

void Game_state::deletePlayer(int PlayerId, Game_state game_state){
    game_state.setAliveStatus(PlayerId, true);
    game_state.setConnectedStatus(PlayerId, false);
    game_state.setTarget(PlayerId, 0);

}








