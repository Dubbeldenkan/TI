#include "ListNode.h"

namespace TIParserNS
{
	ListNode::ListNode(std::string data)
		: _data(data)
	{}

	bool ListNode::GetChild(ListNode** child)
	{
		*child = _child;
		return (child == NULL);
	}

	bool ListNode::GetNext(ListNode** next)
	{
		bool nextIsNull = (_next == NULL);
		*next = _next;
		delete this;
		return nextIsNull;
	}

	std::string ListNode::GetData()
	{
		return _data;
	}

	void ListNode::SetNext(ListNode* next)
	{
		_next = next;
	}

	void ListNode::SetChild(ListNode* child)
	{
		_child = child;
	}
}