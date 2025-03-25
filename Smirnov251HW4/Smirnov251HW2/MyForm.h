#pragma once
#include "src/Matrix.h"
#include "src/Transform.h"
#include "src/Figure.h"
#include "src/Clip.h"
#include <vector>
#include <fstream>
#include <sstream>

namespace Smirnov251HW2 {
	// Number of lines
	float Vx; // ������ ������� �� �����������
	float Vy; // ������ ������� �� ���������
	float aspectFig; // ����������� ������ �������
	// �������, � ������� ������������� ��� �������������� 
	// ������������� ��������� �������
	mat3 T = mat3(1.f);
	// ������� ���������� ��������������
	mat3 initT;
	std::vector<path> figure;

	
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// ������ ��� MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: �������� ��� ������������
			//
		}

	protected:
		/// <summary>
		/// ���������� ��� ������������ �������.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::OpenFileDialog^ openFileDialog;
	private: System::Windows::Forms::Button^ btnOpen;
	private: System::Windows::Forms::Button^ button1;
	protected:

	private:
		/// <summary>
		/// ������������ ���������� ������������.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// ��������� ����� ��� ��������� ������������ � �� ��������� 
		/// ���������� ����� ������ � ������� ��������� ����.
		/// </summary>
		void InitializeComponent(void)
		{
			this->openFileDialog = (gcnew System::Windows::Forms::OpenFileDialog());
			this->btnOpen = (gcnew System::Windows::Forms::Button());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// openFileDialog
			// 
			this->openFileDialog->Filter = L"��������� ����� (*.txt)|*.txt|��� ����� (*.*)|*.*";
			this->openFileDialog->Title = L"������� ����";
			// 
			// btnOpen
			// 
			this->btnOpen->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->btnOpen->Location = System::Drawing::Point(315, 26);
			this->btnOpen->Name = L"btnOpen";
			this->btnOpen->Size = System::Drawing::Size(75, 23);
			this->btnOpen->TabIndex = 0;
			this->btnOpen->Text = L"�������";
			this->btnOpen->UseVisualStyleBackColor = true;
			this->btnOpen->Click += gcnew System::EventHandler(this, &MyForm::btnOpen_Click);
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(203, 37);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(0, 0);
			this->button1->TabIndex = 1;
			this->button1->Text = L"button1";
			this->button1->UseVisualStyleBackColor = true;
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(402, 578);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->btnOpen);
			this->DoubleBuffered = true;
			this->KeyPreview = true;
			this->MinimumSize = System::Drawing::Size(155, 120);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			this->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MyForm::MyForm_Paint);
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MyForm::MyForm_KeyDown);
			this->Resize += gcnew System::EventHandler(this, &MyForm::MyForm_Resize);
			this->ResumeLayout(false);

		}
#pragma endregion
	// ���������� �� ������ ����
	private: float left = 30;
		   float right = 100;
		   float top = 20; 
		   float bottom = 50;
		   // �������� ��������� ��������� x, ������� ��������� x
		   float minX = left, maxX;
		   // �������� ��������� ��������� y, ������� ��������� y
		   float minY = top, maxY;
		   // ���������� ������ ������� ���� ��������������
		   float Wcx = left, Wcy;
		   // ������ � ������ ��������������
		   float Wx, Wy;

	private: System::Void rectCalc() {
		// �������� ��������� ��������� x, ������� ��������� x
		maxX = ClientRectangle.Width - right;
		// �������� ��������� ��������� y, ������� ��������� y
		maxY = ClientRectangle.Height - bottom;
		// ���������� ������ ������� ���� ��������������
		Wcy = maxY;
		// ������ ��������������
		Wx = maxX - left;
		// ������ ��������������
		Wy = maxY - top;
	}


	private: System::Void MyForm_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
		Graphics^ g = e->Graphics;
		// ��������� ����� �����������
		g->Clear(Color::Aquamarine);

		Pen^ rectPen = gcnew Pen(Color::Black, 2);
		g->DrawRectangle(rectPen,
			left, // �� ������
			top, // �������� ���� �������� ���� � ������
			Wx, // ������
			Wy // ������
		);

		for (int i = 0; i < figure.size(); i++) {
			// lines - ��������� ������� �����
			path lines = figure[i];
			// ������� pen � �������� = 2
			Pen^ pen = gcnew Pen(Color::FromArgb(
					lines.color.x,
					lines.color.y,
					lines.color.z )
			);
			pen->Width = lines.thickness;
			//��������� ����� ������� �������
			vec2 start = normalize(T * vec3(lines.vertices[0], 1.0));
			// ���� �� �������� ������ (�� �������)
			for (int j = 1; j < lines.vertices.size(); j++) {
				// �������� �����
				vec2 end = normalize(T * vec3(lines.vertices[j], 1.0));
				// �������������� ���������� ����� ��� �������� �������������
				vec2 tempEnd = end;
				// ���� ����� �������
				if (clip(start, end, minX, minY, maxX, maxY)) { 
					// ����� ��������� start � end - ����� ������� ����� �������
					// ��������� ������� ����� ������� 
					g->DrawLine(pen, 
						start.x, start.y,
						end.x, end.y 
					);
				}
				// �������� ����� �������� ������� ���������� ��������� ������ ����������
				start = tempEnd;
			}
		}
	}
	private: System::Void MyForm_Resize(System::Object^ sender, System::EventArgs^ e) {
		rectCalc();
		Refresh();
	}

	private: System::Void MyForm_Load(System::Object^ sender, System::EventArgs^ e) {
		rectCalc();
	}
	private: System::Void MyForm_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
		// ���������� ������ �������� ����
		float Wcx = ClientRectangle.Width / 2.f; 
		float Wcy = ClientRectangle.Height / 2.f;
		switch (e->KeyCode) {
		// ������� ������� �� 0.01 ������ ������ ������� ������� ������������ ������ ������
		case Keys::Q:
			// ������� ������ ��������� � (Wcx, Wcy)
			T = translate(-Wcx, -Wcy) * T;
			// ������� �� 0.01 ������ ������ ������� ������� ������������ ������ ������
			T = rotate(0.01f) * T;
			// ������� ������ ��������� �������
			T = translate(Wcx, Wcy) * T;
			break;
		// ������� ������� �� 0.01 ������ �� ������� ������� ������������ ������ ������
		case Keys::E:
			// ������� ������ ��������� � (Wcx, Wcy)
			T = translate(-Wcx, -Wcy) * T;
			// ������� �� 0.01 ������ �� ������� ������� ������������ ������ ������
			T = rotate(-0.01f) * T;
			// ������� ������ ��������� �������
			T = translate(Wcx, Wcy) * T;
			break;
		// ������� ������� �� 0.05 ������ �� ������� ������� ������������ ������ ������
		case Keys::R:
			// ������� ������ ��������� � (Wcx, Wcy)
			T = translate(-Wcx, -Wcy) * T;
			// ������� �� 0.05 ������ �� ������� ������� ������������ ������ ������
			T = rotate(-0.05f) * T;
			// ������� ������ ��������� �������
			T = translate(Wcx, Wcy) * T;
			break;
		// ������� ������� �� 0.05 ������ ������ ������� ������� ������������ ������ ������
		case Keys::Y:
			// ������� ������ ��������� � (Wcx, Wcy)
			T = translate(-Wcx, -Wcy) * T;
			// ������� �� 0.05 ������ ������ ������� ������� ������������ ������ ������
			T = rotate(0.05f) * T;
			// ������� ������ ��������� �������
			T = translate(Wcx, Wcy) * T;
			break;
		// ����� ����������� ����� �� 1 �������
		case Keys::W:
			// ����� ����� �� ���� �������
			T = translate(0.f, -1.f) * T;
			break;
		// ����� ����������� ����� �� 1 �������
		case Keys::A:
			// ����� ����� �� ���� �������
			T = translate(-1.f, 0.f) * T;
			break;
		// ����� ����������� ���� �� 1 �������
		case Keys::S:
			// ����� ���� �� ���� �������
			T = translate(0.f, 1.f) * T;
			break;
		// ����� ����������� ������ �� 1 �������
		case Keys::D:
			// ����� ������ �� ���� �������
			T = translate(1.f, 0.f) * T;
			break;
		// ����� ����������� ����� �� 1 �������
		case Keys::T:
			// ����� ����� �� ���� �������
			T = translate(0.f, -10.f) * T;
			break;
		// ����� ����������� ����� �� 1 �������
		case Keys::F:
			// ����� ����� �� ���� �������
			T = translate(-10.f, 0.f) * T;
			break;
		// ����� ����������� ���� �� 1 �������
		case Keys::G:
			// ����� ���� �� ���� �������
			T = translate(0.f, 10.f) * T;
			break;
		// ����� ����������� ������ �� 1 �������
		case Keys::H:
			// ����� ������ �� ���� �������
			T = translate(10.f, 0.f) * T;
			break;
		// ���������� � 1.1 ���
		case Keys::Z:
			// ������� ������ ��������� � (Wcx, Wcy)
			T = translate(-Wcx, -Wcy) * T;
			// ���������� � 1.1 ���
			T = scale(1.1f) * T;
			// ������� ������ ��������� �������
			T = translate(Wcx, Wcy) * T;
			break;
		// ������� �������� ���������� � 1.1 ���
		case Keys::X:
			// ������� ������ ��������� � (Wcx, Wcy)
			T = translate(-Wcx, -Wcy) * T;
			// ������� �������� ���������� � 1.1 ���
			T = scale(1.f / 1.1f) * T;
			// ������� ������ ��������� �������
			T = translate(Wcx, Wcy) * T;
			break;
		// ���������� � 1.1 ��� �� Ox
		case Keys::I:
			// ������� ������ ��������� � (Wcx, Wcy)
			T = translate(-Wcx, -Wcy) * T;
			// ���������� � 1.1 ��� �� Ox
			T = scale(1.1f, 1.f) * T;
			// ������� ������ ��������� �������
			T = translate(Wcx, Wcy) * T;
			break;
		// ������� �������� ���������� � 1.1 ��� �� Ox
		case Keys::K:
			// ������� ������ ��������� � (Wcx, Wcy)
			T = translate(-Wcx, -Wcy) * T;
			// ������� �������� ���������� � 1.1 ��� �� Ox
			T = scale(1.f / 1.1f, 1.f) * T;
			// ������� ������ ��������� �������
			T = translate(Wcx, Wcy) * T;
			break;
		// ���������� � 1.1 ��� �� Oy
		case Keys::O:
			// ������� ������ ��������� � (Wcx, Wcy)
			T = translate(-Wcx, -Wcy) * T;
			// ���������� � 1.1 ��� �� Oy
			T = scale(1.f, 1.1f) * T;
			// ������� ������ ��������� �������
			T = translate(Wcx, Wcy) * T;
			break;
		// ������� �������� ���������� � 1.1 ��� �� Oy
		case Keys::L:
			// ������� ������ ��������� � (Wcx, Wcy)
			T = translate(-Wcx, -Wcy) * T;
			// ������� �������� ���������� � 1.1  ��� �� Oy
			T = scale(1.f, 1.f / 1.1f) * T;
			// ������� ������ ��������� �������
			T = translate(Wcx, Wcy) * T;
			break;
		// ���������� ��������� ������������ Ox
		case Keys::U:
			// ������� ������ ��������� � (Wcx, Wcy)
			T = translate(-Wcx, -Wcy) * T;
			// ���������� ��������� ������������ Ox
			T = mirrorX() * T;
			// ������� ������ ��������� �������
			T = translate(Wcx, Wcy) * T;
			break;
		// ���������� ��������� ������������ Oy
		case Keys::J:
			// ������� ������ ��������� � (Wcx, Wcy)
			T = translate(-Wcx, -Wcy) * T;
			// ���������� ��������� ������������ Oy
			T = mirrorY() * T;
			// ������� ������ ��������� �������
			T = translate(Wcx, Wcy) * T;
			break;


		// ����� ���� ��������� ��������������
		case Keys::Escape:
			T = initT;
			break;
		default:
			break;
		}
		Refresh();
	}
	private: System::Void btnOpen_Click(System::Object^ sender, System::EventArgs^ e) {
		if (openFileDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
			// ���������� ����� ����� �� openFileDialog->FileName � fileName
			wchar_t fileName[1024]; // ����������, � ������� ����������� �������� ��� �����
			for (int i = 0; i < openFileDialog->FileName->Length; i++) {
				fileName[i] = openFileDialog->FileName[i];
			}
			fileName[openFileDialog->FileName->Length] = '\0';
			// ���������� � �������� �����
			std::ifstream in;
			in.open(fileName);
			if (in.is_open()) {
				// ���� ������� ������
				// ������� ��������� ������ �������
				figure.clear(); 
				// ��������� ���������� ��� ������ �� �����
				// ������� �� ��������� �� ��������� 2
				float thickness = 2; 
				// ������������ �����
				float r, g, b; 
				// �������� ������������ ����� �� ��������� (������)
				r = g = b = 0;
				std::string cmd; // ������ ��� ���������� ����� �������
				// ��������������� ������ � ������
				std::string str; // ������, � ������� ��������� ������ �����
				std::getline(in, str); // ��������� �� �������� ����� ������ ������
				while (in) { // ���� ��������� ������ ������� �������
					// ������������ ������
					if ((str.find_first_not_of(" \t\r\n") != std::string::npos) && (str[0] != '#')) {
						// ����������� ������ �� ����� � �� �����������
						std::stringstream s(str); // ��������� ����� �� ������ str
						s >> cmd;
						if (cmd == "frame") { // ������� �����������
							s >> Vx >> Vy; // ��������� ���������� �������� Vx � Vy
							aspectFig = Vx / Vy; // ���������� ����������� ������ �������
							float Wx = ClientRectangle.Width - left - right; // ������ ���� �� �����������
							float Wy = ClientRectangle.Height - top - bottom; // ������ ���� �� ���������
							float aspectForm = Wx / Wy; // ����������� ������ ���� ���������
							// ����������� ���������� ��� ���������� ��������� ����������� ������
							mat3 T1 = translate(-Vx / 2, -Vy / 2);
							// ��������������� �������� �������, �������� ������ ��������
							// ����������� ���������� ��� ���������� ��������� ����������� ������
							float S = aspectFig < aspectForm ? Wy / Vy : Wx / Vx;
							mat3 S1 = scale(S, -S);
							// ����� ����� �������� �� ������ ��������� � ������ �������
							mat3 T2 = translate(Wx / 2 + Wcx, Wcy - Wy / 2);
							// �������������� ����������� ������ ������, ������� ���������������, � ����� �������
							// � initT ��������� ��� ��� ��������������
							initT = T2 * (S1 * T1);
							T = initT;
						}
						else if (cmd == "color") { // ���� �����
							s >> r >> g >> b; // ��������� ��� ������������ �����
						}
						else if (cmd == "thickness") { // ������� �����
							s >> thickness; // ��������� �������� �������
						}
						else if (cmd == "path") { // ����� �����
							std::vector<vec2> vertices; // ������ ����� �������
							int N; // ���������� �����
							s >> N;
							std::string str1; // �������������� ������ ��� ������ �� �����
							while (N > 0) { // ���� �� ��� ����� �������
								getline(in, str1); // ��������� � str1 �� �������� ����� ��������� ������
								// ��� ��� ���� ����������, �� �� ����� ����� ��������� �� �����
									if ((str1.find_first_not_of(" \t\r\n") != std::string::npos) && (str1[0] != '#')) {
										// ����������� ������ �� ����� � �� �����������
										// ������ � ��� ���� ���������
										float x, y; // ���������� ��� ����������
										std::stringstream s1(str1); // ��� ���� ��������� ����� �� ������ str1
										s1 >> x >> y;
										vertices.push_back(vec2(x, y)); // ��������� ����� � ������
										N--; // ��������� ������� ����� ��������� ���������� �����
								}
							}
							// ��� ����� �������, ���������� ������� (path) � ������ �� � ������ figure
							figure.push_back(path(vertices, vec3(r, g, b), thickness));
						}
					}
					// ��������� ��������� ������
					getline(in, str);
				}
				Refresh();
			}
		}
	}
};
}
