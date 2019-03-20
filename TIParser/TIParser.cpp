#include "TIParser.h"

namespace TIParserNS
{
	const std::string TIParser::fileType = ".tid";

	TIParser::TIParser()
	{};

	ListNode* TIParser::ReadFile(std::string fileName)
	{
		char tempPath[MAX_PATH];
		GetModuleFileName(NULL, tempPath, MAX_PATH);
		std::string str = std::string(tempPath);
		str.erase(str.rfind('\\'));
		str.erase(str.rfind('\\'));
		std::string folderPath = str + "\\Data\\";

		std::string filePath = folderPath + fileName + fileType;
		std::ifstream file;
		file.open(filePath);

		ListNode* mainNode = new ListNode("");
		ListNode* latestNode = mainNode;

		if (file.is_open())
		{
			AddNewItem(latestNode, &file);
			mainNode->GetNext(&mainNode);
			file.close();
		}
		else
		{
			OutputDebugString(std::string("unable to open file " + filePath).c_str());
		}
		return mainNode;
	}

	void TIParser::AddNewItem(ListNode* currentNode, std::ifstream* file)
	{
		std::string line;
		while (std::getline(*file, line))
		{
			if (line.find("//") == 0 || line.empty())
			{
				//This is a comment or an empty line
			}
			else if (line.find("{") != -1)
			{
				if (line.find("}") == -1)
				{
					ListNode* childNode = new ListNode("");
					AddNewItem(childNode, file);
					childNode->GetNext(&childNode);
					currentNode->SetChild(childNode);
				}
			}
			else if (line.find("}") != -1)
			{
				break;
			}
			else
			{
				line.erase(std::remove(line.begin(), line.end(), '\t'), line.end());
				//line.erase(std::remove(line.begin(), line.end(), ' '), line.end()); //TODO gör så att man tar bort alla mellanslag före och efter texten men inte mellan 
				ListNode* tempNode = new ListNode(line);
				currentNode->SetNext(tempNode);
				currentNode = tempNode;
				OutputDebugString((line + "\n").c_str());
			}
		}
	}
}