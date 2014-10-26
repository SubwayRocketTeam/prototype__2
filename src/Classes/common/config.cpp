#include "config.h"

#include "parser.h"

using namespace std;

namespace config{

	map<string,string> configs;

	int from_file(
		const string &path){

		FILE *fp = fopen(path.c_str(), "r");
		if(fp == nullptr)
			return false;

		string doc;
		while(true){
			if(feof(fp))
				break;

			char buf[256];
			fgets(buf, 256, fp);

			doc.append(buf);
		}
		fclose(fp);

		return parser::parse(
			doc, configs);
	}
	int from_string(
		const string &str){

		return parser::parse(
			str, configs);
	}

	void set(
		const string &key,
		const string &value){

		configs[key] = value;
	}
	void set(
		const string &key,
		int value){

		char buffer[32];
		sprintf(buffer, "%d", value);

		set(key, buffer);
	}
	int get(
		const string &key,
		string &value){

		return get_as_string(
			key, value);
	}
	int get_as_string(
		const string &key,
		string &value){

		auto it = configs.find(key);
		if(it == configs.end())
			return false;

		value = it->second;

		return true;
	}
	int get_as_int(
		const string &key,
		int &value){

		int ret;
		string s_value;
		ret = get_as_string(key, s_value);

		sscanf(s_value.c_str(), "%d", &value);

		return true;
	}
	int get_as_float(
		const string &key,
		float &value){

		int ret;
		string s_value;
		ret = get_as_string(key, s_value);

		sscanf(s_value.c_str(), "%f", &value);

		return true;
	}


	void print(){
		for(auto c : configs){
			printf("%s %s\n",
				c.first.c_str(),
				c.second.c_str());
		}
	}
};