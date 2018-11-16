#include "stdafx.h"
#include <google/protobuf/io/zero_copy_stream_impl.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/message_lite.h>
#include <google/protobuf/wire_format_lite.h>
#include <google/protobuf/wire_format_lite_inl.h>

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
			int length = 0;
			if (input->ReadVarintSizeAsInt(&length))
			{

			}
			else
			{
				input->ReadTagNoLastTag();
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
	}

	return false;
}


