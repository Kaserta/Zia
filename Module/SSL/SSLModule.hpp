/*
** EPITECH PROJECT, 2020
** SSLModule
** File description:
** SSLModule to have https connexion
*/

#ifndef SSLMODULE_HPP_
#define SSLMODULE_HPP_


class SSLModule;

#include "../Exporter.hpp"
#include "../AModule.hpp"
#include <fstream>
#include <iostream>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <openssl/bio.h>
#include <openssl/opensslv.h>


class EXPORT SSLModule : public AModule {
    public:
        SSLModule();
        ~SSLModule();
        const std::string &getName() const noexcept override {return _MName;};
        const std::string &getVersion() const noexcept override {return _MVersion;};
        void Receive(int socket_fd, std::string request, std::string config);
        void Send(std::string toSend);
        void SetHooks(std::shared_ptr<IHooks> &hooks) noexcept override  {};

    protected:
    private:
        SSL_CTX *_ctx;
        SSL *_ssl;
        uint16_t _port;
        std::string _address;
        bool _enabled = false;
};

#endif /* !SSLMODULE_HPP_ */
