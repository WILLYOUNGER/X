#include "XLog/XLog.h"
int main(int argc, char* argv[])
{
	if (!XLOG->init("XUserLog.txt", 0))
	{
		return 0;
	}

    XLOG_INFO("Hello XUser");

	return 0;
}
