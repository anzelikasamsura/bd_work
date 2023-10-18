#include "MyForm.h"
#include <iostream>
#include <fstream>
#include <string.h>
#include "save_file.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace System::Data::OleDb;
using namespace std;

[STAThreadAttribute]
int main() {
	Application::EnableVisualStyles;
	Application::SetCompatibleTextRenderingDefault(false);
	bd::MyForm form;
	Application::Run(% form);

}

//

//

System::Void bd::MyForm::MyForm_Load(System::Object^ sender, System::EventArgs^ e)
{
	return System::Void();
}

//     ��������� �������

System::Void bd::MyForm::button_add(System::Object^ sender, System::EventArgs^ e)
{

	try {

		String^ coonectionString = "provider=Microsoft.Ace.OLEDB.16.0;Data Source=Database.accdb";
		OleDbConnection^ conDataBase = gcnew OleDbConnection(coonectionString);
		conDataBase->Open();

		String^ query = "SELECT * FROM [table]";
		OleDbCommand^ dbComand = gcnew OleDbCommand(query, conDataBase);
		OleDbDataReader^ dbReader = dbComand->ExecuteReader();

		dataGridView1->Rows->Clear();

		if (dbReader->HasRows == false) {
			MessageBox::Show("������ ���������� ������", "������");
		}
		else {
			while (dbReader->Read()) {
				dataGridView1->Rows->Add(dbReader["Nom_z"], dbReader["Surname"], dbReader["Name"], dbReader["Ot"], dbReader["Obhaga"],
					dbReader["Mat"], dbReader["Rus"], dbReader["Bel"], dbReader["Hist"], dbReader["Eng"], dbReader["Group"], dbReader["Ball"]);
			}
		}
		dbReader->Close();
		conDataBase->Close();

	}
	catch (Exception^ ex) { MessageBox::Show(ex->Message->ToString()); }

	return System::Void();
}

//     �������� ������

System::Void bd::MyForm::button_dowloand(System::Object^ sender, System::EventArgs^ e)
{

	try {

		if (dataGridView1->SelectedRows->Count != 1) {
			MessageBox::Show("�������� 1 ������ ��� ����������", "�������");
			return;
		}

		int Index = dataGridView1->SelectedRows[0]->Index;

		if (dataGridView1->Rows[Index]->Cells[0]->Value == nullptr ||
			dataGridView1->Rows[Index]->Cells[1]->Value == nullptr ||
			dataGridView1->Rows[Index]->Cells[2]->Value == nullptr ||
			dataGridView1->Rows[Index]->Cells[3]->Value == nullptr ||
			// 4-9 �������� ������������� ��� � ���� �������
			dataGridView1->Rows[Index]->Cells[10]->Value == nullptr ||
			dataGridView1->Rows[Index]->Cells[11]->Value == nullptr) {
			MessageBox::Show("�� ��� ������ �������", "�������");
			return;
		}

		String^ nom_z = dataGridView1->Rows[Index]->Cells["nom_z"]->Value->ToString();
		String^ surname = dataGridView1->Rows[Index]->Cells["surname"]->Value->ToString();
		String^ name = dataGridView1->Rows[Index]->Cells["name"]->Value->ToString();
		String^ ot = dataGridView1->Rows[Index]->Cells["ot"]->Value->ToString();
		String^ group = dataGridView1->Rows[Index]->Cells["group"]->Value->ToString();
		String^ ball = dataGridView1->Rows[Index]->Cells["ball"]->Value->ToString();

		String^ coonectionString = "provider=Microsoft.Ace.OLEDB.16.0;Data Source=Database.accdb";
		OleDbConnection^ conDataBase = gcnew OleDbConnection(coonectionString);
		conDataBase->Open();

		String^ query = "INSERT INTO [table] VALUES (" + nom_z + ",'" + surname + "','" + name + "','" + ot + "',(" +
			dataGridView1->Rows[Index]->Cells["obhaga"]->EditedFormattedValue->ToString() + "),(" +
			dataGridView1->Rows[Index]->Cells["mat"]->EditedFormattedValue->ToString() + "),(" +
			dataGridView1->Rows[Index]->Cells["rus"]->EditedFormattedValue->ToString() + "),(" +
			dataGridView1->Rows[Index]->Cells["bel"]->EditedFormattedValue->ToString() + "),(" +
			dataGridView1->Rows[Index]->Cells["hist"]->EditedFormattedValue->ToString() + "),(" +
			dataGridView1->Rows[Index]->Cells["eng"]->EditedFormattedValue->ToString() + "),'" +
			group + "'," + ball + ")";
		OleDbCommand^ dbComand = gcnew OleDbCommand(query, conDataBase);

		if (dbComand->ExecuteNonQuery() != 1) { MessageBox::Show("������ ���������� �������", "������"); }
		else { MessageBox::Show("������ ���������", "�����"); }

		conDataBase->Close();
	}
	catch (Exception^ ex) { MessageBox::Show(ex->Message->ToString()); }

	return System::Void();
}

//     �������� ������

System::Void bd::MyForm::button_update(System::Object^ sender, System::EventArgs^ e)
{

	try {

		if (dataGridView1->SelectedRows->Count != 1) {
			MessageBox::Show("�������� 1 ������ ��� ����������", "�������");
			return;
		}

		int Index = dataGridView1->SelectedRows[0]->Index;

		if (dataGridView1->Rows[Index]->Cells[0]->Value == nullptr ||
			dataGridView1->Rows[Index]->Cells[1]->Value == nullptr ||
			dataGridView1->Rows[Index]->Cells[2]->Value == nullptr ||
			dataGridView1->Rows[Index]->Cells[3]->Value == nullptr ||
			// 4-9 �������� ������������� ��� � ���� �������
			dataGridView1->Rows[Index]->Cells[10]->Value == nullptr ||
			dataGridView1->Rows[Index]->Cells[11]->Value == nullptr) {
			MessageBox::Show("�� ��� ������ �������", "�������");
			return;
		}

		String^ nom_z = dataGridView1->Rows[Index]->Cells["nom_z"]->Value->ToString();
		String^ surname = dataGridView1->Rows[Index]->Cells["surname"]->Value->ToString();
		String^ name = dataGridView1->Rows[Index]->Cells["name"]->Value->ToString();
		String^ ot = dataGridView1->Rows[Index]->Cells["ot"]->Value->ToString();

		String^ obhaga = Convert::ToString(dataGridView1->Rows[Index]->Cells["obhaga"]->Value);
		String^ mat = Convert::ToString(dataGridView1->Rows[Index]->Cells["mat"]->Value);
		String^ rus = Convert::ToString(dataGridView1->Rows[Index]->Cells["rus"]->Value);
		String^ bel = Convert::ToString(dataGridView1->Rows[Index]->Cells["bel"]->Value);
		String^ hist = Convert::ToString(dataGridView1->Rows[Index]->Cells["hist"]->Value);
		String^ eng = Convert::ToString(dataGridView1->Rows[Index]->Cells["eng"]->Value);

		if (Convert::ToString(dataGridView1->Rows[Index]->Cells["obhaga"]->Value) == "True") {  obhaga = "1"; }
		else {  obhaga = "null"; }
		if (Convert::ToString(dataGridView1->Rows[Index]->Cells["mat"]->Value) == "True") {  mat = "1"; }
		else {  mat = "null"; }
		if (Convert::ToString(dataGridView1->Rows[Index]->Cells["rus"]->Value) == "True") {  rus = "1"; }
		else {  rus = "null"; }
		if (Convert::ToString(dataGridView1->Rows[Index]->Cells["bel"]->Value) == "True") {  bel = "1"; }
		else {  bel = "null"; }
		if (Convert::ToString(dataGridView1->Rows[Index]->Cells["hist"]->Value) == "True") {  hist = "1"; }
		else {  hist = "null"; }
		if (Convert::ToString(dataGridView1->Rows[Index]->Cells["eng"]->Value) == "True") {  eng = "1"; }
		else {  eng = "null"; }

		String^ group = dataGridView1->Rows[Index]->Cells["group"]->Value->ToString();
		String^ ball = dataGridView1->Rows[Index]->Cells["ball"]->Value->ToString();

		String^ coonectionString = "provider=Microsoft.Ace.OLEDB.16.0;Data Source=Database.accdb";
		OleDbConnection^ conDataBase = gcnew OleDbConnection(coonectionString);
		conDataBase->Open();

		String^ query = "UPDATE [table] SET Surname ='" + surname + "', Name ='" + name + "', Ot ='" + ot +
			"', Obhaga = " + obhaga + ", Mat = " + mat + ", Rus = " + rus + ", Bel = " + bel + ", Hist = " + hist + ", Eng = " + eng +
			", Group ='" + group + "', Ball = " + ball + " WHERE Nom_z = " + nom_z; 

		OleDbCommand^ dbComand = gcnew OleDbCommand(query, conDataBase);

		if (dbComand->ExecuteNonQuery() != 1) { MessageBox::Show("������ ���������� �������", "������"); }
		else { MessageBox::Show("������ ���������", "�����"); }

		conDataBase->Close();
	}
	catch (Exception^ ex) { MessageBox::Show(ex->Message->ToString()); }

	//richTextBox1->Text = dataGridView1->Rows[0]->Cells["obhaga"]->Value->ToString() + " " + Convert::ToString(dataGridView1->Rows[0]->Cells["eng"]->Value);

	return System::Void();
}

//     ������� ������

System::Void bd::MyForm::button_delete(System::Object^ sender, System::EventArgs^ e)
{

	try {

		if (dataGridView1->SelectedRows->Count != 1) {
			MessageBox::Show("�������� 1 ������ ��� ��������", "�������");
			return;
		}

		int Index = dataGridView1->SelectedRows[0]->Index;

		if (dataGridView1->Rows[Index]->Cells[0]->Value == nullptr) {
			MessageBox::Show("�� ��� ������ �������", "�������");
			return;
		}

		String^ nom_z = dataGridView1->Rows[Index]->Cells[0]->Value->ToString();

		String^ coonectionString = "provider=Microsoft.Ace.OLEDB.16.0;Data Source=Database.accdb";
		OleDbConnection^ conDataBase = gcnew OleDbConnection(coonectionString);
		conDataBase->Open();

		String^ query = "DELETE FROM [table] WHERE nom_z = " + nom_z;
		OleDbCommand^ dbComand = gcnew OleDbCommand(query, conDataBase);

		if (dbComand->ExecuteNonQuery() != 1) { MessageBox::Show("������ ���������� �������", "������"); }
		else {
			MessageBox::Show("������ �������", "�����");
			dataGridView1->Rows->RemoveAt(Index);
		}

		conDataBase->Close();

	}
	catch (Exception^ ex) { MessageBox::Show(ex->Message->ToString()); }

	return System::Void();
}

//     ������� ����

System::Void bd::MyForm::button_ball(System::Object^ sender, System::EventArgs^ e)
{
	try {

		if (textBox1->Text != "") {

			int t = 0;
			for (int i = 0; i < dataGridView1->Rows->Count; i++) {
				if (Convert::ToString(dataGridView1->Rows[i]->Cells["group"]->Value) == Convert::ToString(textBox1->Text)) {
					t++;
				}
			}

			if (t > 0) {

				int sr_b = 0; int a = 0;

				for (int i = 0; i < dataGridView1->Rows->Count-1; i++) {
					if (Convert::ToString(dataGridView1->Rows[i]->Cells["group"]->Value) == Convert::ToString(textBox1->Text)) {
						sr_b += Convert::ToInt32(dataGridView1->Rows[i]->Cells["ball"]->Value);
						a++;
					}
				}

				label5->Text = Convert::ToString(sr_b / a);
			}
			else { label5->Text = "����� ������ ���!"; }
		}
		else { label5->Text = "������� �����\n������!"; }
	}
	catch (Exception^ ex) { MessageBox::Show(ex->Message->ToString()); }

	return System::Void();
}

// ����� ����� ���� ���������� �� 4-�, 5-� � 5 ����� 6-�� �������

System::Void bd::MyForm::Svedenia(System::Object^ sender, System::EventArgs^ e)
{
	try {

		if (textBox2->Text == nullptr || textBox2->Text == "" || textBox2->Text == " ")
		{
			richTextBox1->Text = "������� �������� ������!";
		}
		else {
			richTextBox1->Text = "";

			int t = 0;
			for (int i = 0; i < dataGridView1->Rows->Count; i++) {

				if (Convert::ToString(dataGridView1->Rows[i]->Cells[10]->Value) == Convert::ToString(textBox2->Text)) {
					t++;
				}
			}

			if (t > 0) {
				for (int i = 0; i < dataGridView1->Rows->Count - 1; i++)
				{
					if (Convert::ToString(dataGridView1->Rows[i]->Cells["group"]->Value) == Convert::ToString(textBox2->Text))
					{
						richTextBox1->Text += Convert::ToString(dataGridView1->Rows[i]->Cells["name"]->Value) + " " +
							Convert::ToString(dataGridView1->Rows[i]->Cells["surname"]->Value) + " " +
							Convert::ToString(dataGridView1->Rows[i]->Cells["ot"]->Value) +
							". ����� �������� ������: " + Convert::ToString(dataGridView1->Rows[i]->Cells["nom_z"]->Value) +
							". ������: ";

						int r = 0;
						if (dataGridView1->Rows[i]->Cells["mat"]->EditedFormattedValue->ToString() == "True")
						{
							richTextBox1->Text += "����������. "; r++;
						}

						if (dataGridView1->Rows[i]->Cells["rus"]->EditedFormattedValue->ToString() == "True")
						{
							richTextBox1->Text += "�������. "; r++;
						}

						if (dataGridView1->Rows[i]->Cells["bel"]->EditedFormattedValue->ToString() == "True")
						{
							richTextBox1->Text += "�����������. "; r++;
						}

						if (dataGridView1->Rows[i]->Cells["hist"]->EditedFormattedValue->ToString() == "True")
						{
							richTextBox1->Text += "�������. "; r++;
						}

						if (dataGridView1->Rows[i]->Cells["eng"]->EditedFormattedValue->ToString() == "True")
						{
							richTextBox1->Text += "����������. "; r++;
						}

						if (r == 0) { richTextBox1->Text += " ������ �� ������(�) "; }

						richTextBox1->Text += "\n";
					}
				}
			}
			else {
				richTextBox1->Text = "����� ������ ���!";
				return;
			}
		}
	}
	catch (Exception^ ex) { MessageBox::Show(ex->Message->ToString()); }

	return System::Void();
}

// ����� ����� ����� 6-�� ������� �� ������� � ������ �������

System::Void bd::MyForm::familia(System::Object^ sender, System::EventArgs^ e)
{
	try {
		if (textBox3->Text == "")
		{ richTextBox2->Text = "������� �������!"; }

		else {
			richTextBox2->Text = "";

			int t = 0;
			for (int i = 0; i < dataGridView1->Rows->Count - 1; i++) {
				if (Convert::ToString(dataGridView1->Rows[i]->Cells["surname"]->Value) == textBox3->Text->ToString()) {
					t++;
				}
			}

			if (t > 0)
			{
				for (int i = 0; i < dataGridView1->Rows->Count - 1; i++)
				{
					if (Convert::ToString(dataGridView1->Rows[i]->Cells["surname"]->Value) == textBox3->Text->ToString())
					{
						richTextBox2->Text += Convert::ToString(dataGridView1->Rows[i]->Cells["name"]->Value) + "\n" +
							Convert::ToString(dataGridView1->Rows[i]->Cells["surname"]->Value) + "\n" +
							Convert::ToString(dataGridView1->Rows[i]->Cells["ot"]->Value) +
							"\n����� �������� ������: " + Convert::ToString(dataGridView1->Rows[i]->Cells["nom_z"]->Value);
						richTextBox2->Text += "\n������ ������: " + (i+1);
					/*	int r = 0;
						if (dataGridView1->Rows[i]->Cells["mat"]->EditedFormattedValue->ToString() == "True") 
						{ richTextBox2->Text += "����������, "; r++; }

						if (dataGridView1->Rows[i]->Cells["rus"]->EditedFormattedValue->ToString() == "True") 
						{ richTextBox2->Text += "�������, "; r++; }

						if (dataGridView1->Rows[i]->Cells["bel"]->EditedFormattedValue->ToString() == "True")
						{ richTextBox2->Text += "�����������, "; r++; }

						if (dataGridView1->Rows[i]->Cells["hist"]->EditedFormattedValue->ToString() == "True") 
						{ richTextBox2->Text += "�������, "; r++; }

						if (dataGridView1->Rows[i]->Cells["eng"]->EditedFormattedValue->ToString() == "True")
						{ richTextBox2->Text += "����������. "; r++; }

						if (r == 0) { richTextBox2->Text += " ������ �� ������(�) "; }*/

						richTextBox2->Text += "\n";
					}
				}
			}
			else { richTextBox2->Text = "������� � ����� �������� ���."; }
		}
	}
	catch (Exception^ ex) { MessageBox::Show(ex->Message->ToString()); }

	return System::Void();
}

System::Void bd::MyForm::nomerzah(System::Object^ sender, System::EventArgs^ e)
{
	try {
		if (textBox3->Text == "")
		{ richTextBox2->Text = "������� ����� �������� ������!"; }
		
		else
		{ 
			richTextBox2->Text = "";

			int t = 0;
			for (int i = 0; i < dataGridView1->Rows->Count - 1; i++) {
				if (Convert::ToString(dataGridView1->Rows[i]->Cells["nom_z"]->Value) == textBox3->Text->ToString()) {
					t++;
				}
			}

			if (t > 0)
			{
				for (int i = 0; i < dataGridView1->Rows->Count - 1; i++)
				{
					if (Convert::ToString(dataGridView1->Rows[i]->Cells["nom_z"]->Value) == textBox3->Text->ToString())
					{
						richTextBox2->Text += Convert::ToString(dataGridView1->Rows[i]->Cells["name"]->Value) + "\n" +
							Convert::ToString(dataGridView1->Rows[i]->Cells["surname"]->Value) + "\n" +
							Convert::ToString(dataGridView1->Rows[i]->Cells["ot"]->Value) +
							"\n����� �������� ������: " + Convert::ToString(dataGridView1->Rows[i]->Cells["nom_z"]->Value);
						richTextBox2->Text += "\n������ ������: " + (i + 1);
						/*	int r = 0;
							if (dataGridView1->Rows[i]->Cells["mat"]->EditedFormattedValue->ToString() == "True")
							{ richTextBox2->Text += "����������, "; r++; }

							if (dataGridView1->Rows[i]->Cells["rus"]->EditedFormattedValue->ToString() == "True")
							{ richTextBox2->Text += "�������, "; r++; }

							if (dataGridView1->Rows[i]->Cells["bel"]->EditedFormattedValue->ToString() == "True")
							{ richTextBox2->Text += "�����������, "; r++; }

							if (dataGridView1->Rows[i]->Cells["hist"]->EditedFormattedValue->ToString() == "True")
							{ richTextBox2->Text += "�������, "; r++; }

							if (dataGridView1->Rows[i]->Cells["eng"]->EditedFormattedValue->ToString() == "True")
							{ richTextBox2->Text += "����������. "; r++; }

							if (r == 0) { richTextBox2->Text += " ������ �� ������(�) "; }*/

						richTextBox2->Text += "\n";
					}
				}
			}
			else { richTextBox2->Text = "������� � ����� ������� ���."; }
		}
	}
	catch (Exception^ ex) { MessageBox::Show(ex->Message->ToString()); }

	return System::Void();
}



System::Void bd::MyForm::textbox_probeli(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e)
{
	if (e->KeyChar == ' ' || e->KeyChar == '\n') { e->Handled = true; }
	return System::Void();
}

// ������� ���������� ������� (�������� ������ 1 ���)

System::Void bd::MyForm::sortirovka(System::Object^ sender, System::EventArgs^ e)
{
	try
	{
		if (radioButton1->Checked) {
			dataGridView1->Sort(dataGridView1->Columns["surname"], ListSortDirection::Ascending);
			return;
		}
		else if (radioButton2->Checked) {
			dataGridView1->Sort(dataGridView1->Columns["ball"], ListSortDirection::Descending);
			return;
		}
		MessageBox::Show("�� �� ������� ����� ����������!", "��������!");
	}
	catch (Exception^ ex) { MessageBox::Show(ex->Message->ToString()); }

	return System::Void();
}

System::Void bd::MyForm::obhezitie(System::Object^ sender, System::EventArgs^ e)
{
	try {
		richTextBox3->Text = "������ ����������� � ���������:\n\n";

		for (int i = 0; i < dataGridView1->Rows->Count - 1; i++) {
			if (dataGridView1->Rows[i]->Cells["obhaga"]->EditedFormattedValue->ToString() == "True")
			{
				richTextBox3->Text += Convert::ToString(dataGridView1->Rows[i]->Cells["name"]->Value) + " " +
					Convert::ToString(dataGridView1->Rows[i]->Cells["surname"]->Value) + " " +
					Convert::ToString(dataGridView1->Rows[i]->Cells["ot"]->Value) + ", " + 
					Convert::ToString(dataGridView1->Rows[i]->Cells["group"]->Value) + "\n";
			}
		}
	}
	catch (Exception^ ex) { MessageBox::Show(ex->Message->ToString()); }

	return System::Void();
}

System::Void bd::MyForm::save_file(System::Object^ sender, System::EventArgs^ e)
{
	try {

		if (radioButton5->Checked) {

			if (label5->Text == "" || textBox1->Text == "" ||
				label5->Text == "����� ������ ���!" || label5->Text == "������� �����\n������!")
			{
				MessageBox::Show("�� ������� ��������� ������! �������� ������������ ����������� ������", "��������!");
				return;
			}
			else {
				File_save(label5->Text, "sr_ball", textBox1->Text);
				MessageBox::Show("������ ���������!");
			}
			return;
		}

		if (radioButton3->Checked) {
			if (richTextBox2->Text == "" || textBox3->Text == "" ||
				richTextBox2->Text == "������� �������!" || richTextBox2->Text == "������� � ����� �������� ���." || richTextBox2->Text == "\n" ||
				richTextBox2->Text == "������� ����� �������� ������!" || richTextBox2->Text == "������� � ����� ������� ���.") {
				MessageBox::Show("�� ������� ��������� ������! �������� ������������ ����������� ������", "��������!");
				return;
			}
			else {
				File_save(richTextBox2->Text, "poisk", textBox3->Text);
				MessageBox::Show("������ ���������!");
			}
			return;
		}

		if (radioButton6->Checked) {
			if (richTextBox3->Text == "" || richTextBox3->Text == "\n" ) {
				MessageBox::Show("�� ������� ��������� ������! �������� ������������ ����������� ������", "��������!");
				return;
			}
			else { 
				File_save(richTextBox3->Text, "obhaga", " ");
				MessageBox::Show("������ ���������!");
			}
			return;
		}

		if (radioButton4->Checked) {
			if (richTextBox1->Text == "" || textBox2->Text == "" || richTextBox1->Text == "\n" ||
				richTextBox1->Text == "����� ������ ���!" || richTextBox1->Text == "������� �������� ������!")
			{
				MessageBox::Show("�� ������� ��������� ������! �������� ������������ ����������� ������", "��������!");
				return;
			}
			else { 
				File_save(richTextBox1->Text, "svedenia", textBox2->Text);
				MessageBox::Show("������ ���������!");
			}
			return;
		}

		MessageBox::Show("�������� ����� ��� ����������!");
	}
	catch (Exception^ ex) { MessageBox::Show(ex->Message->ToString()); }

	return System::Void();
}

System::Void bd::MyForm::Programm_svedenia(System::Object^ sender, System::EventArgs^ e)
{
	MessageBox::Show("���� ������ �������� � �������������� Access.\n\n" + 
	"������ ���������� ������� � ����� �������� �������� � ��������� ��� ��������� ��� ��������.\n"+
	"�� ������ ����� ���������� �� 1-� ������, ����� ��������� �� ��� ������� ��� ������ �������� ������, ������ ����������� � ���������, ������� ���� ������.\n"+
	"��� �� �� ������ ��������� ��� ���������� �������� � ��������� ����.");
	return System::Void();
}

System::Void bd::MyForm::App_exit(System::Object^ sender, System::EventArgs^ e)
{
	Application::Exit();
	return System::Void();
}

System::Void bd::MyForm::block_text(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e)
{
	e->Handled = true;
	return System::Void();
}

