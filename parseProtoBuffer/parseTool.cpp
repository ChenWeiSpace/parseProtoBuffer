#include "stdafx.h"
#include "parseTool.h"
#include <sstream>
#include<fstream>
#include <google/protobuf/io/zero_copy_stream_impl.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/message_lite.h>
#include <google/protobuf/wire_format_lite.h>
#include "AbstractMessage.h"
#include <google/protobuf/descriptor.pb.h>
#include "../../../protobuf-master/src/google/protobuf/dynamic_message.h"
#include "../../../protobuf-master/src/google/protobuf/text_format.h"
#include "ft.pb.h"
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

void parseTool::paserUnknow(std::istream & is, std::ostream & os)
{
	google::protobuf::DescriptorPool pool;
	google::protobuf::FileDescriptorProto file;
	file.set_name("empty_message.proto");
	file.add_message_type()->set_name("EmptyMessage");
	if (pool.BuildFile(file))
	{
		std::string codec_type_ = "EmptyMessage";
		const google::protobuf::Descriptor* type = pool.FindMessageTypeByName(codec_type_);
		if (type != NULL) {
			google::protobuf::DynamicMessageFactory dynamic_factory(&pool);
			std::unique_ptr<google::protobuf::Message> message(dynamic_factory.GetPrototype(type)->New());
			google::protobuf::io::IstreamInputStream in(&is);
			if (!message->ParsePartialFromZeroCopyStream(&in))
			{
				os << "Failed to parse input." << std::endl;
			}

			if (!message->IsInitialized()) {
				os << "warning:  Input message is missing required fields:  "
					<< message->InitializationErrorString() << std::endl;
			}
			google::protobuf::io::OstreamOutputStream out(&os);
			if (!google::protobuf::TextFormat::Print(*message, &out)) {
				os << "output: I/O error." << std::endl;
				return;
			}
		}
	}
	os.flush();
}
void paserFile2(std::string & mem)
{
	std::stringstream strem(mem);
	Console::filed2 * t = new Console::filed2;
	t->ParseFromIstream(&strem);
	auto reflection = t->GetReflection();
	const google::protobuf::UnknownFieldSet & unField = reflection->GetUnknownFields(*t);
	for (int i = 0; i < unField.field_count(); ++i)
	{

	}
}

void paserFile7(std::string & mem)
{
	std::stringstream strem(mem);
	Console::filed7 * t = new Console::filed7;
	t->ParseFromIstream(&strem);
	auto reflection = t->GetReflection();
	const google::protobuf::UnknownFieldSet & unField = reflection->GetUnknownFields(*t);
	for (int i = 0; i < unField.field_count(); ++i)
	{

	}
}

void parseTool::readGoogleTitle()
{
	std::string str = "C:\\Users\\chenwei\\Desktop\\temp\\zip\\f";
	std::fstream fs(str+".txt", std::ios_base::in | std::ios_base::binary);
	std::fstream os(str+".dec", std::ios_base::out | std::ios_base::binary | std::ios_base::trunc);
	Console::top * t = new Console::top;
	t->ParseFromIstream(&fs);
	auto reflection = t->GetReflection();
	const google::protobuf::UnknownFieldSet & unField = reflection->GetUnknownFields(*t);
	for ( int i =0;i < unField.field_count();++i)
	{
		const google::protobuf::UnknownField& fie = unField.field(i);
		if ( fie.number_ == 2)
		{
			paserFile2(*(fie.data_.length_delimited_.string_value_));
		}
		else if (fie.number_ == 7)
		{
			paserFile7(*(fie.data_.length_delimited_.string_value_));
		}
	}
	google::protobuf::io::OstreamOutputStream out(&os);
	google::protobuf::TextFormat::Print(*t, &out);
	
	int a = 0;
}
