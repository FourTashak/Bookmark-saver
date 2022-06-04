#pragma once
#include "MyForm.h"
#include <iostream>
#include <fstream>
#include <string>
#include <msclr/marshal_cppstd.h>

void check_database()
{
	std::ifstream myfile("UrlDatabase.txt");
	if(myfile.good()==TRUE)
	{
		myfile.close();
	}
	else
	{
		myfile.close();
		std::ofstream myfile2; 
		myfile2.open("UrlDatabase.txt");
		//myfile2.close();
	}
}

System::Object^ GetInfo() //Gets the urls from a file saved on the pc
{
	std::string line;
	std::ifstream myfile("UrlDatabase.txt");
	if (myfile.is_open())
	{
		while (std::getline(myfile, line, ' '))
		{
			auto converted = gcnew System::String(line.c_str());
			return converted;
		}
	}
	return "error";
}

void WritetoFile(System::String^ Line)
{
	std::ofstream myfile; 
	myfile.open("UrlDatabase.txt",std::ios::app);

	msclr::interop::marshal_context context;
	std::string standartString = context.marshal_as<std::string>(Line);


	myfile << standartString << std::endl;
	myfile.close();
}

void DeleteLine(System::String^Selected)
{
	std::ifstream myfile("UrlDatabase.txt");
	std::string urls;
	std::getline(myfile,urls,' ');
	msclr::interop::marshal_context context;
	std::string standartString = context.marshal_as<std::string>(Selected);
	int found = urls.find(standartString);
	int size = standartString.size();
	int end = size + found;
	for (;found<end;)
	{
		urls[found]=NULL;
		found++;
		if (found==end)
		{
			urls[found] = NULL;
		}
	}
	myfile.close();

	urls.erase(remove(urls.begin(), urls.end(), '\0'), urls.end());

	std::ofstream myfile2;
	myfile2.open("UrlDatabase.txt");
	myfile2 << urls;
	myfile2.close();
}
