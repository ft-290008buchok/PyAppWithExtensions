#include<iostream>
#include<string>
#include<Windows.h>
#include<Python.h>

long calc_factorial(long a)
{
	if (a > 1)
	{
		a--;
		a = calc_factorial(a) * (a + 1);
	}
	return a;
}

double calc_tg(double a)
{
	return sin(a) / cos(a);
}

std::string make_concatenation(std::string s1, std::string s2)
{
	return s1 + s2;
}

//strapping for Python

PyObject* factorial(PyObject*, PyObject* o)
{
	long a = PyLong_AsLong(o);
	long f = calc_factorial(a);
	return PyLong_FromLong(f);
}

PyObject* tg(PyObject*, PyObject* o)
{
	double a = PyFloat_AsDouble(o);
	double t = calc_tg(a);
	return PyFloat_FromDouble(t);
}

PyObject* concatenation(PyObject*, PyListObject* o)
{
	std::string s1 = PyUnicode_AsUTF8(o->ob_item[0]);
	std::string s2 = PyUnicode_AsUTF8(o->ob_item[1]);
	std::string s = make_concatenation(s1, s2);

	char* str = new char[256];
	str = &s[0];
	return PyUnicode_FromString(str);
}

static PyMethodDef fast_methods[] =
{
	{ "fast_factorial", (PyCFunction)factorial, METH_O, nullptr },
	{ "fast_tg", (PyCFunction)tg, METH_O, nullptr },
	{ "fast_concatenation", (PyCFunction)concatenation, METH_O, nullptr },
	{ nullptr, nullptr, 0, nullptr }
};

static PyModuleDef fast_module =
{
	PyModuleDef_HEAD_INIT,
	"fast",                        // Module name to use with Python import statements
	"Provides some functions, but faster",  // Module description
	0,
	fast_methods                   // Structure that defines the methods of the module
};

PyMODINIT_FUNC PyInit_fast() {
	return PyModule_Create(&fast_module);
}