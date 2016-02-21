// HpxTest_1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "register.h"

void function_invocation_demo(hpx::naming::id_type id)
{
	//Applying an Action Asynchronously with Synchronization
	//http://stellar.cct.lsu.edu/files/hpx-0.9.11/html/hpx/manual/applying_actions/action_invocation/async.html

	global_print_number printNo;
	global_get_number getNo;

	hpx::apply(printNo, id, 2.0);
	hpx::future<int> f2 = hpx::async(getNo, id);

	auto value1 = f2.get();
	hpx::cout << "Async function returned: " << value1 << hpx::endl;
	//Applying an Action Synchronously
	//http://stellar.cct.lsu.edu/files/hpx-0.9.11/html/hpx/manual/applying_actions/action_invocation/sync.html
	printNo(id, 5.0);
}

void continuation_demo(hpx::naming::id_type id)
{
	//Applying an Action with a Continuation and with Synchronization
	//http://stellar.cct.lsu.edu/files/hpx-0.9.11/html/hpx/manual/applying_actions/action_invocation/apply_continue.html
	global_increase_ten incTen;
	global_increase_one incOne;
	hpx::future<int> ret2 = hpx::async_continue(incTen, hpx::make_continuation(incOne), id, 31);
	auto contValue = ret2.get();
	hpx::cout << "Value from continuation: " << contValue << hpx::endl;

}

void error_handling_demo(hpx::naming::id_type id)
{
	//Action Error Handling
	//http://stellar.cct.lsu.edu/files/hpx-0.9.11/html/hpx/manual/applying_actions/action_error_handling.html
	global_divide_number divNo;
	try
	{
		divNo(id, 0);
		//divNo(id, -1.0);
	}
	catch (hpx::exception const& e)
	{
		hpx::cout << "Exception thrown: " << e.what() << hpx::endl;
	}
}

void component_demo()
{
	//Defining Components
	//http://stellar.cct.lsu.edu/files/hpx-0.9.11/html/hpx/manual/components/components_server.html
	//get component's and default argument's types
	using my_machine_type = app::components::MyMachine;
	using argument_type = my_machine_type::argument_type;
	//find all localities 
	std::vector<hpx::id_type> localities = hpx::find_all_localities();
	//instantiate a client accessing our component
	app::clients::myclient client1(hpx::components::new_<my_machine_type>(localities.back()));
	//remember component's id
	auto cid = client1.get_id();
	//access the component's get_number-method synchronously (look into stub-declaration for more info)
	argument_type aNumber = client1.get_number_sync(cid);
	hpx::cout << "Original value from component: " << aNumber << hpx::endl;
	//access component's set_number synchronously
	client1.set_number_sync(125);
	//access component's get_number synchronously
	aNumber = client1.get_number_sync(cid);
	hpx::cout << "Component changed value to: " << aNumber << hpx::endl;
}

void dll_component_demo(std::size_t num_components, const std::string& name)
{
	//Loading components
	//http://stellar.cct.lsu.edu/files/hpx-0.9.11/html/hpx/manual/init/configuration/loading_components.html
	std::vector<hpx::id_type> localities = hpx::find_all_localities();
	hpx::components::component_type svc_type = 
		mylib::components::server::get_component_type();
	std::vector<hpx::id_type> components =
		hpx::new_<mylib::components::server[]>(
			hpx::default_layout(localities), num_components).get();

	mylib::components::server::print_greeting_action say_hello;
	for (auto c : components) {
		say_hello(c, name);
	}
}

int hpx_main(int argc, char* argv[])
{
	//get local id
	auto id = hpx::find_here();
	auto num_components = 10;
	const std::string name = "Harris";

	function_invocation_demo(id);

	continuation_demo(id);
	
	error_handling_demo(id);
	
	component_demo();

	dll_component_demo(num_components, name);
	
	//shutdown HPX
	return hpx::finalize();
}

int main(int argc, char* argv[])
{
	//setup any app-specific options
	boost::program_options::options_description desc_commandline(
		"usage: " HPX_APPLICATION_STRING " [options]");
	//init HPX and start the app
	return hpx::init(desc_commandline, argc, argv);
}

