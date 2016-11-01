
#pragma once
#include <iostream>
#include <rapidxml.hpp>
#include <rapidxml_utils.hpp>
#include <rapidxml_print.hpp>
#include <rapidxml_iterators.hpp>
#include <vector>

using namespace rapidxml;

void xml_write_test()
{
	xml_document<> doc;
	xml_node<>* root = doc.allocate_node(rapidxml::node_pi, doc.allocate_string("xml version='1.0' encoding='utf-8'"));
	doc.append_node(root);

	xml_node<>* node = doc.allocate_node(rapidxml::node_element, "config", "information");
	doc.append_node(node);
	{
		xml_node<>* color = doc.allocate_node(rapidxml::node_element, "color", nullptr);
		color->append_node(doc.allocate_node(rapidxml::node_element, "red", "0.1"));
		color->append_node(doc.allocate_node(rapidxml::node_element, "green", "0.5"));
		color->append_node(doc.allocate_node(rapidxml::node_element, "blue", "0.3"));
		color->append_node(doc.allocate_node(rapidxml::node_element, "alpha", "1.0"));
		node->append_node(color);

		xml_node<>* size = doc.allocate_node(rapidxml::node_element, "size", nullptr);
		size->append_node(doc.allocate_node(rapidxml::node_element, "x", "640"));
		size->append_node(doc.allocate_node(rapidxml::node_element, "y", "480"));
		node->append_node(size);

		xml_node<>* mode = doc.allocate_node(rapidxml::node_element, "mode", "screen mode");
		mode->append_attribute(doc.allocate_attribute("fullscreen", "false"));
		mode->append_attribute(doc.allocate_attribute("resizeble", "false"));
		node->append_node(mode);
	}

#if 0
	std::string text;
	rapidxml::print(std::back_inserter(text), doc, 0);

	std::cout << text << std::endl;
#endif

	std::ofstream out("config.xml");
	out << doc;
}

void xml_read_test()
{
	rapidxml::file<> fdoc("config.xml");
	xml_document<> doc;
	doc.parse<0>(fdoc.data());

	xml_node<>* config = doc.first_node();
	xml_node<>* color = config->first_node();
	xml_node<>* red = color->first_node();
	xml_node<>* size = config->first_node("size");
	size->append_node(doc.allocate_node(rapidxml::node_element, "w", "0"));
	size->append_node(doc.allocate_node(rapidxml::node_element, "h", "0"));

#if 1
	std::string text;
	rapidxml::print(std::back_inserter(text), doc, 0);

	std::cout << text << std::endl;
#endif

	std::ofstream out("config.xml");
	out << doc;
}

struct SubTexture
{
	char* name;
	char* x;
	char* y;
	char* width;
	char* height;
};

std::vector<SubTexture*> TexAltas;

void xml_read_spritesheet()
{
	rapidxml::file<> fdoc("blue_spritesheet.xml");
	xml_document<> doc;
	doc.parse<0>(fdoc.data());

	xml_node<>* textureAltas = doc.first_node();
	xml_node<>* leter = textureAltas->first_node();

	xml_node<>* leter_ = leter;
	while (leter_)
	{
#if 0
		std::cout << leter_->first_attribute("name")->value() << std::endl;
		std::cout << leter_->first_attribute("x")->value() << std::endl;
		std::cout << leter_->first_attribute("y")->value() << std::endl;
		std::cout << leter_->first_attribute("width")->value() << std::endl;
		std::cout << leter_->first_attribute("height")->value() << std::endl;
#endif

		SubTexture* subT = new SubTexture();
		subT->name = leter_->first_attribute("name")->value();
		subT->x = leter_->first_attribute("x")->value();
		subT->y = leter_->first_attribute("y")->value();
		subT->width = leter_->first_attribute("width")->value();
		subT->height = leter_->first_attribute("height")->value();
		TexAltas.push_back(subT);

		leter_ = leter_->next_sibling();
	}
}
