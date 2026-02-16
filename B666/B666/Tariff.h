#pragma once
using namespace System;

namespace ATSProject {
    namespace Models {
        // Класс для хранения информации о тарифе
        public ref class Tariff {
        public:
            int Id;
            String^ City;
            double BaseCostPerMinute;
            String^ StrategyType; // "Regular" или "Discounted"
            Nullable<double> DiscountRate;

            // Конструкторы
            Tariff();
            Tariff(int id, String^ city, double cost, String^ strategy);
            Tariff(int id, String^ city, double cost, String^ strategy, double discount);

            // Методы
            double CalculateCost(int duration);
            String^ ToString() override;
        };
    }
}
