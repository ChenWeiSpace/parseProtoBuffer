// parseProtoBuffer.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "parseTool.h"


int main()
{
	parseToolPtr t = std::make_shared<parseTool>();
	t->readFile("D:\\vsProject\\protoTest\\protoTest\\st1.out");
    return 0;
}

