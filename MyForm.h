#pragma once
#include <Windows.h>
#include <string>
#include "func.h"

namespace UrlSaver {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TextBox^ textBox1;
	private: System::ComponentModel::BackgroundWorker^ backgroundWorker1;
	private: System::Windows::Forms::Button^ button1;

	private: System::Windows::Forms::ListBox^ listBox1;
	private: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::Button^ button3;



	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->backgroundWorker1 = (gcnew System::ComponentModel::BackgroundWorker());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->listBox1 = (gcnew System::Windows::Forms::ListBox());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(12, 331);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(475, 20);
			this->textBox1->TabIndex = 0;
			// 
			// backgroundWorker1
			// 
			this->backgroundWorker1->WorkerSupportsCancellation = true;
			this->backgroundWorker1->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &MyForm::backgroundWorker1_DoWork);
			this->backgroundWorker1->RunWorkerAsync();
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(12, 357);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(205, 58);
			this->button1->TabIndex = 1;
			this->button1->Text = L"Save";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// listBox1
			// 
			this->listBox1->FormattingEnabled = true;
			this->listBox1->Location = System::Drawing::Point(12, 6);
			this->listBox1->Name = L"listBox1";
			this->listBox1->Size = System::Drawing::Size(475, 316);
			this->listBox1->TabIndex = 3;
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(148, 438);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(205, 58);
			this->button2->TabIndex = 4;
			this->button2->Text = L"Browse";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &MyForm::button2_Click);
			// 
			// button3
			// 
			this->button3->Location = System::Drawing::Point(282, 357);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(205, 58);
			this->button3->TabIndex = 5;
			this->button3->Text = L"Delete";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &MyForm::button3_Click);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->AutoSize = true;
			this->ClientSize = System::Drawing::Size(496, 529);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->listBox1);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->textBox1);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) // Save
	{
		System::String^ text = UrlSaver::MyForm::textBox1->Text;
		if (textBox1->Text != "")
		{
			listBox1->Items->Add(text);
			WritetoFile(text);
		}
	}

	private: System::Void backgroundWorker1_DoWork(System::Object^ sender, System::ComponentModel::DoWorkEventArgs^ e)//Read
	{
		check_database();
		std::string line;
		std::ifstream myfile("UrlDatabase.txt");
		
		while (true)
		{
			std::getline(myfile, line);
			if (line == "")
			{
				break;
			}
			auto converted = gcnew System::String(line.c_str());
			listBox1->Items->Add(converted);
		}
		myfile.close();
	}

	private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) // Browse
	{
		System::String^ Url;
		if (listBox1->SelectedItem != nullptr)
		{
			Url = listBox1->SelectedItem->ToString();
			System::Diagnostics::Process::Start(Url);
		}
	}

	private: System::Void button3_Click(System::Object^ sender, System::EventArgs^ e) // Delete
	{
		System::Object^ who = UrlSaver::MyForm::listBox1->SelectedItem;
		listBox1->Items->Remove(listBox1->SelectedItem);
		if (who!=nullptr)
		{
			DeleteLine(who->ToString());
		}
	}
	};
}
