#ifndef TI_PARSER_H
#define TI_PARSER_H

#include "ListNode.h"

#include <algorithm>
#include <fstream>
#include <string>
#include <Windows.h>

namespace TIParserNS
{
	class TIParser
	{
	private:
		static const std::string fileType;
	public:
		TIParser();
		~TIParser() {};

		static ListNode* ReadFile(std::string);

	private:
		static void AddNewItem(ListNode*, std::ifstream*);
	};
}

#endif // !TI_PARSER_H