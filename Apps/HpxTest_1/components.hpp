#pragma once

namespace app {
	namespace components {
		class MyMachine : public 
			hpx::components::locking_hook<
				hpx::components::component_base<MyMachine>> {
			
		public:
			using argument_type = boost::int64_t;

			MyMachine() {
				hpx::cout << "[COMPONENT] ctor called" << hpx::endl;
			}
			~MyMachine() {
				hpx::cout << "[COMPONENT] dtor called" << hpx::endl;
			}
			argument_type get_number() const {
				return num_;
			}
			void set_number(argument_type v) {
				num_ = v;
			}
			HPX_DEFINE_COMPONENT_ACTION(MyMachine, get_number);
			HPX_DEFINE_COMPONENT_ACTION(MyMachine, set_number);
		private:
			argument_type num_ = 42;
		};
	}
}

HPX_REGISTER_ACTION_DECLARATION(app::components::MyMachine::get_number_action, machine_get_number_action);
HPX_REGISTER_ACTION_DECLARATION(app::components::MyMachine::set_number_action, machine_set_number_action);