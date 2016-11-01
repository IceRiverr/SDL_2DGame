
#pragma once
#include <rapidjson\document.h>
#include <rapidjson\filewritestream.h>
#include <rapidjson\filereadstream.h>
#include <rapidjson\stringbuffer.h>
#include <rapidjson\writer.h>
#include <string>

using namespace rapidjson;
using namespace std;

void json_write_test()
{
	rapidjson::Document doc;
	Document::AllocatorType& allocator = doc.GetAllocator();
	
	Value root(kObjectType);

	Value weapon(kArrayType);
	weapon.PushBack("crossbow", allocator).PushBack("blade", allocator).PushBack("hammer", allocator);
	root.AddMember("Weapon", weapon, allocator);

	Value hero(kObjectType);
	hero.AddMember("name", "Bruce Lee", allocator);
	hero.AddMember("str", "100", allocator);
	hero.AddMember("atk", "200", allocator);
	root.AddMember("Hero", hero, allocator);

	Value skill(kObjectType);
	skill.AddMember("fire", "circle_40", allocator).AddMember("fly", "height_10", allocator).AddMember("hide", "speed_30",allocator);
	root.AddMember("skill", skill, allocator);
	
	FILE* fp = nullptr;
	fopen_s(&fp, "name_list.json", "w");
	char writeBuffer[65536];
	FileWriteStream os(fp, writeBuffer, sizeof(writeBuffer));
	Writer<FileWriteStream> writer(os);
	root.Accept(writer);
	fclose(fp);

	int a = 10;
}

void json_read_test()
{
	char readBuffer[65536];
	FILE* fp = nullptr;
	fopen_s(&fp, "test.json", "rb");
	FileReadStream is(fp, readBuffer, sizeof(readBuffer));

	Document doc;
	doc.Parse<0>(&readBuffer[0]);
	if (doc.HasParseError())
	{
		std::cout << doc.GetParseError() << std::endl;
		return;
	}

	Value& v = doc["dictVersion"];
	if(v.IsInt())
		std::cout << v.GetInt() << std::endl;

	Value& author = doc["author"];
	assert(author.IsString());
	std::cout << author.GetString() << std::endl;

	Value& contents = doc["content"];
	if (contents.IsArray())
	{
		for (rsize_t i = 0; i < contents.Size(); ++i)
		{
			Value& word = contents[i];
			assert(word.IsObject());

			assert(word.HasMember("key"));
			Value& eng = word["key"];
			std::cout << eng.GetString() << std::endl;

			assert(word.HasMember("value"));
			Value& chs = word["value"];
			std::cout << chs.GetString() << std::endl;
		}
	}
}