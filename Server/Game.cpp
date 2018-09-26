//
//  Game.cpp
//  Server
//
//  Created by intx on 21.09.18.
//  Copyright © 2018 intx. All rights reserved.
//

#include "Game.hpp"


Game::Game(int gameID){
    this->id = gameID;
    this->cleanArr();
}

Game::ptr_Game Game::create() {
    static int count;
    count++;
    std::cout << "Create Game #" << count << std::endl;
    return std::shared_ptr<Game>(new Game(count), [k = count](auto p) {
        std::cout <<"Delete Game" << k << std::endl;
        delete p;
    });
}

Game::~Game(){
}

void Game::startGame() throw(){
    std::stringstream to1, to2;
    std::string ip1 =player[0]->socket().remote_endpoint().address().to_string() + ", " + player[0]->getAccount().name;
    std::string ip2 =player[1]->socket().remote_endpoint().address().to_string() + ", " + player[1]->getAccount().name;
    std::cout << "Start Game with: " << ip1 << "&&" << ip2 << std::endl;
    
    to1 << "GAMEREADY [";
    to1 << ip2;
    to1 << "]";
    to2 << "GAMEREADY [";
    to2 << ip1;
    to2 << "]";
    this->player[0]->do_write(to1.str());
    this->player[1]->do_write(to2.str());
}

bool Game::broadcast(std::string mssg, std::shared_ptr<Connection> connection){
    int ret = 1;
    for(int i = 0; i < MaxPlayer; i++){
        if(player[i] && player[i].get() != connection.get()){
            player[i]->do_write(mssg);
            ret++;
        }
    }
    if(ret == MaxPlayer){
        return true;
    }
    return false;
}

bool Game::addPlayer(Connection::ptr_Connection newPlayer){
    for(int i = 0; i < MaxPlayer; i++){
        if (!player[i]){
            player[i] = newPlayer;
            newPlayer->start(std::to_string(i+1));
            if(this->getAmountPlayer() == MaxPlayer){
                std::cout << "Game #" << this->id << " - PlayerAmount == MaxPlayer" << std::endl;
                this->startGame();
                return true;
            }
            std::cout << "Game #" << this->id << " - Size = " << this->getAmountPlayer() << ":" << MaxPlayer <<std::endl;
            return true;
        }
    }
    return false;
}

int Game::getAmountPlayer(){
    int ret = 0;
    for(int i = 0; i < MaxPlayer; i++){
        if(player[i])
            ret++;
    }
    return ret;
}

void Game::cleanArr(){
    memset(this->player, 0, (sizeof(this->player) / sizeof(this->player[0])));
    for(int i = 0; i < MaxPlayer; i++){
        player[i] = nullptr;
    }
}
