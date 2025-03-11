#include "src/Matrix.h"
#include "src/Transform.h"
#include "src/Figure.h"
#include <vector>
#include <fstream>
#include <sstream>
#include "MyForm.h"

using namespace System;
using namespace System::Windows::Forms;

[STAThreadAttribute]
void Main(array<String^>^ args) {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	Smirnov251HW2::MyForm form;
	Application::Run(% form);
}
