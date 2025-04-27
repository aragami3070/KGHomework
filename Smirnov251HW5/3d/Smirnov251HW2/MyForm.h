#pragma once
#include "src/Clip.h"
#include "src/Matrix.h"
#include "src/Transform.h"
#include <cmath>
#include <vector>

namespace Smirnov251HW2 {

// Под начальные значения
vec3 Vc; // Координаты левого нижнего угла
vec3 V;  // Размеры прямогульника в пространстве гарфика
// Под рабочие значения
vec3 Vc_work; // Координаты левого нижнего угла
vec3 V_work;  // Размеры прямогульника в пространстве гарфика

// Матрица, в которой накапливаются все преобразования
// Первоначально единичная матрица
mat4 T = mat4(1.f);
// Матрица начального преобразования
mat4 initT;

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

/// <summary>
/// Сводка для MyForm
/// </summary>
public
ref class MyForm : public System::Windows::Forms::Form {
  public:
    MyForm(void) {
        InitializeComponent();
        //
        // TODO: добавьте код конструктора
        //
    }

  protected:
    /// <summary>
    /// Освободить все используемые ресурсы.
    /// </summary>
    ~MyForm() {
        if (components) {
            delete components;
        }
    }

  private:
    System::Windows::Forms::OpenFileDialog ^ openFileDialog;

  protected:
  private:
    /// <summary>
    /// Обязательная переменная конструктора.
    /// </summary>
    System::ComponentModel::Container ^ components;

#pragma region Windows Form Designer generated code
    /// <summary>
    /// Требуемый метод для поддержки конструктора — не изменяйте
    /// содержимое этого метода с помощью редактора кода.
    /// </summary>
    void InitializeComponent(void) {
        this->openFileDialog = (gcnew System::Windows::Forms::OpenFileDialog());
        this->SuspendLayout();
        //
        // openFileDialog
        //
        this->openFileDialog->Filter =
            L"Текстовые файлы (*.txt)|*.txt|Все файлы (*.*)|*.*";
        this->openFileDialog->Title = L"Открыть файл";
        //
        // MyForm
        //
        this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
        this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
        this->ClientSize = System::Drawing::Size(390, 249);
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
  private:
    // Расстояния до границ окна
    float left = 30, right = 100, top = 20, bottom = 50;
    // Диапазон изменения координат x, пределы изменения x
    float minX = left, maxX;
    // Диапазон изменения координат y, пределы изменения y
    float minY = top, maxY;
    // Координаты левого нижнего угла прямоугольника
    float Wcx = left, Wcy;
    // Ширина и высота прямоугольника
    float Wx, Wy;
    // ширина и высота области вывода одной линии графика
    float Wx_work, Wy_work;
    // доля Wx_work, Wy_work от Wx, Wy соответственно
    float Wx_part = 0.6, Wy_part = 0.6;

    // координаты левого нижнего угла самого дальнего
    // прямоугольника
    float Wcx_work, Wcy_work;
    // количество рабочих прямоугольников
    float Wz_work;
    // количество секций координатной сетки по осям
    int numXsect = 5, numYsect = 5, numZsect = 5;

  private:
    System::Void rectCalc() {
        // Диапазон изменения координат x, пределы изменения x
        maxX = ClientRectangle.Width - right;
        // Диапазон изменения координат y, пределы изменения y
        maxY = ClientRectangle.Height - bottom;
        // Координаты левого нижнего угла прямоугольника
        Wcy = maxY;
        // Ширина прямоугольника
        Wx = maxX - left;
        // Высота прямоугольника
        Wy = maxY - top;
        // вычисление ширины и высоты
        Wx_work = Wx_part * Wx;
        // рабочего прямоугольника
        Wy_work = Wy_part * Wy;
        // вычисление координат нижнего левого
        Wcx_work = maxX - Wx_work;
        // угла самого дальнего рабочего прямоугольника
        Wcy_work = minY + Wy_work;
        // количество рабочих прямоугольников
        Wz_work = Wcy - Wcy_work;
    }

  private:
    System::Void worldRectCalc() {
        // Пересчитываем значение Vc_work
        Vc_work = normalize(T * vec4(Vc, 1.f));
        // Пересчитываем значение V_work
        V_work = mat3(T) * V;
    }

  private:
    float f(float x, float z) {
        return x * std::sin(sqrtf(x * x + z * z));
    }

  private:
    bool f_exists(float x, float z, float delta) {
        return true;
    }

  private:
    System::Void MyForm_Paint(System::Object ^ sender,
                              System::Windows::Forms::PaintEventArgs ^ e) {
        Graphics ^ g = e->Graphics;
        // Заполнить форму аквамарином
        g->Clear(Color::Aquamarine);

        Pen ^ rectPen = gcnew Pen(Color::Black, 2);
        g->DrawRectangle(rectPen,
                         left, // От левого
                         top,  // верхнего угла отмеряем вниз и вправо
                         Wx,   // Ширина
                         Wy    // Высота
        );

        Pen ^ gridPen = gcnew Pen(Color::Black, 1);
        SolidBrush ^ drawBrush = gcnew SolidBrush(Color::Black);
        System::Drawing::Font ^ drawFont =
            gcnew System::Drawing::Font("Arial", 8);
        // расстояние между линиями сетки по x
        float gridStep_x = Wx_work / numXsect;

        // расстояние между линиями сетки
        // по x в мировых координатах
        float grid_dX = V_work.x / numXsect;

        // значение соответствующее первой линии сетки
        float tick_x = Vc_work.x;

        // цикл по количеству линий
        for (int i = 0; i <= numXsect; i++) {
            // нижняя координата x i-й диагональной линии
            float tmpXCoord_d = Wcx + i * gridStep_x;
            // координата x i-й вертикальной линии
            float tmpXCoord_v = Wcx_work + i * gridStep_x;
            // i-я диагональная линия
            g->DrawLine(gridPen, tmpXCoord_d, Wcy, tmpXCoord_v, Wcy_work);
            // i-я вертикальная линия
            g->DrawLine(gridPen, tmpXCoord_v, Wcy_work, tmpXCoord_v, minY);

            // если линия не крайняя
            if (i > 0 && i < numXsect) {
                // выводим текст в нижней точке диагональной линии
                g->DrawString(tick_x.ToString("F4"), drawFont, drawBrush,
                              tmpXCoord_d, Wcy);
            }
            // вычисляем значение, соответствующее следующей линии
            tick_x += grid_dX;
        }

        // расстояние между вертикальными линиями
        // сетки по горизонтали
        gridStep_x = (Wx - Wx_work) / numZsect;

        // расстояние между горизонтальными линиями
        // сетки по вертикали
        float gridStep_y = Wz_work / numZsect;
        // расстояние между линиями сетки
        // по $z$ в мировых координатах
        float grid_dZ = V_work.z / numZsect;
        // значение, соответствующее первой линии сетки
        float tick_z = Vc_work.z;
        // цикл по количеству линий
        for (int i = 0; i <= numZsect; i++) {
            // координата x вертикальных линий
            float tmpXCoord_v = Wcx_work - i * gridStep_x;
            // координата y горизонтальных линий
            float tmpYCoord_g = Wcy_work + i * gridStep_y;
            // вторая координата x горизонтальных линий
            float tmpXCoord_g = tmpXCoord_v + Wx_work;
            // i-я вертикальная линия
            g->DrawLine(gridPen, tmpXCoord_v, tmpYCoord_g, tmpXCoord_v,
                        tmpYCoord_g - Wy_work);
            // i-я горизонтальная линия
            g->DrawLine(gridPen, tmpXCoord_v, tmpYCoord_g, tmpXCoord_g,
                        tmpYCoord_g);
            // если линия не крайняя
            if (i > 0 && i < numZsect) {
                // выводим текст в правой точке
                // горизонтальной линии
                g->DrawString(tick_z.ToString("F4"), drawFont, drawBrush,
                              tmpXCoord_g, tmpYCoord_g);
            }
            // вычисляем значение, соответствующее следующей линии
            tick_z += grid_dZ;
        }
        gridStep_y = Wy_work / numYsect;
        float grid_dY = V_work.y / numYsect;
        float tick_y = -Vc_work.y;
        // цикл по количеству линий
        for (int i = 0; i <= numYsect; i++) {
            // координата y горизонтальных линий
            float tmpYCoord_g = Wcy_work + i * gridStep_y;

            // i-я горизонтальная линия
            g->DrawLine(gridPen, Wcx_work, tmpYCoord_g - Wy_work,
                        Wcx_work + Wx_work, tmpYCoord_g - Wy_work);
            // i-я диагональная линия
            g->DrawLine(gridPen, Wcx_work, tmpYCoord_g - Wy_work, Wcx,
                        Wz_work - Wy_work + tmpYCoord_g);
            // если линия не крайняя
            if (i > 0 && i < numYsect) {
                // выводим текст в правой точке горизонтальной линии
                g->DrawString(tick_y.ToString("F4"), drawFont, drawBrush, maxX,
                              tmpYCoord_g - Wy_work);
            }
            // вычисляем значение, соответствующее следующей линии
            tick_y -= grid_dY;
        }
        Pen ^ pen = gcnew Pen(Color::Blue, 1);
        // шаг по x в мировых координатах
        float deltaX = V_work.x / Wx_work;
        // шаг по z в мировых координатах
        float deltaZ = V_work.z / Wz_work;
        // шаг прямоугольников по x в координатах экрана
        float deltaWcx = (Wcx_work - Wcx) / Wz_work;
        // координата z наиболее удаленных точек графика
        float z = Vc_work.z;

        // координаты левого нижнего угла рабочего прямоугольника
        // (инициализация)
        float Wcx_w = Wcx_work, Wcy_w = Wcy_work;
        // пока не перебрали все прямоугольники
        while (Wcy_w <= Wcy) {
            // точка начала отрезка в координатах экрана
            vec2 start;
            // переменные для координат точки в мировой СК
            float x, y;
            // для начальной точки первого отрезка
            // устанавливаем координату x
            start.x = Wcx_w;
            // координата x начальной точки первого отрезка в
            // мировых координатах
            x = Vc_work.x;

            bool hasStart = f_exists(x, z, deltaX);

            if (hasStart) {
                // координата y начальной точки в мировых координатах
                y = f(x, z);
                // вычисляем соответствующее значение в координатах экрана
                start.y = Wcy_w - (y - Vc_work.y) / V_work.y * Wy_work;
            }
            // максимальное значение x в рабочем прямоугольнике
            float maxX = Wcx_w + Wx_work;

            while (start.x < maxX) {
                // точка конца отрезка в координатах экрана
                vec2 end;
                // высота точки в прямоугольнике (доля общей высоты)
                float deltaY;
                // компоненты цвета отрезка
                float red, green, blue;
                // координата x отличается на единицу
                end.x = start.x + 1.f;
                // координата x конечной точки отрезка в мировых
                // координатах
                x += deltaX;

                bool hasEnd = f_exists(x, z, deltaX);

                if (hasEnd) {
                    // координата y начальной точки в мировых
                    // координатах
                    y = f(x, z);
                    // вычисляем соответствующее значение в координатах экрана
                    deltaY = (y - Vc_work.y) / V_work.y;
                    end.y = Wcy_w - deltaY * Wy_work;
                }
                vec2 tmpEnd = end;
                bool visible =
                    hasStart && hasEnd &&
                    clip(start, end, Wcx_w - Wx_work, 0,
                         Wcx_w + Wx_work, Wcy_w + Wy_work);
                // если отрезок видим
                if (visible) {
                    // после отсечения, start и end - концы видимой части
                    // отрезка
                    // Нормализуем значение высоты точки на случай, если отрезок
                    // отсекался
                    if (deltaY > 1.f) {
                        deltaY = 1.f;
                    }
                    if (deltaY < 0.f) {
                        deltaY = 0.f;
                    }
                    // предварительное вычисление произведения
                    green = 510.f * deltaY;
                    // если точка ниже середины области видимости
                    if (deltaY < 0.5) {
                        // компонента зеленого уже вычислена
                        // синий дополняет зеленый
                        blue = 255.f - green;
                        // красный равен нулю
                        red = 0.f;
                    }
                    // если точка не ниже середины
                    else {
                        // синий равен нулю
                        blue = 0.f;
                        // вычисляем красный и зеленый
                        red = green - 255.f;
                        // с использованием вычисленного произведения
                        green = 510.f - green;
                    }
                    // меняем цвет пера
                    pen->Color = Color::FromArgb(red, green, blue);
                    // отрисовка видимых частей
                    g->DrawLine(pen, start.x, start.y, end.x, end.y);
                }
                // конечная точка неотсеченного отрезка становится начальной
                // точкой следующего
                start = tmpEnd;
                hasStart = hasEnd;
            }
            // переходим к следующему прямоугольнику, он будет
            // ниже на один пиксел
            Wcy_w += 1.f;
            // и левее на некоторое значение
            Wcx_w -= deltaWcx;
            // вычисляем соответствующее значение z для очередного
            // прямоугольника
            z += deltaZ;
        }
    }

  private:
    System::Void MyForm_Resize(System::Object ^ sender, System::EventArgs ^ e) {
        rectCalc();
        Refresh();
    }

  private:
    System::Void MyForm_Load(System::Object ^ sender, System::EventArgs ^ e) {
        // Задаем квадрат со стороной 4, с центром в начале координат
        Vc = vec3(-2.f, -2.f, -2.f);
        V = vec3(4.f, 4.f, 4.f);

        initT = mat4(1.f);
        T = initT;

        rectCalc();
        worldRectCalc();
    }

  private:
    System::Void MyForm_KeyDown(System::Object ^ sender,
                                System::Windows::Forms::KeyEventArgs ^ e) {
        // координаты центра
        float Wcx = ClientRectangle.Width / 2.f;
        // текущего окна
        float Wcy = ClientRectangle.Height / 2.f;
        // координаты центра прямоугольника
        // в мировой системе координат
        float centerX = Vc_work.x + V_work.x / 2;
        float centerY = Vc_work.y + V_work.y / 2;
        float centerZ = Vc_work.z + V_work.z / 2;
        switch (e->KeyCode) {
        // Сброс всех сделанных преобразований
        case Keys::Escape:
            T = initT;
            break;
        case Keys::A:
            // сдвиг графика вправо на один пиксел
            T = translate(-V_work.x / Wx, 0.f, 0.f) * T;
            break;
        case Keys::D:
            // сдвиг графика влево на один пиксел
            T = translate(V_work.x / Wx, 0.f, 0.f) * T;
            break;
        case Keys::W:
            // сдвиг графика вправо на один пиксел
            T = translate(0.f, 0.f, -V_work.z / sqrt(Wx * Wx + Wy * Wy)) * T;
            break;
        case Keys::S:
            // сдвиг графика вправо на один пиксел
            T = translate(0.f, 0.f, V_work.z / sqrt(Wx * Wx + Wy * Wy)) * T;
            break;
        case Keys::R:
            // сдвиг графика влево на один пиксел
            T = translate(0.f, -V_work.y / Wy, 0.f) * T;
            break;
        case Keys::F:
            // сдвиг графика влево на один пиксел
            T = translate(0.f, V_work.y / Wy, 0.f) * T;
            break;
        case Keys::Z:
            // перенос начала координат в центр
            T = translate(-centerX, -centerY, -centerZ) * T;
            // масштабирование относительно начала координат
            T = scale(1.1, 1.1, 1.1) * T;
            // возврат позиции начала координат
            T = translate(centerX, centerY, centerZ) * T;
            break;
        case Keys::X:
            // перенос начала координат в центр
            T = translate(-centerX, -centerY, -centerZ) * T;
            // масштабирование относительно начала координат
            T = scale(1 / 1.1, 1 / 1.1, 1 / 1.1) * T;
            // возврат позиции начала координат
            T = translate(centerX, centerY, centerZ) * T;
            break;
        case Keys::Q:
            Wx_part = std::min(0.9, Wx_part * 1.1);
            break;
        case Keys::E:
            Wx_part = std::max(0.2, Wx_part / 1.1);
            break;
        case Keys::C:
            Wy_part = std::min(0.9, Wy_part * 1.1);
            break;
        case Keys::V:
            Wy_part = std::max(0.2, Wy_part / 1.1);
            break;
        case Keys::T:
            // перенос начала координат в центр
            T = translate(-centerX, -centerY, -centerZ) * T;
            // масштабирование относительно начала координат
            T = scale(1.1, 1, 1) * T;
            // возврат позиции начала координат
            T = translate(centerX, centerY, centerZ) * T;
            break;
        case Keys::G:
            // перенос начала координат в центр
            T = translate(-centerX, -centerY, -centerZ) * T;
            // масштабирование относительно начала координат
            T = scale(1 / 1.1, 1, 1) * T;
            // возврат позиции начала координат
            T = translate(centerX, centerY, centerZ) * T;
            break;
        case Keys::Y:
            // перенос начала координат в центр
            T = translate(-centerX, -centerY, -centerZ) * T;
            // масштабирование относительно начала координат
            T = scale(1, 1.1, 1) * T;
            // возврат позиции начала координат
            T = translate(centerX, centerY, centerZ) * T;
            break;
        case Keys::H:
            // перенос начала координат в центр
            T = translate(-centerX, -centerY, -centerZ) * T;
            // масштабирование относительно начала координат
            T = scale(1, 1 / 1.1, 1) * T;
            // возврат позиции начала координат
            T = translate(centerX, centerY, centerZ) * T;
            break;
        case Keys::U:
            // перенос начала координат в центр
            T = translate(-centerX, -centerY, -centerZ) * T;
            // масштабирование относительно начала координат
            T = scale(1, 1, 1.1) * T;
            // возврат позиции начала координат
            T = translate(centerX, centerY, centerZ) * T;
            break;
        case Keys::J:
            // перенос начала координат в центр
            T = translate(-centerX, -centerY, -centerZ) * T;
            // масштабирование относительно начала координат
            T = scale(1, 1, 1 / 1.1) * T;
            // возврат позиции начала координат
            T = translate(centerX, centerY, centerZ) * T;
            break;
        case Keys::D1:
            numXsect++;
            break;
        case Keys::D2:
            numXsect = std::max(2, numXsect - 1);
            break;
        case Keys::D3:
            numYsect++;
            break;
        case Keys::D4:
            numYsect = std::max(2, numYsect - 1);
        case Keys::D5:
            numZsect++;
            break;
        case Keys::D6:
            numZsect = std::max(2, numZsect - 1);
            break;
        default:
            break;
        }
        worldRectCalc();
        Refresh();
    }
};
} // namespace Smirnov251HW2
