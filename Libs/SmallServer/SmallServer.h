#pragma once

#include <string>
#include <hpx/include/iostreams.hpp>
#include <hpx/include/components.hpp>
#include <hpx/runtime/actions/component_action.hpp>


namespace mylib
{
	namespace components {
		// Define a simple component exposing one action 'print_greeting'
		class HPX_COMPONENT_EXPORT server
			: public hpx::components::component_base<server>
		{
		public:
			server() {
				hpx::cout << "[SERVER] ctor called" << hpx::endl;
			}
			~server() {
				hpx::cout << "[SERVER] dtor called" << hpx::endl;
			}
			void print_greeting(const std::string& name);

			// Component actions need to be declared, this also defines the
			// type 'print_greeting_action' representing the action.
			HPX_DEFINE_COMPONENT_ACTION(server, print_greeting, print_greeting_action);
		};
	}
}

// Declare boilerplate code required for each of the component actions.
HPX_REGISTER_ACTION_DECLARATION(
	mylib::components::server::print_greeting_action,
	server_print_greeting_action);