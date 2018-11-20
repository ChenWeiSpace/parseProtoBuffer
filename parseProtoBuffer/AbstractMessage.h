#ifndef AbstractMessage_h__
#define AbstractMessage_h__
#include <string>
#include <map>
#include <memory>
#include <vector>
#include <tuple>
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
		Is_Double,
		Is_String,
		Is_Message,
		Is_IntArray,
		Is_FloatArray,
		Is_DoubleArray

	};
	union FileValue
	{
		int i;
		__int64 i64;
		float d;
		bool b;
	};
	typedef std::vector<google::protobuf::uint64> IntArray;
	typedef std::vector<float> FLoatArray;
	typedef std::vector<double> DoubleArray;

	AbstractField();
	~AbstractField();

	void setName(std::string name);
	std::string getName();
public:
	int fileNumber;
	FileValue val;
	std::string mem;
	FieldWireType wireType;
	std::map<int, std::vector<std::shared_ptr<AbstractField>>> fileds;
	int blockSize;
	guessType gt;

	IntArray  _valArray;
	FLoatArray _fArray;
	DoubleArray _dArray;

	std::string _name;
};
typedef std::shared_ptr<AbstractField> AbstractFieldPtr;

class AbstractMessage : public AbstractField
{
public:
	AbstractMessage();
	~AbstractMessage();

	bool paresFromStream(google::protobuf::io::CodedInputStream* input);
	bool readAsIntArray(google::protobuf::io::CodedInputStream* input, IntArray & valArray,int length);
	bool readAsIntArray(std::string mem, IntArray & valArray, int length);
	
	//************************************
	// Method:    readAsFloatArray
	// FullName:  AbstractMessage::readAsFloatArray
	// Access:    public 
	// Returns:   bool
	// Qualifier:
	// Parameter: std::string mem
	// Parameter: FLoatArray & valArray
	// Parameter: int length
	//************************************
	bool readAsFloatArray(std::string mem, FLoatArray & valArray, int length);

	bool readAsDoubleArray(std::string mem, DoubleArray & valArray, int length);

	bool readAsMessage(std::string mem, std::shared_ptr<AbstractMessage > & mesPtr);

	//************************************
	// Method:    exitFieldTar ÊÇ·ñ´æÔÚfieldTar
	// FullName:  AbstractMessage::exitFieldTar
	// Access:    public 
	// Returns:   std::tuple<int, int,bool> fieldNum,WireType,
	// Qualifier:
	// Parameter: std::string mem
	//************************************
	std::tuple<int, int,bool> exitFieldTar(std::string mem);
};
typedef std::shared_ptr<AbstractMessage> AbstractMessagePtr;
#endif // AbstractMessage_h__
