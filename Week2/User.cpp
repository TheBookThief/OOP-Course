#include<iostream>
#include<cstring>
#include<fstream> 

#include "User.hpp"

const char* User::getUsername() const
{
    return this->username;
}
const char* User::getEmail() const
{
    return this->email;
}
const unsigned int User::getAge() const
{
    return this->age;
}
void User::setUsername(const char *username)
{
    if(std::strlen(username) < 64)
    {
        std::strcpy(this->username, username);
        return;
    }
    std::cout<<"Invalid username"<<std::endl;
}
void User::setEmail(const char *email)
{
    if(this->isValidEmail(email))
    {
        std::strcpy(this->email, email);
        return;
    }
    std::cout<<"Invalid email"<<std::endl;
}
void User::setAge(const unsigned int age)
{
    this->age = age;
}
void User::setPassword(const char *password)
{
    if(std::strlen(password) < 32)
    {
        strcpy(this->password, password);
        return;
    }
    std::cout<<"Too long password"<<std::endl;
}
void User::setGender(const int gender)
{
    this->gender = static_cast<GENDER>(gender);
}
bool User::isAdult() const
{
    if(this->age >= 18)
        return true;
    return false;
}
unsigned int User::getPasswordSecurity() const 
{
    unsigned int cnt = 0;
    int used_digits[10] = {0};
    if(std::strlen(this->password) > 10)
        cnt++;
    for(int i=0; i<std::strlen(this->password); i++)
    {
        cnt += isSpecialSymbol(this->password[i]);
        if(isDigit(this->password[i]) && used_digits[this->password[i]-'0']==0)
        {
            used_digits[this->password[i]-'0'] = true;
            cnt++;
        }
    }
    return cnt;
}
bool User::isValidEmail(const char *email) const
{
    bool flag = true;
    bool monkey_a = false;
    for(int i=0; i<std::strlen(email); i++)
    {
        if(this->isDigit(email[i])) continue;
        if(this->isSpecialSymbol(email[i])) continue;
        if(email[i] >= 'a' && email[i] <= 'z') continue;
        if(email[i] >= 'A' && email[i] <= 'Z') continue;
        if(email[i] == '@' && monkey_a == false)
        {
            monkey_a = true;
            continue;
        }
        else if(email[i] == '@' && monkey_a == true)
            return false;
        flag = false;
        break;
    }
    return flag;
}
bool User::isDigit(const char c) const
{
    if(c >= '0' && c <= '9') 
        return true;
    return false;
}
bool User::writeInFile(const char *filename) const
{
    std::ofstream out(filename);

    if(!out.is_open())
    {
        std::cout<<"Error opening file"<<std::endl;
        return false;
    }
    out << this->username << ' '
        << this->email << ' '
        << this->password << ' '
        << this->age << '\n';
    out.close();

    return true;
}
bool User::isSpecialSymbol(const char c) const
{
    if(c == '.' || c == '_' || c == '-')
        return true;
    return false;
}
