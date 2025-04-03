#ifndef USER_H
#define USER_H

#include <iostream>
#include <string>

class User {
public:
    User(const std::string& name);
    ~User();
    
    User(const User& other);
    User& operator=(const User& other);
    User(User&& other) = delete;
    User& operator=(User&& other) = delete;

    void add_friend(const std::string& name);
    std::string get_name() const;
    size_t size() const;
    void set_friend(size_t index, const std::string& name);

    User& operator+=(User& other); 
    bool operator<(const User& other) const;
    bool operator==(const User& other) const;
    bool operator!=(const User& other) const;
    
    friend std::ostream& operator<<(std::ostream& os, const User& user);

    std::string& operator[](size_t index);
    const std::string& operator[](size_t index) const;

private:
    std::string _name;
    std::string* _friends;
    size_t _size;
    size_t _capacity;
};

#endif // USER_H