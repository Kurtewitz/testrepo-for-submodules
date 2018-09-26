//
//  Connection.cpp
//  Server2
//
//  Created by intx on 23.09.18.
//  Copyright © 2018 intx. All rights reserved.
//

#include "Connection.hpp"
#include "Connection_Manager.hpp"
#include "Game.hpp"

Connection::ptr_Connection Connection::create(boost::asio::io_service &io_service) {
    static int count;
    count++;
    std::cout << "Create socket #" << count << std::endl;
    return std::shared_ptr<Connection>(new Connection(io_service), [k = count](auto p) { std::cout <<"Delete socket #" << k << std::endl;
        delete p;
    });
}

boost::asio::ip::tcp::socket &Connection::socket() {
    return socket_;
}

void Connection::start(){
    do_read();
}

void Connection::start(std::string startMessage) {
    do_read();
    do_write(startMessage);
}

void Connection::stop(){
    socket_.close();
}

Connection::~Connection() {
    std::cout << "Delete connection" << std::endl;
}

Connection::Connection(boost::asio::io_service &io_service)
: socket_(io_service) {
}

void Connection::addGame(std::shared_ptr<Game> newGame){
    if(newGame){
        this->game_ = newGame;
    }
    else {
        std::cout << "Connection::addGame()::Error, Can't add Game" << std::endl;
    }
}

void Connection::detachGame(){
    this->game_.reset();
}

void Connection::do_read()
{
    boost::asio::async_read(socket_, buffer_, boost::asio::transfer_at_least(1), boost::bind(&Connection::handle_read, shared_from_this(), boost::asio::placeholders::error));
}

void Connection::handle_read(const boost::system::error_code& error)
{
    auto self(shared_from_this());
    boost::asio::streambuf::const_buffers_type bufs = buffer_.data();
    std::string msg(boost::asio::buffers_begin(bufs),
                    boost::asio::buffers_begin(bufs) +
                    buffer_.size());
    
    buffer_.consume(buffer_.size());
    
    
    std::cout << "Got Message from:_" << socket_.remote_endpoint().address().to_string() << ":" << socket_.remote_endpoint().port() <<" ->: " << msg << std::endl;
    if(game_){
        if (game_->getAmountPlayer() == MaxPlayer){
            if(game_->broadcast(msg, self)){
                std::cout << "Broadcasted Message: " << msg << std::endl;
            }
        }
        else{
            std::cout << "!game_AmountPlayer" << std::endl;
        }
    }
    else if(connection_Manager_){
        connection_Manager_->handle_Request(self, msg);
    }
    else{
        std::cout << "!NO GAME OR CONNECTION_MANAGER" << std::endl;
    }
    do_read();
    
}

void Connection::do_write(std::string response)
{
    auto self(shared_from_this());
    response += "\r";
    boost::asio::async_write(socket_, boost::asio::buffer(response),[this, self, response](boost::system::error_code ec, std::size_t /*length*/) {
        if (!ec)
        {
            std::cout << "Send Message: " << response << std::endl;
        }
    });
}

void Connection::addConnectionManager(std::shared_ptr<Connection_Manager> connection_Manager) {
    if(connection_Manager)
        this->connection_Manager_ = connection_Manager;
}

bool Connection::connectToAccount(Account acc){
    if(acc.loggedIn && !this->account.loggedIn){
        this->account = acc;
        std::cout << "Added Account: " << acc.name << ":" << acc.password << std::endl;
        return true;
    }
    return false;
}

Account Connection::getAccount() {
    return this->account;
}
