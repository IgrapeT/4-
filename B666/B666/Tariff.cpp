#include "Tariff.h"

namespace ATSProject {
    namespace Models {

        Tariff::Tariff() {
            Id = 0;
            City = "";
            BaseCostPerMinute = 0.0;
            StrategyType = "Regular";
            DiscountRate = Nullable<double>();
        }

        Tariff::Tariff(int id, String^ city, double cost, String^ strategy) {
            Id = id;
            City = city;
            BaseCostPerMinute = cost;
            StrategyType = strategy;
            DiscountRate = Nullable<double>();
        }

        Tariff::Tariff(int id, String^ city, double cost, String^ strategy, double discount) {
            Id = id;
            City = city;
            BaseCostPerMinute = cost;
            StrategyType = strategy;
            DiscountRate = discount;
        }

        double Tariff::CalculateCost(int duration) {
            double cost = duration * BaseCostPerMinute;

            if (StrategyType == "Discounted" && DiscountRate.HasValue) {
                double discount = cost * (DiscountRate.Value / 100.0);
                cost -= discount;
            }

            return cost;
        }

        String^ Tariff::ToString() {
            if (DiscountRate.HasValue) {
                return String::Format("{0};{1};{2};{3};{4}",
                    Id, City, BaseCostPerMinute, StrategyType, DiscountRate.Value);
            }
            else {
                return String::Format("{0};{1};{2};{3};",
                    Id, City, BaseCostPerMinute, StrategyType);
            }
        }
    }
}
