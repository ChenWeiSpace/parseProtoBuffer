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
				::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_SINT32>(
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
			if (::google::protobuf::internal::WireFormatLite::ReadString(
				input, &str))
			{
				continue;
				//¶Á³ö×Ö·û´®
				auto tup =exitFieldTar(str);
				if (std::get<2>(tup))
				{
					//message
					size_t length = str.length();
					std::vector<int> intArray;
					AbstractMessagePtr msg = std::make_shared<AbstractMessage>();
					if (readAsMessage(str, msg))
					{
						msg->wireType = (AbstractField::FieldWireType)war;
						msg->gt = AbstractField::Is_Message;
						msg->mem = str;
						this->fileds[filedNumber].push_back(msg);
						int of = msg->blockSize = input->CurrentPosition() - currentPos;
						continue;
					}
				}
				IntArray  valArray;
				FLoatArray fArray;
				DoubleArray dArray;
				if (readAsIntArray(str,valArray, str.size()))
				{
					AbstractFieldPtr field = std::make_shared<AbstractField>();
					field->wireType = (AbstractField::FieldWireType)war;
					field->_valArray.swap(valArray);
					field->gt = AbstractField::Is_IntArray;
					this->fileds[filedNumber].push_back(field);
					field->blockSize = str.size();
				}
				else if (readAsDoubleArray(str, dArray, str.size()))
				{
					AbstractFieldPtr field = std::make_shared<AbstractField>();
					field->wireType = (AbstractField::FieldWireType)war;
					field->_dArray.swap(dArray);
					field->gt = AbstractField::Is_FloatArray;
					this->fileds[filedNumber].push_back(field);
					field->blockSize = str.size();
				}
				else if (readAsFloatArray(str, fArray, str.size()))
				{
					AbstractFieldPtr field = std::make_shared<AbstractField>();
					field->wireType = (AbstractField::FieldWireType)war;
					field->_fArray.swap(fArray);
					field->gt = AbstractField::Is_DoubleArray;
					this->fileds[filedNumber].push_back(field);
					field->blockSize = str.size();
				}
				else
				{
					AbstractFieldPtr field = std::make_shared<AbstractField>();
					field->wireType = (AbstractField::FieldWireType)war;
					google::protobuf::internal::WireFormatLite::VerifyUtf8String(
						str.data(),
						str.length(),
						::google::protobuf::internal::WireFormatLite::PARSE,
						"test");

					field->mem = str;
					field->gt = AbstractField::Is_String;
					this->fileds[filedNumber].push_back(field);
					field->blockSize = str.size();
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

bool AbstractMessage::readAsIntArray(std::string mem, IntArray & valArray, int length)
{
	google::protobuf::io::ArrayInputStream arrauStream(mem.data(), mem.size());
	google::protobuf::io::CodedInputStream codeInput(&arrauStream);
	return readAsIntArray(&codeInput, valArray, length);
}

bool AbstractMessage::readAsFloatArray(std::string mem, FLoatArray & valArray, int length)
{
	if (!mem.size()%sizeof(float))
	{
		valArray.resize(mem.size() / sizeof(float));
		memcpy(valArray.data(), mem.data(), mem.size());
		return true;
	}
	return false;
}

bool AbstractMessage::readAsDoubleArray(std::string mem, DoubleArray & valArray, int length)
{
	if (!mem.size() % sizeof(double))
	{
		valArray.resize(mem.size()/ sizeof(double));
		memcpy(valArray.data(), mem.data(), mem.size());
		return true;
	}
	return false;
}

bool AbstractMessage::readAsMessage(std::string mem, std::shared_ptr<AbstractMessage > & mesPtr)
{
	std::stringstream strStream(mem);
	google::protobuf::io::IstreamInputStream inputStream(&strStream);
	google::protobuf::io::CodedInputStream input(&inputStream);

	
	return mesPtr->paresFromStream(&input);
}

std::tuple<int, int, bool> AbstractMessage::exitFieldTar(std::string mem)
{
	google::protobuf::io::ArrayInputStream arrauStream(mem.data(), mem.size());
	google::protobuf::io::CodedInputStream codeInput(&arrauStream);
	google::protobuf::uint32 tar = codeInput.ReadTag();
	if ( tar == 0 )
	{
		return std::make_tuple(0, 0, false);
	}
	google::protobuf::internal::WireFormatLite::WireType wireT = google::protobuf::internal::WireFormatLite::GetTagWireType(tar);
	if (wireT>=google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT && wireT<=google::protobuf::internal::WireFormatLite::WIRETYPE_FIXED32)
	{
		int fieldNum = google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tar);
		return std::make_tuple(fieldNum, wireT, true);
	}

	return  std::make_tuple(0, 0, false);
}

