#pragma once
using namespace System;

namespace ATSProject {
    namespace Models {
        // Класс для хранения информации о клиенте
        public ref class Client {
        public:
            int Id;
            String^ LastName;
            String^ FirstName;
            String^ PhoneNumber;

            // Конструкторы
            Client();
            Client(int id, String^ lastName, String^ firstName, String^ phone);

            // Методы
            String^ GetFullName();
            String^ ToString() override;
        };
    }
}
