//
//  TCP_Server.hpp
//  Server2
//
//  Created by intx on 22.09.18.
//  Copyright © 2018 intx. All rights reserved.
//

#ifndef TCP_Server_hpp
#define TCP_Server_hpp
#define PORT_LISTEN 8000

#include "Connection_Manager.hpp"


class TCP_Server {
public:
    TCP_Server(boost::asio::io_service& io_service, std::shared_ptr<Connection_Manager> con_man);
    ~TCP_Server();
private:
    void do_accept();
    void do_await_stop();
    void handle_accept(Connection::ptr_Connection new_connection, const boost::system::error_code& error);
    
    boost::asio::signal_set signals_;
    boost::asio::ip::tcp::acceptor acceptor_;
    std::shared_ptr<Connection_Manager> connection_manager_;
};

#endif /* TCP_Server_hpp */
