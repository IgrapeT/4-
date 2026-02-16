#include "MainForm.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace ATSProject::Forms;

[STAThreadAttribute]
int main(array<System::String^>^ args)
{
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);

    // Запуск главной формы
    Application::Run(gcnew MainForm());
    return 0;
}
