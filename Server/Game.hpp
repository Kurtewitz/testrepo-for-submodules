//
//  Game.hpp
//  Server
//
//  Created by intx on 21.09.18.
//  Copyright © 2018 intx. All rights reserved.
//

#ifndef Game_hpp
#define Game_hpp

#define MaxSessions 10
#define MaxPlayer 2

#include "Connection.hpp"
#include <map>

class Connection;

class Game : public std::enable_shared_from_this<Game>, private boost::noncopyable
{
public:
    typedef std::shared_ptr<Game> ptr_Game;
    static ptr_Game create();
    
    ~Game();
    
    void startGame() throw();
    bool broadcast(std::string mssg, std::shared_ptr<Connection> connection);
    bool addPlayer(Connection::ptr_Connection newPlayer);
    
    int getAmountPlayer();
    
private:
    int id = -69;
    Game(int gameID);
    bool gameRDY;
    void cleanArr();
    Connection::ptr_Connection player[MaxPlayer];
    
};

#endif /* Game_hpp */
