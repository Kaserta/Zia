/**
 * @file IHooks.hpp
 * Describe the Interface IHooks
 * @author Chétafi Alexandre
 */

#ifndef API_IHOOKS_HPP
#define API_IHOOKS_HPP

#include <memory>
#include <map>

struct Request;
struct Response;
class HTTPStatus;
struct clientDialog;

/**
 * The IHooks Interface class provide hooking system to make
 * synchronous call to the subscribed method when the system undergo a change of its state
 */

class IHooks : public std::enable_shared_from_this<IHooks>
{
public:
	/// All methods signatures
	using requestMethod = std::function<void(Request &, HTTPStatus &)>;
	using responseMethod = std::function<void(Response &)>;
	using requestResponseMethod = std::function<void(Request &, std::string &, HTTPStatus &)>;
	using networkMethod = std::function<void(clientDialog &)>;
	using confMethod = std::function<void(const std::map<std::string, std::string> &)>;
	using logRequestMethod = std::function<void(Request const &)>;
	using logResponseMethod = std::function<void(Response const &)>;
	using noMethod = std::function<void(void)>;

public:

	/**
	 * A hook to initiate a dialog as soon as a client is connected
	 */

	virtual void hook_pre_network_client(networkMethod) noexcept = 0; // dès la création

	/**
	 * A hook to continue a dialog after being ask by hook_pre_network_client (flag AGAIN) (until the flag is at OK or FAILURE)
	 */

	virtual void hook_post_network_client(networkMethod) noexcept = 0; // dialogue

public:

	/**
	 * A hook to capture the request before parsing
	 */

	virtual void hook_pre_parse(requestMethod) noexcept = 0;

	/**
	 * A hook to capture the request after parsing
	 */

	virtual void hook_post_parse(requestMethod) noexcept = 0;

	/**
	 * A hook to call a method before everyone else
	 */

	virtual void hook_quick_run(requestResponseMethod) noexcept = 0;

	/**
	 * A hook to build a response on a request
	 */

	virtual void hook_run(requestResponseMethod) noexcept = 0;

	/**
	 * A hook to capture a request and response after treatment
	 */

	virtual void hook_post_run(requestResponseMethod) noexcept = 0;

	/**
	 * A hook to capture the response before being sent away
	 */

	virtual void hook_pre_send(responseMethod) noexcept = 0;

public:
	//virtual void hook_authentication_access(requestMethod &&) noexcept = 0;
	//virtual void hook_authentication_user_check(requestMethod &&) noexcept = 0; // check base authentication
	//virtual void hook_authentication(requestMethod &&) noexcept = 0; // authorization phase

public:
	/**
	 * A hook that will call a specific method before configuration
	 */

	virtual void hook_module_pre_config(noMethod) noexcept = 0;

	/**
	 * A hook that will be called to configure the module with the configuration
	 */

	virtual void hook_module_config(confMethod) noexcept = 0;

	/**
	 * A hook that will be called after the configuration
	 */

	virtual void hook_module_post_config(noMethod) noexcept = 0;

public:
	/**
	 * A hook that will be called before the logging of the request
	 */

	virtual void hook_pre_log_request(logRequestMethod) noexcept = 0;

	/**
	 * A hook that will be called after the logging of the request
	 */

	virtual void hook_post_log_request(logRequestMethod) noexcept = 0;

	/**
	 * A hook that will be called before the logging of the answer
	 */

	virtual void hook_pre_log_response(logResponseMethod) noexcept = 0;

	/**
	 * A hook that will be called after the logging of the answer
	 */

	virtual void hook_post_log_response(logResponseMethod) noexcept = 0;
};

#endif //API_IHOOKS_HPP