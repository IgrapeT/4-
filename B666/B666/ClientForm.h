#pragma once
#include "Client.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace System::Drawing;
using namespace System::Text::RegularExpressions;

namespace ATSProject {
    namespace Forms {
        // Режимы работы формы
        public enum class FormMode {
            Add,    // Добавление нового клиента
            Edit    // Редактирование существующего
        };

        public ref class ClientForm : public Form {
        private:
            TextBox^ txtLastName;
            TextBox^ txtFirstName;
            TextBox^ txtPhone;
            Button^ btnOK;
            Button^ btnCancel;
            Label^ lblLastName;
            Label^ lblFirstName;
            Label^ lblPhone;
            Label^ lblTitle;

            FormMode mode;
            Models::Client^ editingClient;

        public:
            Models::Client^ ResultClient;

            // Конструктор для добавления нового клиента
            ClientForm();

            // ПЕРЕГРУЗКА КОНСТРУКТОРА для редактирования существующего
            ClientForm(Models::Client^ client);

        private:
            void InitializeComponent();
            void InitializeForMode();
            void OnPhoneKeyPress(Object^ sender, KeyPressEventArgs^ e);
            bool ValidateName(String^ name, String^ fieldName);
            bool ValidatePhone(String^ phone);
            void OnOKClick(Object^ sender, EventArgs^ e);
        };
    }
}
