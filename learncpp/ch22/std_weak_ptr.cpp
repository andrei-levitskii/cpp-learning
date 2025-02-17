#include <iostream>
#include <memory> // for std::shared_ptr and std::weak_ptr
#include <string>

class Person
{
  std::string m_name;
  std::weak_ptr<Person> m_partner; // note: This is a std::weak_ptr

public:
  Person(const std::string& name) : m_name(name) { std::cout << m_name << " created\n"; }
  ~Person() { std::cout << m_name << " destroyed\n"; }

  friend bool partnerUp(std::shared_ptr<Person>& p1, std::shared_ptr<Person>& p2)
  {
    if (!p1 || !p2) return false;

    p1->m_partner = p2;
    p2->m_partner = p1;

    std::cout << p1->m_name << " is now partnered with " << p2->m_name << '\n';

    return true;
  }

  std::shared_ptr<Person> getPartner() const
  {
    // use lock() to convert weak_ptr to shared_ptr, weak_ptr can't be used on it's own (`->`, etc). It's ok that
    // `partner` ptr is created on the caller side, it will be destroyed and won't do harm
    return m_partner.lock();
  }
  const std::string& getName() const { return m_name; }
};

int main()
{
  auto lucy{ std::make_shared<Person>("Lucy") };
  auto ricky{ std::make_shared<Person>("Ricky") };

  partnerUp(lucy, ricky);

  auto partner = ricky->getPartner(); // get shared_ptr to Ricky's partner
  std::cout << ricky->getName() << "'s partner is: " << partner->getName() << '\n';

  /*
  Unlike std::shared_ptr, std::weak_ptr is not considered when determining whether the resource should be destroyed.

  std::weak_ptr::expired() can be used to check if the object was destroyed. if .expired() is true .lock() will return
  shared_ptr to nullptr
  */

  return 0;
}