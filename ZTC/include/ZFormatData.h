#include <fstream>
#include <vector>

using namespace std;

class ZFormatData
{
public:
	ZFormatData(const char *pReadFileName, const char * pWriteFileName);
	~ZFormatData();
	bool isVaild();
	void formatData();
	void formatData1();
private:
	
	bool splitBaseOnGropChar(string str, string split, vector<string > &vStr);
	void trim(string &str);

	ofstream m_writeFile;
	ifstream m_readFile;
};

extern const int a[2];