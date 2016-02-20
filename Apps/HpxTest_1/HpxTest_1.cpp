// HpxTest_1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "register.h"

int hpx_main(int argc, char* argv[])
{
	global_print_number printNo;
	global_get_number getNo;

	auto id = hpx::find_here();
	//Applying an Action Asynchronously with Synchronization
	//http://stellar.cct.lsu.edu/files/hpx-0.9.11/html/hpx/manual/applying_actions/action_invocation/async.html
	hpx::apply(printNo, id, 2.0);
	hpx::future<int> f2 = hpx::async(getNo, id);
	
	auto value1 = f2.get();
	hpx::cout << "Async function returned: " << value1 << hpx::endl;
	//Applying an Action Synchronously
	//http://stellar.cct.lsu.edu/files/hpx-0.9.11/html/hpx/manual/applying_actions/action_invocation/sync.html
	printNo(id, 5.0);

	//Applying an Action with a Continuation and with Synchronization
	global_increase_ten incTen;
	global_increase_one incOne;
	hpx::future<int> ret2 = hpx::async_continue(incTen, hpx::make_continuation(incOne), id, 31);
	auto contValue = ret2.get();
	hpx::cout << "Value from continuation: " << contValue << hpx::endl;

	//Action Error Handling
	//http://stellar.cct.lsu.edu/files/hpx-0.9.11/html/hpx/manual/applying_actions/action_error_handling.html
	global_divide_number divNo;
	try
	{
		divNo(id, -1.0);
	}
	catch (hpx::exception const& e)
	{
		hpx::cout << "Exception thrown: " << e.what() << hpx::endl;
	}

	//Defining Components
	//http://stellar.cct.lsu.edu/files/hpx-0.9.11/html/hpx/manual/components/components_server.html
	using my_machine_type = app::components::MyMachine;
	using argument_type = my_machine_type::argument_type;
	std::vector<hpx::id_type> localities = hpx::find_all_localities();
	
	app::clients::myclient client1(hpx::components::new_<my_machine_type>(localities.back()));
	//remember component's id
	auto cid = client1.get_id();
	argument_type aNumber = client1.get_number_sync(cid);
	hpx::cout << "Original value from component: " << aNumber << hpx::endl;
	client1.set_number_sync(125);
	aNumber = client1.get_number_sync(cid);
	hpx::cout << "Component changed value to: " << aNumber << hpx::endl;
	
	//shutdown HPX
	return hpx::finalize();
}

int main(int argc, char* argv[])
{
	// Configure application-specific options.
	boost::program_options::options_description desc_commandline(
		"usage: " HPX_APPLICATION_STRING " [options]");

	return hpx::init(desc_commandline, argc, argv); // Initialize and run HPX.
}

