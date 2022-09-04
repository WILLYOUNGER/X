#include "XLog/XLog.h"
int main(int argc, char* argv[])
{
	if (!XLOG->init("XMuduoLog.txt", 1))
	{
		return 0;
	}

    XLOG_INFO("Hello XMuduo");

	return 0;
}
