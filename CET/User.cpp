#include "include/User.h"

User::User(QString firstName, QString lastName, QString userID, QString password, UserType type) : FirstName(firstName),
LastName(lastName), UserID(userID), Password(password), Type(type)
{

}

User::~User() {

}

QString User::getFirstName() {
    return FirstName;
}

QString User::getLastName() {
    return LastName;
}

/*UserType User::getUserType() {
    return Type;
}*/
