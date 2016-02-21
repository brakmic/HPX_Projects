#include <hpx/include/iostreams.hpp>
#include "SmallServer.h"

namespace mylib {
	namespace components {
		void server::print_greeting(const std::string& name) {
			auto id = this->get_id();
			hpx::cout<< "[ID " << id << "] " << "Hello " << name << hpx::endl;
		}
	}
}