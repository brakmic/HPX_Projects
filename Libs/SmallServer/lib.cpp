#include <hpx/hpx_fwd.hpp>
#include <hpx/include/components.hpp>
#include <hpx/runtime/components/component_factory.hpp>
#include "smallserver.h"

using server_type = hpx::components::component<mylib::components::server>;

// Define boilerplate required once per component module.
HPX_REGISTER_COMPONENT_MODULE();

// Define factory object associated with our component of type 'app::server'.
HPX_REGISTER_COMPONENT(server_type, app_server);

// Define boilerplate code required for each of the component actions. Use the
// same argument as used for HPX_REGISTER_ACTION_DECLARATION above.
HPX_REGISTER_ACTION(server_type::wrapped_type::print_greeting_action, server_print_greeting_action);