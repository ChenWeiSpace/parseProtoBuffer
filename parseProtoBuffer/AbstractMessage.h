#ifndef AbstractMessage_h__
#define AbstractMessage_h__
#include <string>
#include <map>
#include <memory>
#include <vector>
#include "protoBufferDeclear.h"

class AbstractField : public std::enable_shared_from_this<AbstractField>
{
public:
	enum FieldWireType {
		WIRETYPE_VARINT = 0,
		WIRETYPE_FIXED64 = 1,
		WIRETYPE_LENGTH_DELIMITED = 2,
		WIRETYPE_START_GROUP = 3,
		WIRETYPE_END_GROUP = 4,
		WIRETYPE_FIXED32 = 5,
	};
	enum guessType
	{
		Invalid,
		Is_Int,
		Is_Float,
		Is_Double
	};
	union FileValue
	{
		int i;
		__int64 i64;
		float d;
		bool b;
	};

	AbstractField();
	~AbstractField();
public:
	int fileNumber;
	FileValue val;
	std::string mem;
	FieldWireType wireType;
	std::map<int, std::vector<std::shared_ptr<AbstractField>>> fileds;
	int blockSize;
	guessType gt;
};
typedef std::shared_ptr<AbstractField> AbstractFieldPtr;

class AbstractMessage : public AbstractField
{
public:
	AbstractMessage();
	~AbstractMessage();

	bool paresFromStream(google::protobuf::io::CodedInputStream* input);
};
typedef std::shared_ptr<AbstractMessage> AbstractMessagePtr;
#endif // AbstractMessage_h__
