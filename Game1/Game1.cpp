#include "stdafx.h"
#include <boost/python.hpp>
#include <errno.h>
#include <fstream>

using namespace boost::python;

std::string extractException()
{
	using namespace boost::python;

	PyObject *exc, *val, *tb;
	PyErr_Fetch(&exc, &val, &tb);
	PyErr_NormalizeException(&exc, &val, &tb);
	handle<> hexc(exc), hval(allow_null(val)), htb(allow_null(tb));
	if (!hval)
	{
		return extract<std::string>(str(hexc));
	}
	else
	{
		object traceback(import("traceback"));
		object format_exception(traceback.attr("format_exception"));
		object formatted_list(format_exception(hexc, hval, htb));
		object formatted(str("").join(formatted_list));
		return extract<std::string>(formatted);
	}
}

void PyRun_FromFile(const char* filename)
{
	std::ifstream ifs(filename);
	std::string script((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
	PyRun_SimpleString(script.c_str());
}

int _tmain(int argc, _TCHAR* argv[])
{
	try {
		Py_Initialize();
		PyRun_FromFile("C:/Users/ops/Documents/Visual Studio 2012/Projects/Game/Game1/scripts/client.py");

	}
	catch(error_already_set const &)
	{
		PyErr_Print();
		printf("%s\n", extractException());
	}
	system("pause");
	return 0;
}

