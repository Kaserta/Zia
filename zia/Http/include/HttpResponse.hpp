/*
** EPITECH PROJECT, 2020
** HttpsResponse
** File description:
** HttpResponseCodes
*/

#ifndef HTTPRESPONSE_HPP_
#define HTTPRESPONSE_HPP_

#include <map>
#include <memory>
#include <iostream>

class HttpResponse {
    public:
        HttpResponse();
        ~HttpResponse();

    protected:
    private:
        const std::map<uint32_t, std::string> response_codes = {

        {100, "Continue"},
        {101, "SwitchingProtocols"},

        {200, "Ok"},
        {201, "Created"},
        {202, "Accepted"},
        {203, "NonAuthoritativeInformation"},
        {204, "NoContent"},
        {205, "ResetContent"},
        {206, "PartialContent"},

        {300, "MultipleChoices"},
        {301, "MovedPermanently"},
        {302, "MovedTemporarily"},
        {304, "NotModified"},
        {305, "UseProxy"},
        {307, "TemporaryRedirect"},

        {400, "BadRequest"},
        {401, "Unauthorized"},
        {402, "PaymentRequired"},
        {403, "Forbidden"},
        {404, "NotFound"},
        {405, "MethodNotAllowed"},
        {406, "NotAcceptable"},
        {407, "ProxyAuthenticationRequired"},
        {408, "RequestTimeOut"},
        {409, "Conflict"},
        {410, "Gone"},
        {411, "LengthRequired"},
        {412, "PreconditionFailed"},
        {413, "RequestEntityTooLarge"},
        {414, "RequestURITooLarge"},
        {415, "UnsupportedMediaType"},
        {416, "RequestedRangeNotSatisfiable"},
        {417, "ExpectationFailed"},
        {418, "I'm a teapot"},

        {500, "InternalServerError"},
        {501, "NotImplemented"},
        {502, "BadGateway"},
        {503, "ServiceUnavailable"},
        {504, "GatewayTimeout"},
        {505, "HTTPVersionNotSupported"}};
};

#endif /* !HTTPRESPONSE_HPP_ */
