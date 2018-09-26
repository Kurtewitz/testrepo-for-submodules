//
//  Connection_Manager.hpp
//  Server2
//
//  Created by intx on 23.09.18.
//  Copyright © 2018 intx. All rights reserved.
//

#ifndef Connection_Manager_hpp
#define Connection_Manager_hpp

#include "Game.hpp"

class Connection_Manager : public std::enable_shared_from_this<Connection_Manager>, private boost::noncopyable
{
public:
    typedef std::shared_ptr<Connection_Manager> ptr_Connection_Manager;
    Connection_Manager();
    ~Connection_Manager();
    
    void add_Connection(Connection::ptr_Connection connection);
    void erase_Connection(Connection::ptr_Connection connection);
    void connectToGame(Connection::ptr_Connection connection);
    void handle_Request(Connection::ptr_Connection connection, std::string request);
    
private:
    
    std::multimap<Game::ptr_Game, Connection::ptr_Connection> mmap_;
    std::vector<Connection::ptr_Connection> connections;
    std::shared_ptr<Game> freeGame;
};
#endif /* Connection_Manager_hpp */
