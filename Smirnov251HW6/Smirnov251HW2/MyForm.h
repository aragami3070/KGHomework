#pragma once
#include "src/Clip.h"
#include "src/Figure.h"
#include "src/Matrix.h"
#include "src/Transform.h"
#include <fstream>
#include <sstream>
#include <vector>

namespace Smirnov251HW2 {
// Number of lines
float Vx;        // ������ ������� �� �����������
float Vy;        // ������ ������� �� ���������
float aspectFig; // ����������� ������ �������
// �������, � ������� ������������� ��� ��������������
// ������� ���������� ��������������
mat4 initT;
// ������������� ��������� �������
std::vector<model> models;
mat4 T;       // �������, � ������� ������������� ��� ��������������
vec3 S, P, u; // ���������� ����� ����������
// �����, � ������� ��������� ������ ����������
// ������� ����������� �����
float dist;         // ��������������� ���������� - ���������� ����� S � P
float fovy, aspect; // ���� ������ � ����������� ������ ���� ����������
float fovy_work, aspect_work; // ������� ���������� ��� fovy � aspect
float near, far;              // ���������� �� ���� ���������� � �� ���������
float n, f;                   // ������� ���������� ��� near � far
float l, r, t, b;             // ������� ��������������� ����������
                              // ��� �������� ��������� �����, ������,
                              // ������ � ������� ���������� � ���
enum projType { Ortho, Frustum, Perspective } pType; // ��� ���������� ��������
//

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

/// <summary>
/// ������ ��� MyForm
/// </summary>
public
ref class MyForm : public System::Windows::Forms::Form {
  public:
    MyForm(void) {
        InitializeComponent();
        //
        // TODO: �������� ��� ������������
        //
    }

  protected:
    /// <summary>
    /// ���������� ��� ������������ �������.
    /// </summary>
    ~MyForm() {
        if (components) {
            delete components;
        }
    }

  private:
    System::Windows::Forms::OpenFileDialog ^ openFileDialog;

  private:
    System::Windows::Forms::Button ^ btnOpen;

  private:
    System::Windows::Forms::Button ^ button1;

  protected:
  private:
    /// <summary>
    /// ������������ ���������� ������������.
    /// </summary>
    System::ComponentModel::Container ^ components;

#pragma region Windows Form Designer generated code
    /// <summary>
    /// ��������� ����� ��� ��������� ������������ � �� ���������
    /// ���������� ����� ������ � ������� ��������� ����.
    /// </summary>
    void InitializeComponent(void) {
        this->openFileDialog = (gcnew System::Windows::Forms::OpenFileDialog());
        this->btnOpen = (gcnew System::Windows::Forms::Button());
        this->button1 = (gcnew System::Windows::Forms::Button());
        this->SuspendLayout();
        //
        // openFileDialog
        //
        this->openFileDialog->Filter =
            L"��������� ����� (*.txt)|*.txt|��� ����� (*.*)|*.*";
        this->openFileDialog->Title = L"������� ����";
        //
        // btnOpen
        //
        this->btnOpen->Anchor =
            static_cast<System::Windows::Forms::AnchorStyles>(
                (System::Windows::Forms::AnchorStyles::Top |
                 System::Windows::Forms::AnchorStyles::Right));
        this->btnOpen->Location = System::Drawing::Point(1062, 26);
        this->btnOpen->Name = L"btnOpen";
        this->btnOpen->Size = System::Drawing::Size(75, 23);
        this->btnOpen->TabIndex = 0;
        this->btnOpen->Text = L"�������";
        this->btnOpen->UseVisualStyleBackColor = true;
        this->btnOpen->Click +=
            gcnew System::EventHandler(this, &MyForm::btnOpen_Click);
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
        this->ClientSize = System::Drawing::Size(1149, 956);
        this->Controls->Add(this->button1);
        this->Controls->Add(this->btnOpen);
        this->DoubleBuffered = true;
        this->KeyPreview = true;
        this->MinimumSize = System::Drawing::Size(155, 120);
        this->Name = L"MyForm";
        this->Text = L"MyForm";
        this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
        this->Paint += gcnew System::Windows::Forms::PaintEventHandler(
            this, &MyForm::MyForm_Paint);
        this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(
            this, &MyForm::MyForm_KeyDown);
        this->Resize +=
            gcnew System::EventHandler(this, &MyForm::MyForm_Resize);
        this->ResumeLayout(false);
    }
#pragma endregion
    // ���������� �� ������ ����
  private:
    float left = 30;
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

  private:
    System::Void rectCalc() {
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

  private:
    System::Void initWorkPars() { // ������������� ������� ���������� ������
        n = near;
        f = far;
        fovy_work = fovy;
        aspect_work = aspect;
        float Vy = 2 * near * tan(fovy / 2);
        float Vx = aspect * Vy;
        l = -Vx / 2;
        r = Vx / 2;
        b = -Vy / 2;
        t = Vy / 2;
        dist = length(P - S);
        T = lookAt(S, P, u);
    }

  private:
    System::Void MyForm_Paint(System::Object ^ sender,
                              System::Windows::Forms::PaintEventArgs ^ e) {
        Graphics ^ g = e->Graphics;
        g->Clear(Color::Aquamarine);

        Pen ^ rectPen = gcnew Pen(Color::Black, 2);
        g->DrawRectangle(rectPen, left, top, Wx, Wy);

        mat4 proj; // ������� �������� � ������������ ���������
        switch (pType) {
        case Ortho: // ������������� ��������
            proj = ortho(l, r, b, t, -n, -f);
            break;
        case Frustum: // ������������� �������� � Frustum
            proj = frustum(l, r, b, t, n, f);
            break;
        case Perspective: // ������������� �������� � Perspective
            proj = perspective(fovy_work, aspect_work, n, f);
            break;
        }
        // ������� ������������
        mat3 cdr = cadrRL(vec2(-1.f, -1.f), vec2(2.f, 2.f), vec2(Wcx, Wcy),
                          vec2(Wx, Wy));
        mat4 C =
            proj *
            T; // ������� �������� �� ������� ��������� � ������������ ���������
        for (int k = 0; k < models.size(); k++) { // ���� �� �������
            std::vector<path> figure =
                models[k].figure; // ������ ������� ��������� ������
            mat4 TM =
                C * models[k].modelM; // ������� ������ �������������� ������
            for (int i = 0; i < figure.size(); i++) {
                path lines = figure[i]; // lines - ��������� ������� �����
                Pen ^ pen = gcnew Pen(Color::FromArgb(
                    lines.color.x, lines.color.y, lines.color.z));
                pen->Width = lines.thickness;
                // ��������� ����� ������� ������� � ���������� ����������
                // �����������
                vec3 start_3D = normalize(TM * vec4(lines.vertices[0], 1.0));
                // ��������� ����� ������� ������� � ����������� ������
                vec2 start = normalize(cdr * vec3(vec2(start_3D), 1.f));
                for (int j = 1; j < lines.vertices.size();
                     j++) { // ���� �� �������� ������ (�� �������)
                    // �������� ����� ������� � ���������� ����������
                    // �����������
                    vec3 end_3D = normalize(TM * vec4(lines.vertices[j], 1.0));
                    // �������� ����� ������� � ����������� ������
                    vec2 end = normalize(cdr * vec3(vec2(end_3D), 1.f));
                    vec2 tmpEnd = end; // �������������� ���������� ����� ���
                                       // �������� �������������
                    if (clip(start, end, minX, minY, maxX,
                             maxY)) { // ���� ������� �����
                        // ����� ���������, start � end - ����� ������� �����
                        // �������
                        g->DrawLine(pen, start.x, start.y, end.x,
                                    end.y); // ��������� ������� ������
                    }
                    start = tmpEnd; // �������� ����� ������������� �������
                                    // ���������� ��������� ������ ����������
                }
            }
        }
    }

  private:
    System::Void MyForm_Resize(System::Object ^ sender, System::EventArgs ^ e) {
        rectCalc();
        Refresh();
    }

  private:
    System::Void MyForm_Load(System::Object ^ sender, System::EventArgs ^ e) {
        rectCalc();
    }

  private:
    System::Void MyForm_KeyDown(System::Object ^ sender,
                                System::Windows::Forms::KeyEventArgs ^ e) {
        switch (e->KeyCode) {
        // ����� ���� ��������� ��������������
        case Keys::Escape:
            initWorkPars();
            break;
        case Keys::D3:
            pType = Perspective;
            break;
        case Keys::D2:
            pType = Frustum;
            break;
        case Keys::D1:
            pType = Ortho;
            break;
        case Keys::W:
            if (Control::ModifierKeys == Keys::Shift) {
                T = lookAt(vec3(0, 0, -0.1), vec3(0, 0, -1.1), vec3(0, 1, 0)) * T;
            }
            else {
                T = lookAt(vec3(0, 0, -1), vec3(0, 0, -2), vec3(0, 1, 0)) * T;
            }
            break;
        case Keys::S:
            if (Control::ModifierKeys == Keys::Shift) {
                T = lookAt(vec3(0, 0, 0.1), vec3(0, 0, -0.9), vec3(0, 1, 0)) * T;
            }
            else {
                T = lookAt(vec3(0, 0, 1), vec3(0, 0, 0), vec3(0, 1, 0)) * T;
            }
            break;
        case Keys::A:
            if (Control::ModifierKeys == Keys::Shift) {
                T = lookAt(vec3(-0.1, 0, 0), vec3(-0.1, 0, -1), vec3(0, 1, 0)) * T;
            }
            else {
                T = lookAt(vec3(-1, 0, 0), vec3(-1, 0, -1), vec3(0, 1, 0)) * T;
            }
            break;
        case Keys::D:
            if (Control::ModifierKeys == Keys::Shift) {
                T = lookAt(vec3(0.1, 0, 0), vec3(0.1, 0, -1), vec3(0, 1, 0)) * T;
            }
            else {
                T = lookAt(vec3(1, 0, 0), vec3(1, 0, -1), vec3(0, 1, 0)) * T;
            }
            break;
        case Keys::R: {
            vec3 u_new = mat3(rotate(0.1, vec3(0, 0, 1))) * vec3(0, 1, 0);
            T = lookAt(vec3(0, 0, 0), vec3(0, 0, -1), u_new) * T;
            break;
        }
        case Keys::T: {
            if (Control::ModifierKeys == Keys::Shift) {
                // ������� ��������, ������������ ����� P
                mat4 M = rotateP(0.1, vec3(1, 0, 0), vec3(0, 0, -dist));
                // �������� ����������� �����
                vec3 u_new = mat3(M) * vec3(0, 1, 0);
                vec3 S_new = normalize(
                    M * vec4(0, 0, 0, 1)); // �������� ������ ���������
                // ������� � ��� � ������� ������ ��������� � ����� �����, �
                // �����������
                // ���������� - � ����� P
                T = lookAt(S_new, vec3(0, 0, -dist), u_new) * T;
            }
            else {
                // ������� �������� ������������ Ox
                mat4 M = rotate(0.1, vec3(1, 0, 0));
                // �������� ����������� �����
                vec3 u_new = mat3(M) * vec3(0, 1, 0);
                // �������� �����, � ������� ������� , �����������
                vec3 P_new = normalize(M * vec4(0, 0, -1, 1));
                T = lookAt(vec3(0, 0, 0), P_new, u_new) * T;
            }
            break;
        }
        case Keys::I:
            if (Control::ModifierKeys == Keys::Shift) {
                t -= 1;
            }
            else {
                t += 1;
            }
            break;
        case Keys::J:
            if (Control::ModifierKeys == Keys::Shift) {
                l -= 1;
            }
            else {
                l += 1;
            }
            break;
        default:
            break;
        }
        Refresh();
    }

  private:
    System::Void btnOpen_Click(System::Object ^ sender, System::EventArgs ^ e) {
        if (openFileDialog->ShowDialog() ==
            System::Windows::Forms::DialogResult::OK) {
            // � �������� ������� ������ ������ OK
            // ���������� ����� ����� �� openFileDialog->FileName � fileName
            wchar_t fileName[1024]; // ����������, � ������� �����������
                                    // �������� ��� �����
            for (int i = 0; i < openFileDialog->FileName->Length; i++) {
                fileName[i] = openFileDialog->FileName[i];
            }
            fileName[openFileDialog->FileName->Length] = '\0';

            // ���������� � �������� �����
            std::ifstream in;
            in.open(fileName);
            if (in.is_open()) {
                // ���� ������� ������
                models.clear(); // ������� ��������� ������ ��������
                // ��������� ���������� ��� ������ �� �����
                mat4 M = mat4(1.f); // ������� ��� ��������� ��������� �������
                mat4 initM; // ������� ��� ���������� �������������� �������
                            // �������
                std::vector<mat4> transforms; // ���� ������ ��������������
                std::vector<path> figure; // ������ ������� ���������� �������
                float thickness = 2;      // ������� �� ��������� �� ��������� 2
                float r, g, b;            // ������������ �����
                r = g = b =
                    0; // �������� ������������ ����� �� ��������� (������)
                std::string cmd; // ������ ��� ���������� ����� �������
                // ��������������� ������ � ������
                std::string str; // ������, � ������� ��������� ������ �����
                std::getline(in,
                             str); // ��������� �� �������� ����� ������ ������
                while (in) {       // ���� ��������� ������ ������� �������
                    // ������������ ������
                    if ((str.find_first_not_of(" \t\r\n") !=
                         std::string::npos) &&
                        (str[0] != '#')) {
                        // ����������� ������ �� ����� � �� �����������
                        std::stringstream s(
                            str); // ��������� ����� �� ������ str
                        s >> cmd;
                        if (cmd == "camera") { // ��������� ������
                            s >> S.x >> S.y >>
                                S.z; // ���������� ����� ����������
                            s >> P.x >> P.y >>
                                P.z; // �����, � ������� ��������� ������
                                     // ����������
                            s >> u.x >> u.y >> u.z; // ������ ����������� �����
                        }
                        else if (cmd == "screen") { // ��������� ���� ����������
                            s >> fovy_work >> aspect >> near >>
                                far; // ��������� �������
                            fovy =
                                fovy_work / 180.f *
                                Math::PI; // ������� ���� �� �������� � ��������
                        }
                        else if (cmd == "color") { // ���� �����
                            s >> r >> g >>
                                b; // ��������� ��� ������������ �����
                        }
                        else if (cmd == "thickness") { // ������� �����
                            s >> thickness; // ��������� �������� �������
                        }
                        else if (cmd == "path") {       // ����� �����
                            std::vector<vec3> vertices; // ������ ����� �������
                            int N;                      // ���������� �����
                            s >> N;
                            std::string str1; // �������������� ������ ���
                                              // ������ �� �����
                            while (N > 0) {   // ���� �� ��� ����� �������
                                // ��������� � str1 �� ��������
                                // ����� ��������� ������
                                std::getline(in, str1);
                                // ��� ��� ���� ����������, �� �� ����� �����
                                // ��������� �� �����
                                if ((str1.find_first_not_of(" \t\r\n") !=
                                     std::string::npos) &&
                                    (str1[0] != '#')) {
                                    // ����������� ������ �� ����� � ��
                                    // ����������� ������ � ��� ���� ���������
                                    float x, y, z; // ���������� ��� ����������
                                    std::stringstream s1(
                                        str1); // ��� ���� ��������� ����� ��
                                               // ������ str1
                                    s1 >> x >> y >> z;
                                    vertices.push_back(vec3(
                                        x, y, z)); // ��������� ����� � ������
                                    N--; // ��������� ������� ����� ���������
                                         // ���������� �����
                                }
                            }
                            // ��� ����� �������, ���������� ������� (path) �
                            // ������ �� � ������ figure
                            figure.push_back(
                                path(vertices, vec3(r, g, b), thickness));
                        }
                        else if (cmd ==
                                 "model") { // ������ �������� ������ �������
                            float mVcx, mVcy, mVcz, mVx, mVy,
                                mVz; // ��������� ������� model
                            s >> mVcx >> mVcy >> mVcz >> mVx >> mVy >>
                                mVz; // ��������� �������� ����������
                            float S = mVx / mVy < 1 ? 2.f / mVy : 2.f / mVx;
                            // ����� ����� �������� �� ������ ��������� � ������
                            // ������� ����� �������� �������� ���������������
                            initM =
                                scale(S, S, S) * translate(-mVcx, -mVcy, -mVcz);
                            figure.clear();
                        }
                        else if (cmd == "figure") { // ������������ ����� ������
                            models.push_back(model(figure, M * initM));
                        }
                        else if (cmd == "translate") { // �������
                            float Tx, Ty,
                                Tz; // ��������� �������������� ��������
                            s >> Tx >> Ty >> Tz; // ��������� ���������
                            M = translate(Tx, Ty, Tz) *
                                M; // ��������� ������� � ������ ��������������
                        }
                        else if (cmd == "scale") {  // ���������������
                            float S;                // �������� ���������������
                            s >> S;                 // ��������� ��������
                            M = scale(S, S, S) * M; // ��������� ���������������
                                                    // � ������ ��������������
                        }
                        else if (cmd == "rotate") { // �������
                            float theta;            // ���� �������� � ��������
                            float nx, ny, nz;       // ���������� �������������
                                                    // ������� ��� ��������
                            s >> theta >> nx >> ny >> nz; // ��������� ���������
                            // ��������� �������� � ������ ��������������
                            M = rotate(theta / 180.f * Math::PI,
                                       vec3(nx, ny, nz)) *
                                M;
                        }
                        else if (cmd ==
                                 "pushTransform") { // ���������� ������� � ����
                            transforms.push_back(M); // ��������� ������� � ����
                        }
                        else if (cmd ==
                                 "popTransform") { // ����� � ������� �� �����
                            M = transforms
                                    .back(); // �������� ������� ������� �����
                            transforms
                                .pop_back(); // ���������� ������� �� �����
                        }
                    }
                    // ��������� ��������� ������
                    std::getline(in, str);
                }
                initWorkPars();
                Refresh();
            }
        }
    }
};
} // namespace Smirnov251HW2
