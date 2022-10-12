#pragma once

#ifndef __il2cpp
#define __il2cpp

namespace il2cpp
{
	enum class valuetype_e
	{
		ADDRESS,
		SIGNATURE,
		TYPESIGNATURE
	};
	struct output_s
	{
		std::string string;
		uintptr_t value;
	};
	struct input_s
	{
		valuetype_e value_type;
		std::string file_path;
		std::string search_keyword;
	};
	struct il2cpp_value
	{
		input_s input_value;
		output_s output_value;
		bool success;
	};

	bool il_FindValue2(il2cpp_value *val);
	void il_FindValue(il2cpp_value* val);
	uintptr_t il_ParseAddress(std::fstream& f);
	std::string il_ParseName(std::fstream& f);

}

#endif