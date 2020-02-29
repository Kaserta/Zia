/*
** EPITECH PROJECT, 2020
** Exporter
** File description:
** Exporter for windows and linux
*/

#ifndef API_EXPORT_HPP
#define API_EXPORT_HPP

#if defined(_WIN32) || defined(_WIN64) || defined(__CYGWIN__)
# define IMPORT __declspec(dllimport)
# define EXPORT __declspec(dllexport)
#elif defined(__GNUC__)
# define IMPORT __attribute__ ((dllimport))
# define EXPORT __attribute__ ((dllimport))
#elif defined(__GNUC__ <= 4)
# define IMPORT __attribute__ ((visibility ("hidden")))
# define EXPORT __attribute__ ((visibility ("default")))
#endif

#endif //API_EXPORT_HPP