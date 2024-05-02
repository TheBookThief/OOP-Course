#ifndef USER_HPP
#define USER_HPP
class User
{
    public:
        const char* getUsername() const;
        const char* getEmail() const;
        const unsigned int getAge() const;

        void setUsername(const char *username);
        void setEmail(const char *email);
        void setAge(const unsigned int age);
        void setPassword(const char *password);
        void setGender(const int gender);

        bool isAdult() const; 
        unsigned int getPasswordSecurity() const;
        
        bool writeInFile(const char *filename) const;

    private:
        bool isValidEmail(const char *email) const;
        bool isSpecialSymbol(const char c) const;
        bool isDigit(const char c) const;

    private:
        enum GENDER
        {
            UNKNOWN = -1,
            MALE,
            FEMALE,
            OTHER,
            GENDER_COUNT
        };
        char username[64];
        char email[101];
        char password[32];
        unsigned int age;
        GENDER gender; 
};
#endif