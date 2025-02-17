#include <iostream>
#include <string>
#include <string_view>

class Employee
{
public:
  /*
  Define any nested types at the top of your class type (nested type names must be fully defined before they can be
  used, so they are usually defined first).
  Nested types can't be forward declared (for now).
  */
  enum Type { worker, manager };

  // we can have alias here
  using IDType = int;

  // classes can also be nested
  class Printer
  {
  public:
    void print(const Employee& e) const
    {
      // Printer can't access Employee's `this` pointer so we can't print m_name and m_id directly.
      // Instead, we have to pass in an Employee object to use. Because Printer is a member of Employee, we can access
      // private members e.m_name and e.m_id directly.
      std::cout << e.m_name << " has id: " << e.m_id << '\n';
    }
  };

private:
  std::string m_name{};
  IDType m_id{};
  double m_wage{};
  Type m_type{};

public:
  Employee(std::string_view name, IDType id, double wage) : m_name{ name }, m_id{ id }, m_wage{ wage } {}

  Type getType() { return m_type; }
};

int main()
{
  const Employee john{ "John", 1, 45000 };
  const Employee::Printer p{}; // instantiate an object of the inner class
  p.print(john);

  return 0;
}