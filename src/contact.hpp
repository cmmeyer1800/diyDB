#include <string>
#include <ostream>

struct Contact{
    std::string name;
    std::string phone;

    Contact(){
        name = "UNDEFINED";
        phone = "UNDEFINED";
    }

    Contact(std::string newName, std::string newPhone){
        name = newName;
        phone = newPhone;
    }

    friend std::ostream &operator<<(std::ostream &output, const Contact &con){
        output << "Name: " << con.name << "|" << "Phone: " << con.phone << std::endl;
        return output;
    }
};