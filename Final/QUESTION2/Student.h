#ifndef __STUDENT_H__
#define __STUDENT_H__

#include <string>
#include <fstream>

class Student
{
  private:
    std::string _name;
    int _sid;
  public:
    Student(std::string name,int sid) : _name(name),_sid(sid) { }

    /* Accessors */
    int sid() const { return _sid; }
    std::string name() const { return _name; }
    bool operator==(const Student &rhs) const { return rhs._sid == this->_sid; }

    friend std::ostream& operator<<(std::ostream&,const Student&);
};

#endif // __STUDENT_H__