/*
** EPITECH PROJECT, 2020
** IModule
** File description:
** Implementation of the interface compliant with the api
*/

#ifndef IMODULE_HPP_
#define IMODULE_HPP_

#include <iostream>
class IHooks;

#include <functional>
#include <string>
#include "IHooks.hpp"
#include "Exporter.hpp"

/**
 * This is the interface for all module. The server will managed each pointer to the primary interface of the
 * library with this interface.
 */

class IModule : public std::enable_shared_from_this<IModule>
{
public:
	/**
	 * Return the name of the module
	 * @return A string containing the name
	 */

	virtual const std::string	&getName() const noexcept = 0;

	/**
	 * Return the version of the module
	 * @return A string containing the version
	 */
	virtual const std::string	&getVersion() const noexcept = 0;

	/**
	 * Hook all method in the system
	 * @param hooks The pointer to the hooking system
	 */

	virtual void SetHooks(std::shared_ptr<IHooks> &hooks) noexcept = 0;
};


/**
 * This is the primary access fot the server to get a pointer to the module.
 * @return Return a pointer to the module
 */

extern "C" EXPORT IModule *getModule();

#endif /* !IMODULE_HPP_ */
