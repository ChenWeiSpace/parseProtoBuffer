// parseProtoBuffer.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "parseTool.h"


int main()
{
	parseToolPtr t = std::make_shared<parseTool>();
	t->readFile("C:\\Users\\chenwei\\source\\repos\\ConsoleApplication2\\ConsoleApplication2\\123.tt");
    return 0;
}

