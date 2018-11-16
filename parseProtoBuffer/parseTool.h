#ifndef parseTool_h__
#define parseTool_h__
#include <memory>
#include <iostream>
class parseTool : std::enable_shared_from_this<parseTool>
{
public:
	parseTool();
	~parseTool();

	bool readIo(std::string & str);
	bool readFile(std::string  fileName);

	bool readIo(std::istream & is);

};
typedef std::shared_ptr<parseTool> parseToolPtr;
#endif // parseTool_h__
