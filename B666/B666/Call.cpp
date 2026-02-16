#include "Call.h"

namespace ATSProject {
    namespace Models {

        Call::Call() {
            Id = 0;
            ClientId = 0;
            TariffId = 0;
            City = "";
            Duration = 0;
            Cost = 0.0;
        }

        Call::Call(int id, int clientId, int tariffId, String^ city, int duration, double cost) {
            Id = id;
            ClientId = clientId;
            TariffId = tariffId;
            City = city;
            Duration = duration;
            Cost = cost;
        }

        String^ Call::ToString() {
            return String::Format("{0};{1};{2};{3};{4};{5}",
                Id, ClientId, TariffId, City, Duration, Cost);
        }
    }
}
