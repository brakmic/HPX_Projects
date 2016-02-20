#include "stdafx.h"

namespace app {
	namespace functions {
		void print_number(double v)
		{
			hpx::cout << "value is: " << v << hpx::endl;
		}
		int get_number() {
			return 42;
		}

		int increase_ten(int v) {
			return v + 10;
		}

		int increase_one(int v) {
			return v + 1;
		}

		double divide_number(double v) {
			if (v == 0) {
				HPX_THROW_EXCEPTION(hpx::bad_parameter, 
					"divide_number", "Given number is zero");
			}
			return (v / 2);
		}

	}
}