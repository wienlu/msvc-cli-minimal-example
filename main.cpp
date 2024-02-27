#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>

#include <msclr/gcroot.h>
#include <msclr/marshal.h>
#include <msclr/marshal_cppstd.h>

#using <System.dll>

/// below are some minimal examples that do or don't work.
/// those that don't compile are commented out.


// this errors out because internal iterators are using constraints on the System::Object
//std::unordered_map<uint64_t, msclr::gcroot<System::Object^>> map;

// vector works?!
std::vector<msclr::gcroot<System::Object^>> vec = {};

void foo()
{
	std::vector<msclr::gcroot<System::Object^>> vec = {};

	// pushing back does not work though
	//vec.push_back(gcnew System::Object());

	// iterating somehow works?! even though iterators are involved in this syntax?
	for (const auto& obj : vec)
	{
		std::string s = msclr::interop::marshal_as<std::string>(obj->ToString());
		std::cout << s;
	}

	// any use of iterators does not work either
	//const auto itr = std::find(vec.cbegin(), vec.cend(), gcnew System::Object());
}