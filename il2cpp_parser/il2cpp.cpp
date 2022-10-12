
#include "pch.h"


struct saved_data
{
	uintptr_t address;
	std::string name;
	std::string typeSignature;
};
uintptr_t il2cpp::il_ParseAddress(std::fstream& f)
{
	std::string addr_str;
	
	addr_str = fs::F_ReadUntil(f, ',');

	if (addr_str.find("Address") == std::string::npos || addr_str.find(": ") == std::string::npos) {
		printf("failure to find the string 'Address: ', found instead '%s'\nline: [%i, %i]\n", addr_str.c_str(), fs::file.lines_read, fs::file.current_column);
		fs::F_CloseFile(f);
		return NULL;
	}

	try {
		return std::stoull(addr_str.substr(addr_str.find(':') + 2));
	}
	catch (std::exception& ex) {
		printf("il_ParseAddress() failed with: '%s'\n", ex.what());
		return NULL;
	}

	return NULL;
}
std::string il2cpp::il_ParseName(std::fstream& f)
{
	std::string substr = fs::F_ReadUntil(f, ',');

	substr = substr.substr(substr.find(": ") + 3);
	substr = substr.substr(0, substr.find('"'));

	return substr;
	

}
void il2cpp::il_FindValue(il2cpp_value* val)
{
	val->success = il_FindValue2(val);

}
bool il2cpp::il_FindValue2(il2cpp_value* val)
{

	std::fstream f;
	fs::F_Reset();

	printf("attempting to open file '%s'\n", val->input_value.file_path.c_str());

	if (!fs::F_DirectoryExists(val->input_value.file_path)) {
		printf_s("file '%s' does not exist\n", val->input_value.file_path.c_str());
		fs::F_CloseFile(f);
		return false;
	}

	if (!fs::F_OpenFile(f, val->input_value.file_path, fs::fileopen::FILE_IN)) {
		printf_s("failure to open file '%s' with error: %s\n", val->input_value.file_path.c_str(), fs::_GetLastError().c_str());
		fs::F_CloseFile(f);
		return false;
	}

	if (val->input_value.search_keyword.size() < 1) {
		printf_s("search string size is empty\n");
		fs::F_CloseFile(f);
		return false;
	}

	fs::F_ReadUntil(f, '[');
	std::string addr_str;

	while(f.good() && !f.eof()){

		fs::F_ReadUntil(f, '{');

		uintptr_t addr = il_ParseAddress(f);
		std::string name = il_ParseName(f);

		if (!addr)
			printf("failure to read address\n");
		else
			printf("address: %u\n", addr);

		printf("name: %s\n", name.c_str());

		if (!name.compare(val->input_value.search_keyword)) {
			val->output_value.value = addr;
			val->output_value.string = name;
			return true;

		}

	}
	fs::F_CloseFile(f);

	return true;

}