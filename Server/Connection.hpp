//
//  Connection.hpp
//  Server2
//
//  Created by intx on 23.09.18.
//  Copyright © 2018 intx. All rights reserved.
//

#ifndef Connection_hpp
#define Connection_hpp

#define bufSize 200

#include <iostream>
#include <stdio.h>
#include <array>
#include <algorithm>
#include <boost/asio.hpp>
#include <boost/bind.hpp>

#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/thread/thread.hpp>

struct Account{
    std::string name;
    std::string password;
    bool loggedIn;
};

class Game;
class Connection_Manager;

class Connection : public std::enable_shared_from_this<Connection>,
private boost::noncopyable
{
public:
    typedef std::shared_ptr<Connection> ptr_Connection;
    static ptr_Connection create(boost::asio::io_service& io_service);
    ~Connection();
    
  
    void addGame(std::shared_ptr<Game> newGame);
    void detachGame();
    void addConnectionManager(std::shared_ptr<Connection_Manager> connection_Manager);
    bool connectToAccount(Account acc);
    Account getAccount();
    
    void do_write(std::string response);
    boost::asio::ip::tcp::socket& socket();
    void start();
    void start(std::string startMessage);
    void stop();
    void handle_read(const boost::system::error_code& error);
    
private:
    Connection(boost::asio::io_service& io_service);
    void do_read();
    
    std::shared_ptr<Game> game_;
    std::shared_ptr<Connection_Manager> connection_Manager_;
    Account account;
    boost::asio::ip::tcp::socket socket_;
    boost::asio::streambuf buffer_;
};

#endif /* Connection_hpp */
