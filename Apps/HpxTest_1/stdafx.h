// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define _SCL_SECURE_NO_WARNINGS
#define _CRT_NON_CONFORMING_SWPRINTFS
#define HPX_COMPONENT_EXPORTS
#include "targetver.h"

#include <gsl.h>
#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <string>


// TODO: reference additional headers your program requires here
#include <iostream>
#include <string>
#include <hpx/hpx_init.hpp>
#include <hpx/include/actions.hpp>
#include <hpx/include/lcos.hpp>
#include <hpx/include/components.hpp>
#include <hpx/include/serialization.hpp>

#include <boost/any.hpp>
#include <hpx/include/iostreams.hpp>

#include "functions.hpp"
#include "components.hpp"
#include "stubs.h"
#include "clients.h"