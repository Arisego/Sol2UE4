// Fill out your copyright notice in the Description page of Project Settings.

#include "SolBpLib.h"
#include "Sol2Ue.h"


#define SOL_ALL_SAFETIES_ON 1
#include "sol.hpp"


void USolBpLib::TestSol()
{
	UE_LOG(LogLua,Log, TEXT("=== basic ==="));

	// create an empty lua state
	sol::state lua;

	// by default, libraries are not opened
	// you can open libraries by using open_libraries
	// the libraries reside in the sol::lib enum class
	lua.open_libraries(sol::lib::base);
	// you can open all libraries by passing no arguments
	//lua.open_libraries();

	lua.set_function("print", [](const char* y) { UE_LOG(LogLua, Log, TEXT("%s"), UTF8_TO_TCHAR(y)); });

	// call lua code directly
	lua.script("print('hello world')");

	// call lua code, and check to make sure it has loaded and run properly:
	auto handler = &sol::script_default_on_error;
	lua.script("print('hello again, world')", handler);

	// Use a custom error handler if you need it
	// This gets called when the result is bad
	auto simple_handler = [](lua_State*, sol::protected_function_result result) {
		// You can just pass it through to let the call-site handle it
		return result;
	};
	// the above lambda is identical to sol::simple_on_error, but it's
	// shown here to show you can write whatever you like

	// 
	{
		auto result = lua.script("print('hello hello again, world') \n return 24", simple_handler);
		if (result.valid()) {
			UE_LOG(LogLua, Log, TEXT("the third script worked, and a double-hello statement should appear above this one!"));
			int value = result;
			ensure(value == 24);
		}
		else {
			UE_LOG(LogLua, Log, TEXT("the third script failed, check the result type for more information!"));
		}
	}

	/**	<This test will log out 0xE24C4A03 */
	{
		auto result = lua.script("does.not.exist", simple_handler);
		if (result.valid()) {
			UE_LOG(LogLua, Log, TEXT("the fourth script worked, which it wasn't supposed to! Panic!"));
			int value = result;
			ensure(value == 24);
		}
		else {
			sol::error err = result;
			UE_LOG(LogLua, Log, TEXT("the fourth script failed, which was intentional! nError: %s"), ANSI_TO_TCHAR(err.what()));
		}
	}
}
