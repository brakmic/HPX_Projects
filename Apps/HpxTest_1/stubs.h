#pragma once
namespace app {
	namespace stubs {
		struct mycomp :
			hpx::components::stub_base<components::MyMachine> {

			using argument_type = components::MyMachine::argument_type;

			static void set_number_async(hpx::naming::id_type const& gid, argument_type v) {
				hpx::cout << "[STUB] set_number_async, value: " << v << hpx::endl;
				using action_type = components::MyMachine::set_number_action;
				hpx::async<action_type>(gid, v);
			}

			static void set_number_sync(hpx::naming::id_type const& gid, argument_type v) {
				hpx::cout << "[STUB] set_number_sync, value: " << v << hpx::endl;
				using action_type = components::MyMachine::set_number_action;
				hpx::async<action_type>(gid, v).get();
			}

			static hpx::lcos::future<argument_type> get_number_async(hpx::naming::id_type const& gid) {
				hpx::cout << "[STUB] get_number_async" << hpx::endl;
				using action_type = components::MyMachine::get_number_action;
				return hpx::async<action_type>(gid);
			}

			static argument_type get_number_sync(hpx::naming::id_type const& gid) {
				hpx::cout << "[STUB] get_number_sync" << hpx::endl;
				return get_number_async(gid).get();
			}
		};
	}
}