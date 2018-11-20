#include "stdafx.h"
#include "parseTool.h"
#include <sstream>
#include<fstream>
#include <google/protobuf/io/zero_copy_stream_impl.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/message_lite.h>
#include <google/protobuf/wire_format_lite.h>
#include "AbstractMessage.h"
parseTool::parseTool()
{
}


parseTool::~parseTool()
{
}

bool parseTool::readIo(std::string & str)
{
	std::stringstream stream(str);
	return readIo(stream);
}

bool parseTool::readIo(std::istream & is)
{
	AbstractMessagePtr msg = std::make_shared<AbstractMessage>();
	msg->setName("f20");
	google::protobuf::io::IstreamInputStream inputStream(&is);
	google::protobuf::io::CodedInputStream input(&inputStream);
	

	msg->paresFromStream(&input);
	
	return false;
}

bool parseTool::readFile(std::string  fileName)
{
	std::ifstream f(fileName, std::ios_base::in | std::ios_base::binary);
	if (f.is_open())
	{
		return readIo(f);
	}
	return false;
}
