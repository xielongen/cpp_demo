//
// Created by x on 19-12-5.
//
#include <gtest/gtest.h>
#include <string>
#include <iostream>
#include <boost/asio.hpp>

TEST(BOOST, NETWOKR){
    using boost::asio::ip::tcp;
    try
    {
        boost::asio::io_service io_service;
        tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), 13));
        while(true)
        {
            tcp::socket socket(io_service);
            acceptor.accept(socket);

            std::string msg = "Hello, world";
            boost::system::error_code ignored_err;
            boost::asio::write(socket, boost::asio::buffer(msg), ignored_err);
        }
    }
    catch(std::exception& err)
    {
        std::cerr << err.what() << std::endl;
    }
}

