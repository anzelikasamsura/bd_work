#pragma once

#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;
using namespace System;

// ������� � ����� �� ����������� ����, ��� ��������
void _MarshalString(String^ s, string& os) {
	using namespace Runtime::InteropServices;
	const char* chars =
		(const char*)(Marshal::StringToHGlobalAnsi(s)).ToPointer();
	os = chars;
	Marshal::FreeHGlobal(IntPtr((void*)chars));
}


void File_save(System::String^ text_osn, string buton, System::String^ dop_sved) {

	/* �� std::string � System::String^
	char* strChar = "������";
	std::string str2 = "������";
	System::String^ strCLR = gcnew System::String(strChar);
	System::String^ strCLR2 = gcnew System::String(str2.c_str());*/

	string dop_sved1, text_osn1;

	_MarshalString(text_osn, text_osn1);
	_MarshalString(dop_sved, dop_sved1);


	if (buton == "sr_ball") {
		ofstream sr_ball;
		sr_ball.open("������� ���� ������.txt");

		sr_ball << "� ������ " + dop_sved1 + " ������� ���� - " + text_osn1;

		sr_ball.close();
	}

	if (buton == "poisk") {
		ofstream poisk;
		poisk.open("����� �������� �� ���� ������.txt");

		poisk << "�� ������ ������ ���� �������� ��������� ������:\n";
		poisk << text_osn1;

		poisk.close();
	}

	if (buton == "obhaga") {
		ofstream obhaga;
		obhaga.open("����������� � ���������.txt");

		obhaga << text_osn1;

		obhaga.close();
	}

	if (buton == "svedenia") {
		ofstream svedenia;
		svedenia.open("�������� �� ������.txt");

		svedenia << "�� ������ " + dop_sved1 + " ���� ������� ��������� ����������: \n";
		svedenia << text_osn1;

		svedenia.close();
	}

}