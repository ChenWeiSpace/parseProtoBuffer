// parseProtoBuffer.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "parseTool.h"
#include <fstream>

int main()
{
	parseToolPtr t = std::make_shared<parseTool>();
	//t->readFile("C:\\Users\\chenwei\\Desktop\\temp\\zip\\f.txt");
// 	std::fstream fs("C:\\Users\\Administrator\\Desktop\\asd\\f2.txt", std::ios_base::in | std::ios_base::binary);
// 	std::fstream os("C:\\Users\\Administrator\\Desktop\\asd\\f2.dec", std::ios_base::out | std::ios_base::binary | std::ios_base::trunc);
// 	if (fs.is_open() && os.is_open())
// 	{
// 		t->paserUnknow(fs, os);
// 	}
	t->readGoogleTitle();
	//D:\\vsProject\\protoTest\\protoTest\\st1.out
    return 0;
}

