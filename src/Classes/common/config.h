#pragma once

#include <string>
#include <map>

#define _CONFIG(key, dst, type) do{\
	int ret = config::get_as_##type( \
		(key), dst); \
	} while(0)
#define _CONFIG_STR(key, dst) _CONFIG(key,dst, string)
#define _CONFIG_INT(key, dst) _CONFIG(key,dst, int)
#define _CONFIG_FLT(key, dst) _CONFIG(key,dst, float)

namespace config{

	int from_file(
		const std::string &path);
	int from_string(
		const std::string &str);

	void set(
		const std::string &key,
		const std::string &value);
	void set(
		const std::string &key,
		int value);

	int get(
		const std::string &key,
		std::string &value);
	int get_as_string(
		const std::string &key,
		std::string &value);
	int get_as_int(
		const std::string &key,
		int &value);
	int get_as_float(
		const std::string &key,
		float &value);

	void print();
};