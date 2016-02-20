#pragma once
//Defining Client Side Representation Classes
//http://stellar.cct.lsu.edu/files/hpx-0.9.11/html/hpx/manual/components/components_client.html

namespace app {
	namespace clients {
		class myclient :
			public hpx::components::client_base<myclient, stubs::mycomp>
		{

			using base_type = hpx::components::client_base<myclient, stubs::mycomp>;
			using argument_type = base_type::argument_type;
			
		public:
			myclient() {
				hpx::cout << "[CLIENT] default ctor called" << hpx::endl;
			}
			myclient(hpx::future<hpx::naming::id_type>&& gid)
				: base_type(std::move(gid)) {
				hpx::cout << "[CLIENT] ctor called" << hpx::endl;
			}
			~myclient() {
				hpx::cout << "[CLIENT] dtor called" << hpx::endl;
			}
			void set_number_async(argument_type v) {
				HPX_ASSERT(this->get_id());
				this->base_type::set_number_async(this->get_id(), v);
			}
			void set_number_sync(argument_type v) {
				HPX_ASSERT(this->get_id());
				this->base_type::set_number_sync(this->get_id(), v);
			}
			hpx::future<argument_type> get_number_async() {
				HPX_ASSERT(this->get_id());
				return this->base_type::get_number_async(this->get_id());
			}
			argument_type get_number() {
				HPX_ASSERT(this->get_id());
				return this->base_type::get_number_sync(this->get_id());
			}
		};
	}
}