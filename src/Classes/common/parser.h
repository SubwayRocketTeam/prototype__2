#pragma once

#include <string>
#include <vector>
#include <map>

namespace config{
namespace parser{

	int parse(
		const std::string &doc,
		std::map<std::string,std::string> &dst);

};};