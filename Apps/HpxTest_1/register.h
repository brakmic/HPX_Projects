#pragma once
// Add factory registration functionality.
HPX_REGISTER_COMPONENT_MODULE();

//******************************ACTIONS***********************************
HPX_PLAIN_ACTION(app::functions::print_number, global_print_number);
HPX_PLAIN_ACTION(app::functions::get_number, global_get_number);
HPX_PLAIN_ACTION(app::functions::increase_ten, global_increase_ten);
HPX_PLAIN_ACTION(app::functions::increase_one, global_increase_one);
HPX_PLAIN_ACTION(app::functions::divide_number, global_divide_number);
//************************************************************************


//******************************COMPONENTS********************************
using mycomp_type = hpx::components::simple_component<app::components::MyMachine>;
using argument_type = mycomp_type::argument_type;
HPX_REGISTER_COMPONENT(mycomp_type, MyMachine);
HPX_REGISTER_ACTION(mycomp_type::wrapped_type::get_number_action, machine_get_number_action);
HPX_REGISTER_ACTION(mycomp_type::wrapped_type::set_number_action, machine_get_number_action);
//************************************************************************