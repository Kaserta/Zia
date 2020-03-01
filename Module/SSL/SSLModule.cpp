/*
** EPITECH PROJECT, 2020
** SSLModule
** File description:
** SSLModule
*/

#include "SSLModule.hpp"

SSLModule::SSLModule() : AModule("SSLModule", "0.1")
{
    OPENSSL_init_ssl(0, NULL);
    OpenSSL_add_ssl_algorithms();
    SSL_load_error_strings();
    this->_ctx = SSL_CTX_new(SSLv23_server_method());
    this->_enabled = true;
}

SSLModule::~SSLModule()
{
    SSL_free(this->_ssl);
    SSL_CTX_free(this->_ctx);
    EVP_cleanup();
}

void SSLModule::Receive(int socket_fd, std::string request, std::string config)
{
    std::ifstream certstream("certifacate.pem");
    std::ifstream keystream("key.pem");
    std::string certFile = std::string((std::istreambuf_iterator<char>(certstream)), std::istreambuf_iterator<char>());
    std::string keyFile =  std::string((std::istreambuf_iterator<char>(keystream)), std::istreambuf_iterator<char>());

    int client = socket_fd.getHandle();
    this->_port = socket_fd.getRemotePort();

    if (SSL_CTX_use_certificate_file(this->_ctx, certFile.c_str(), SSL_FILETYPE_PEM) < 1)
        return;
    if (SSL_CTX_use_PrivateKey_file(this->_ctx, keyFile.c_str(), SSL_FILETYPE_PEM) < 1)
        return;
    _ssl = SSL_new(this->_ctx);
    if (!_ssl)
        return;
    if (SSL_set_fd(_ssl, client) <= 0)
        return;
    if (_enabled == false)
        return;
    int	iResult;
    bool	no_error = true;
    do {
        iResult = SSL_accept(_ssl);
        switch(SSL_get_error(_ssl, iResult)) {
            case SSL_ERROR_NONE:
                break;
            case SSL_ERROR_ZERO_RETURN:
            case SSL_ERROR_WANT_READ:
                break;
            case SSL_ERROR_WANT_WRITE:
                break;
            case SSL_ERROR_WANT_CONNECT:
            case SSL_ERROR_WANT_ACCEPT:
            case SSL_ERROR_WANT_X509_LOOKUP:
            case SSL_ERROR_SYSCALL:
            case SSL_ERROR_SSL:
            default:
                no_error = false;
                break;
            }
        }
    while (iResult < 0 && no_error);
    const std::size_t readSize = 1024;
    std::size_t len = 0;
    for (;;) {
        char buff[readSize + 1] = {0};
        std::size_t recv = SSL_read(_ssl, buff, readSize);

        if (SSL_get_error(_ssl, recv) == SSL_ERROR_WANT_READ)
        break;
        buff[recv] = 0;
        request.append(buff, recv);
        len += recv;
        if (recv < readSize)
        break;
    }
}

void SSLModule::Send(std::string toSend)
{
    int	iResult;
    bool no_error = true;

    do {
        iResult = SSL_write(_ssl, toSend.c_str(), toSend.size());
        switch (SSL_get_error(_ssl, iResult)) {
            case SSL_ERROR_NONE:
                break;
            case SSL_ERROR_ZERO_RETURN:
            case SSL_ERROR_WANT_READ:
            case SSL_ERROR_WANT_WRITE:
                break;
            case SSL_ERROR_WANT_CONNECT:
            case SSL_ERROR_WANT_ACCEPT:
            case SSL_ERROR_WANT_X509_LOOKUP:
            case SSL_ERROR_SYSCALL:
            case SSL_ERROR_SSL:
            default:
                no_error = false;
                break;
        }
    }
    while (iResult > 0 && no_error);
}


extern "C"
{
    IModule *getModule()
    {
        return new SSLModule;
    }
    void deleteModule(SSLModule *module)
    {
        delete module;
    }
}