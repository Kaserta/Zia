/*
** EPITECH PROJECT, 2020
** HttpRequest
** File description:
** HttpRequest
*/

#ifndef HTTPREQUEST_HPP_
#define HTTPREQUEST_HPP_

#include <array>
#include <iostream>

class HttpRequest {
    public:
        HttpRequest();
        ~HttpRequest();

    protected:
    private:
        const std::array<std::string, 8> methods = {
            "GET",
            "POST",
            "HEAD",
            "PUT",
            "DELETE",
            "TRACE",
            "CONNECT",
            "OPTIONS"
        };
         const std::array<std::string, 19> headers = {
            "Accept",
            "Accept-Charset",
            "Accept-Encoding",
            "Accept-Language",
            "Authorization",
            "Expect",
            "From",
            "Host",
            "If-Match",
            "If-Modified-Since",
            "If-None-Match",
            "If-Range",
            "If-Unmodified-Since",
            "Max-Forwards",
            "Proxy-Authorization",
            "Range",
            "Referer",
            "TE",
            "User-Agent"
        };
};

#endif /* !HTTPREQUEST_HPP_ */
