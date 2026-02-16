#pragma once
using namespace System;

namespace ATSProject {
    namespace Models {
        // Класс для хранения информации о звонке
        public ref class Call {
        public:
            int Id;
            int ClientId;
            int TariffId;
            String^ City;
            int Duration; // в минутах
            double Cost;

            // Конструкторы
            Call();
            Call(int id, int clientId, int tariffId, String^ city, int duration, double cost);

            // Методы
            String^ ToString() override;
        };
    }
}
