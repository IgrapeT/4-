#include "Client.h"

namespace ATSProject {
    namespace Models {

        Client::Client() {
            Id = 0;
            LastName = "";
            FirstName = "";
            PhoneNumber = "";
        }

        Client::Client(int id, String^ lastName, String^ firstName, String^ phone) {
            Id = id;
            LastName = lastName;
            FirstName = firstName;
            PhoneNumber = phone;
        }

        String^ Client::GetFullName() {
            return LastName + " " + FirstName;
        }

        String^ Client::ToString() {
            return String::Format("{0};{1};{2};{3}", Id, LastName, FirstName, PhoneNumber);
        }
    }
}
