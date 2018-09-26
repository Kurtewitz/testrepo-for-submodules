//
//  TCP_Server.cpp
//  Server2
//
//  Created by intx on 22.09.18.
//  Copyright © 2018 intx. All rights reserved.
//

#include "TCP_Server.hpp"

using boost::asio::ip::tcp;

TCP_Server::TCP_Server(boost::asio::io_service &io_service, std::shared_ptr<Connection_Manager> con_man) : acceptor_(io_service, tcp::endpoint(tcp::v4(), u_short(8000))), signals_(io_service), connection_manager_(con_man) {
    do_accept();
}

TCP_Server::~TCP_Server(){
}

void TCP_Server::do_accept() {
    
    Connection::ptr_Connection new_connection = Connection::create(acceptor_.get_io_service());
    
    acceptor_.async_accept(new_connection->socket(), [this, new_connection](const auto &error) {
        if (!acceptor_.is_open())
        {
            std::cout << "Acceptor != is_open()" << std::endl;
            return;
        }
        if (!error) {
            std::cout << "New Connection_" << new_connection->socket().remote_endpoint().address().to_string() << ":" << new_connection->socket().remote_endpoint().port() << std::endl;
            connection_manager_->add_Connection(new_connection);
        }
        do_accept();
        std::cout << "SERVER::do_accept()" << std::endl;
    });
}

void TCP_Server::do_await_stop()
{
    signals_.async_wait([this](boost::system::error_code /*ec*/, int /*signo*/)
    {// The server is stopped by cancelling all outstanding asynchronous
        // operations. Once all operations have finished the io_service::run()
        // call will exit.
        acceptor_.close();
        //connection_manager_.stop_all();
    });
}

