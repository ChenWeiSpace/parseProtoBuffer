#include "stdafx.h"
#include <google/protobuf/io/zero_copy_stream_impl.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/message_lite.h>
#include <google/protobuf/wire_format_lite.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <sstream>
#include "AbstractMessage.h"

AbstractField::AbstractField()
{
	fileNumber = -1;
	val.i64 = 0;	
	blockSize = 0;
}

AbstractField::~AbstractField()
{

}

AbstractMessage::AbstractMessage()
{
}


AbstractMessage::~AbstractMessage()
{
}

bool AbstractMessage::paresFromStream(google::protobuf::io::CodedInputStream* input)
{
	::google::protobuf::uint32 tag;
	for (;;)
	{
		::std::pair<::google::protobuf::uint32, bool> p = input->ReadTagWithCutoffNoLastTag(127u);
		tag = p.first;
		if (!p.second && tag == 0)
		{
			return true;
		}
		
		int currentPos = input->CurrentPosition();

		int filedNumber = google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag);
		google::protobuf::internal::WireFormatLite::WireType war = 
			google::protobuf::internal::WireFormatLite::GetTagWireType(tag);
		if (war == google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT)
		{
			google::protobuf::int32 sz_;
			bool val = google::protobuf::internal::WireFormatLite::ReadPrimitive<
				::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
					input, &sz_);

			if ( val )
			{
				AbstractFieldPtr field = std::make_shared<AbstractField>();
				field->wireType = (AbstractField::FieldWireType)war;
				field->val.i = sz_;
				field->gt = AbstractField::Is_Int;
				this->fileds[filedNumber].push_back(field);
				int of = field->blockSize = input->CurrentPosition() - currentPos;
			}
		}
		else if (war == google::protobuf::internal::WireFormatLite::WIRETYPE_FIXED64)
		{

		}
		else if (war == google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED)
		{
			std::string str;
			google::protobuf::uint32 length;
			if (input->ReadVarint32(&length))
			{
				int arrarPos = input->CurrentPosition();
				//读取数据长度
				//1-按照in数组读取
				std::vector<google::protobuf::uint64> intArray;
				if (readAsIntArray(input,intArray,length))
				{

				}
				else
				{
					int t = input->CurrentPosition();
					//input->Advance(arrarPos-t);
				}
			}
			else
			{
				return false;
			}

			if (::google::protobuf::internal::WireFormatLite::ReadString(
				input, &str))
			{
// 				AbstractFieldPtr field = std::make_shared<AbstractField>();
// 				field->wireType = (AbstractField::FieldWireType)war;
// 				field->gt = AbstractField::Is_String;
// 				field->mem = str;
// 				this->fileds[filedNumber].push_back(field);
// 				int of = field->blockSize = input->CurrentPosition() - currentPos;
				size_t length = str.length();
				std::vector<int> intArray;
				AbstractMessagePtr msg= std::make_shared<AbstractMessage>();
				if (readAsMessage(str,msg))
				{
					msg->wireType = (AbstractField::FieldWireType)war;
					msg->gt = AbstractField::Is_Message;
					msg->mem = str;
					this->fileds[filedNumber].push_back(msg);
					int of = msg->blockSize = input->CurrentPosition() - currentPos;
				}
				
				else if ( length % 4)
				{
					//可能为float数组
				}
			}
		}
		else if ( war == google::protobuf::internal::WireFormatLite::WIRETYPE_START_GROUP)
		{

		}
		else if (war == google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP)
		{

		}
		else if (war == google::protobuf::internal::WireFormatLite::WIRETYPE_FIXED32)
		{
			float st_;
			bool val =  (::google::protobuf::internal::WireFormatLite::ReadPrimitive<
				float, ::google::protobuf::internal::WireFormatLite::TYPE_FLOAT>(
					input, &st_));
			if ( val )
			{
				AbstractFieldPtr field = std::make_shared<AbstractField>();
				field->wireType = (AbstractField::FieldWireType)war;
				field->val.d = st_;
				field->gt = AbstractField::Is_Float;
				this->fileds[filedNumber].push_back(field);
				int of = field->blockSize = input->CurrentPosition() - currentPos;
			}
		}
		else
		{
			return false;
		}
	}

	return false;
}

bool AbstractMessage::readAsIntArray(google::protobuf::io::CodedInputStream* input, IntArray & valArray, int length)
{
	typedef google::protobuf::int32 CType;
	google::protobuf::io::CodedInputStream::Limit limit = input->PushLimit(length);
	while (input->BytesUntilLimit() > 0) {
		CType value;
		if (!google::protobuf::internal::WireFormatLite::ReadPrimitive<CType, google::protobuf::internal::WireFormatLite::TYPE_INT32>(input, &value))
			return false;
		valArray.push_back(value);
	}
	input->PopLimit(limit);

	return true;
}

bool AbstractMessage::readAsMessage(std::string mem, std::shared_ptr<AbstractMessage > & mesPtr)
{
	std::stringstream strStream(mem);
	google::protobuf::io::IstreamInputStream inputStream(&strStream);
	google::protobuf::io::CodedInputStream input(&inputStream);

	
	return mesPtr->paresFromStream(&input);
}

