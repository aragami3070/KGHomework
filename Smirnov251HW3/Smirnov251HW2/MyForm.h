#pragma once

namespace Smirnov251HW2 {
	// Number of lines
	float Vx; // ������ ������� �� �����������
	float Vy; // ������ ������� �� ���������
	float aspectFig; // ����������� ������ �������

	float ejik[] = {
		// ���
		0.5f, 3.5f, 0.5f, 3.3f, // ��� ����
		0.5f, 3.3f, 0.3f, 3.1f, // ��� ����� ����
		0.3f, 3.1f, 0.1f, 3.5f, // ��� ����� ����
		0.1f, 3.5f, 0.5f, 3.5f, // ��� ����

		// ������
		0.5f, 3.5f, 1.1f, 3.7f, // ������ �� ���� ������ ����� 
		// ������: ����: ������
		1.1f, 3.7f, 1.3f, 3.7f, // ������ ������
		1.3f, 3.7f, 1.5f, 4.1f, // ������ ������ �����
		// ������: ����
		1.1f, 3.7f, 1.5f, 3.5f, // ���� ������ ����
		1.5f, 3.5f, 1.7f, 4.1f, // ���� ������ �����
		1.7f, 4.1f, 1.3f, 4.1f, // ���� �����
		// ������
		1.1f, 3.7f, 1.3f, 4.1f, // ������ �� ������ ����� ������ ����� 
		1.3f, 4.1f, 1.7f, 4.5f, // ������ �� ����� ����� ������ ����� 
		// ������:������� ������ �����
		1.7f, 4.5f, 2.1f, 4.7f, //  �. ������� ������ �����
		2.1f, 4.7f, 1.9f, 4.1f, //  �. ������� ����� ����
		1.9f, 4.1f, 2.3f, 4.5f, //  �. ������� ������ �����
		2.3f, 4.5f, 2.1f, 3.7f, //  �. ������� ����� ����
		2.1f, 3.7f, 2.5f, 3.9f, //  �. ������� ������ �����
		2.5f, 3.9f, 2.3f, 3.3f, //  �. ������� ����� ����
		2.3f, 3.3f, 2.7f, 3.5f, //  �. ������� ������ �����
		2.7f, 3.5f, 2.5f, 3.1f, //  �. ������� ����� ����
		// ������
		2.5f, 3.1f, 2.3f, 2.9f, //  ������ �� �������/�������� ����� ����
		2.3f, 2.9f, 1.9f, 2.7f, //  ������ ����� � ����� ����� ����
		1.9f, 2.7f, 1.3f, 2.9f, //  ������ �� ���� ����� �����
		// ������: ���
		1.3f, 2.9f, 1.9f, 3.3f, //  ��� ������ �����
		1.9f, 3.3f, 1.9f, 3.5f, //  ��� �����
		// ������
		1.3f, 2.9f, 0.5f, 3.3f, //  ������ �� ��� � ���� ����� �����


		// ������� ������� �����
		1.7f, 4.5f, 1.3f, 4.3f, //  �. ������� ����� ����
		1.3f, 4.3f, 1.5f, 4.7f, //  �. ������� ������ �����
		1.5f, 4.7f, 0.9f, 4.5f, //  �. ������� ����� ����
		0.9f, 4.5f, 1.5f, 5.1f, //  �. ������� ������ �����
		1.5f, 5.1f, 1.1f, 5.5f, //  �. ������� ����� �����
		1.1f, 5.5f, 1.7f, 5.3f, //  �. ������� ������ ����
		1.7f, 5.3f, 1.9f, 5.7f, //  �. ������� ������ �����
		1.9f, 5.7f, 2.1f, 5.3f, //  �. ������� ������ ����
		2.1f, 5.3f, 2.7f, 5.7f, //  �. ������� ������ �����
		2.7f, 5.7f, 2.7f, 5.3f, //  �. ������� ������ ����
		2.7f, 5.3f, 3.3f, 5.5f, //  �. ������� ������ �����
		3.3f, 5.5f, 3.1f, 5.1f, //  �. ������� ����� ����
		3.1f, 5.1f, 3.7f, 4.9f, //  �. ������� ������ ����
		3.7f, 4.9f, 3.3f, 4.7f, //  �. ������� ����� ����
		3.3f, 4.7f, 3.9f, 4.3f, //  �. ������� ������ ����
		3.9f, 4.3f, 4.f, 4.1f, //  �. ������� ������ ����
		4.f, 4.1f, 3.7f, 4.1f, //  �. ������� �����
		3.7f, 4.1f, 3.9f, 3.5f, //  �. ������� ������ ����
		3.9f, 3.5f, 3.5f, 3.5f, //  �. ������� �����
		3.5f, 3.5f, 3.9f, 3.3f, //  �. ������� ������ ����
		3.9f, 3.3f, 3.5f, 3.1f, //  �. ������� ����� ����
		3.5f, 3.1f, 3.9f, 2.9f, //  �. ������� ������ ����
		3.9f, 2.9f, 3.5f, 2.7f, //  �. ������� ����� ����
		3.5f, 2.7f, 3.9f, 2.3f, //  �. ������� ������ ����
		3.9f, 2.3f, 3.3f, 2.1f, //  �. ������� ����� ����
		3.3f, 2.1f, 3.9f, 1.9f, //  �. ������� ������ ����
		3.9f, 1.9f, 3.5f, 1.7f, //  �. ������� ����� ����
		3.5f, 1.7f, 3.9f, 1.3f, //  �. ������� ������ ����
		3.9f, 1.3f, 3.5f, 1.1f, //  �. ������� ����� ����
		3.5f, 1.1f, 3.9f, 0.9f, //  �. ������� ������ ����
		3.9f, 0.9f, 3.5f, 0.662f, //  �. ������� ����� ����

		// �����
		2.9f, 1.1f, 3.7f, 0.5f, //  ����� � �. �������� ������ ����
		2.9f, 1.1f, 2.7f, 0.9f, //  ����� ����� � ����� ����� ����
		2.7f, 0.9f, 2.7f, 0.7f, //  ����� ����� � ����� ����
		2.7f, 0.7f, 3.7f, 0.5f, //  ����� � �. �������� ������ ����



		// ����
		2.5f, 3.1f, 2.9f, 2.7f, // ���� �� �������/������ ������ ����
		2.9f, 2.7f, 3.1f, 1.9f, // ���� ������ ����
		3.1f, 1.9f, 2.9f, 1.1f, // ���� ����� ����
		2.7f, 0.7f, 1.9f, 0.5f,  // ���� ����� ����
		// ����: ����
		1.9f, 0.5f, 1.1f, 0.3f,  // ���� ����� ����
		1.1f, 0.3f, 0.7f, 0.9f,  // ���� ����� �����
		0.7f, 0.9f, 0.9f, 1.5f,  // ���� ������ �����
		0.9f, 1.5f, 1.3f, 1.7f,  // ���� ������ �����
		1.3f, 1.7f, 1.9f, 0.5f,  // ���� ������ ����
		// ����
		1.5f, 1.3f, 1.9f, 1.5f,  // ���� ������ �����
		// ����: ����
		1.8f, 1.7f, 3.05f, 1.7f,  // ���� ����� �����
		// ����
		1.9f, 1.5f, 1.7f, 1.9f,  // ���� ����� �����
		// ����: ����
		1.7f, 1.9f, 2.5f, 1.9f,  // ���� ������
		2.1f, 1.9f, 2.1f, 2.4f,  // ���� �����
		1.7f, 2.3f, 2.5f, 2.5f,  // ���� ������
		1.7f, 2.3f, 1.5f, 2.5f,  // ���� ����� �����
		1.5f, 2.5f, 1.1f, 2.1f,  // ���� ����� ����
		1.1f, 2.1f, 1.5f, 1.7f,  // ���� ������ ����
		1.5f, 1.7f, 1.7f, 1.9f,  // ���� ������ �����
		1.9f, 2.7f, 1.1f, 2.3f,  // ���� ����� ����
		// ����
		1.7f, 2.3f, 1.9f, 2.7f,  // ���� ����� �����

		// ������
		1.3f, 2.3f, 1.04f, 2.3f,  // ������ �����
		1.1f, 2.1f, 0.9f, 2.7f,  // ������ ����� �����
		0.9f, 2.7f, 0.7f, 2.5f,  // ������ ����� ����
		0.7f, 2.5f, 1.1f, 2.1f,  // ������ ������ ����
		0.9f, 2.3f, 0.5f, 2.3f,  // ������ �����
		0.5f, 2.3f, 0.5f, 2.1f,  // ������ ����
		0.5f, 2.1f, 0.1f, 1.5f,  // ������ ����� ����
		0.1f, 1.5f, 0.1f, 1.1f,  // ������ ����
		0.1f, 1.1f, 0.5f, 0.5f,  // ������ ������ ����
		0.5f, 0.5f, 0.95f, 0.5f,  // ������ ������
		0.5f, 2.1f, 0.7f, 1.9f,  // ������ ������ ����
		0.7f, 1.9f, 0.7f, 2.2f,  // ������ �����
		0.7f, 2.2f, 0.9f, 2.3f,  // ������ ������ �����
		0.7f, 2.1f, 0.9f, 1.9f,  // ������ ������ ����
		0.9f, 1.9f, 1.3f, 1.9f,  // ������ ������ ����

	};
	unsigned int ejikLinesLength = sizeof(ejik) / sizeof(float);
	float ejikVx = 4.f; // ������ ������� �� �����������
	float ejikVy = 5.9f; // ������ ������� �� ���������
	float ejikaspectFig = ejikVx / ejikVy; // ����������� ������ �������

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
			this->SuspendLayout();
			// 
			// openFileDialog
			// 
			this->openFileDialog->Filter = L"��������� ����� (*.txt)|*.txt|��� ����� (*.*)|*.*";
			this->openFileDialog->Title = L"������� ����";
			// 
			// btnOpen
			// 
			this->btnOpen->Location = System::Drawing::Point(284, 24);
			this->btnOpen->Name = L"btnOpen";
			this->btnOpen->Size = System::Drawing::Size(75, 23);
			this->btnOpen->TabIndex = 0;
			this->btnOpen->Text = L"�������";
			this->btnOpen->UseVisualStyleBackColor = true;
			this->btnOpen->Click += gcnew System::EventHandler(this, &MyForm::btnOpen_Click);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(402, 578);
			this->Controls->Add(this->btnOpen);
			this->DoubleBuffered = true;
			this->KeyPreview = true;
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			this->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MyForm::MyForm_Paint);
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MyForm::MyForm_KeyDown);
			this->Resize += gcnew System::EventHandler(this, &MyForm::MyForm_Resize);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: bool keepAspectRatio; // �������� - ��������� �� ����������� ������ �������? 
	private: bool choosePicture; // true - �������, false - ������

	private: System::Void MyForm_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
		Graphics^ g = e->Graphics;
		// ��������� ����� �����������
		g->Clear(Color::Aquamarine);

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
				// ��������� ������� 
				g->DrawLine(pen, 
					start.x, start.y,
					end.x, end.y 
				);
				// �������� ����� �������� ������� ���������� ��������� ������ ����������
				start = end;
			}
		}
	}
	private: System::Void MyForm_Resize(System::Object^ sender, System::EventArgs^ e) {
		Refresh();
	}

	private: System::Void MyForm_Load(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void MyForm_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
		// ���������� ������ �������� ����
		float Wcx = ClientRectangle.Width / 2.f; 
		float Wcy = ClientRectangle.Height / 2.f;
		switch (e->KeyCode) {
		// ������� ������� �� 0.01 ������ ������������ ������ ������
		case Keys::Q:
			// ������� ������ ��������� � (Wcx, Wcy)
			T = translate(-Wcx, -Wcy) * T;
			// ������� �� 0.01 ������ ������������ ������ ������
			T = rotate(0.01f) * T;
			// ������� ������ ��������� �������
			T = translate(Wcx, Wcy) * T;
			break;
		// ����� ����������� ����� �� 1 �������
		case Keys::W:
			// ����� ����� �� ���� �������
			T = translate(0.f, -1.f) * T;
			break;
		// ����� ���� ��������� ��������������
		case Keys::Escape:
			// ��������� T ��������� �������
			T = mat3(1.f);
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
							float Wx = ClientRectangle.Width; // ������ ���� �� �����������
							float Wy = ClientRectangle.Height; // ������ ���� �� ���������
							float aspectForm = Wx / Wy; // ����������� ������ ���� ���������
							// ����������� ���������� ��� ���������� ��������� ����������� ������
							float S = aspectFig < aspectForm ? Wy / Vy : Wx / Vx;
							// �������� � ������������� ������� �� ��� Oy ����� ����� �����
							float Ty = S * Vy;
							// �������������� ����������� ������ ������, ������� ���������������, � ����� �������
							// � initT ��������� ��� ��� ��������������
							initT = translate(0.f, Ty) * scale(S, -S);
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
