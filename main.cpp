#include "List.h"

using namespace std;


class Person {
public:
    
    /*!
     * Constructor.
     * @param name The name of the person.
     */
    Person(std::string name);
    
    /*!
     * Get the person's name.
     * @return The person's name.
     */
    std::string getName();
    
public:
    std::string _name;
};

Person::Person(std::string name) : _name(name){
    
}

std::string Person::getName() {
    return _name;
}




int main() {
    List<int> list;
    list.append(1);
    list.append(2);
    list.append(3);
    list.append(4);
    cout << "list: " << list << endl;
//    int r1 = list.removeAt(0);
//    int r2 = list.removeAt(1);
    cout << "list: " << list << endl;
    list.insert(9);
    list.insert(8);
    list.insert(7);
    cout << "list: " << list << endl;
    List<int> list2(list);
    cout << "list2: " << list2 << endl;
    List<int>::Iterator it = list2.begin();
    while(it.hasNext())
        cout << *it++ << " ";
    cout << endl;
    cout << "test ->data : " << it->data << endl;
    
    
    List<int> list3;
    list3.append(1);
    list3.insert(2);
    list3.append(3);
    cout << list3 << endl;
    
    
    const List<int> b = { 42, 3, 14 ,35,22};
    cout << b << endl;
    
    List<string> l;
    l.append("un");
    l.append("deux");
    l.append("trois");
    for (List<string>::Iterator it = l.begin(); it != l.end(); ++it)
        cout << *it << " ";
    cout << endl;
    // Affichage: un deux trois
    
    const List<int> c = { 42, 3, 14 };
        for (List<int>::ConstIterator it = --c.end(); it != --c.begin(); --it)
            cout << *it << " ";
        cout << endl;
    // Affichage: 14 3 42
    
    
    
    
    
    
    
    
    std::cout << std::endl << "Creating all the lists and objects..." << std::endl;
    List<std::string> l1;
    List<int> l2;
    List<double> l3;
    const List<int> l4({4, 3, 2, 1});
    List<char>* l5 = new List<char>;
    
    List<Person*> people;
    Person* person1 = new Person("Ludovic");
    Person* person2 = new Person("Kevin");
    Person* person3 = new Person("Gérard");
    
    std::cout << std::endl << "Testing all kind of operations..." << std::endl;
    
    std::cout << "l1: ";
    for (List<std::string>::ConstIterator it = l1.begin(); it != l1.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    
    l1.append("est");
    l1.append("un");
    l1.append("test");
    l1.insert("ceci");
    std::cout << "l1: " << l1 << std::endl;
    
    std::cout << "'ceci' se trouve à la position " << l1.find("ceci")
    << " de la liste l1." << std::endl;
    
    std::cout << "'reussite' se trouve à la position " << l1.find("reussite")
    << " de la liste l1." << std::endl;
    
    l1[2] = "une";
    l1[3] = "reussite";
    
    std::cout << "l1: " << l1 << std::endl;
    
    std::cout << "l1 contient " << l1.size() << " éléments." << std::endl;
    
    l2.append(1);
    l2.append(2);
    l2.append(3);
    std::cout << "l2: " << l2 << std::endl;
    
    l3.append(4.56);
    std::cout << "l3: " << l3 << std::endl;
    
    std::cout << "l4: " << l4 << std::endl;
    std::cout << "l4[2]: " << l4[2] << std::endl;
    
    l2 = l4;
    std::cout << "l2: " << l2 << std::endl;
    
    l2.remove(3);
    std::cout << "l2: " << l2 << std::endl;
    
    l2.removeAt(0);
    std::cout << "l2: " << l2 << std::endl;
    
    people.append(person1);
    people.insert(person2);
    people.append(person3);
    
    for (List<Person*>::Iterator p = people.begin(); p != people.end(); p++) {
        std::cout << "Person's name: " << (*p)->getName() << std::endl;
    }
    
    people.remove(person2);
    
    std::cout << "People: " << people << std::endl;
    
    for (List<int>::ConstIterator it = l4.begin(); it != l4.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    
    for (List<int>::ConstIterator it = --l4.end(); it != --l4.begin(); it--) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    
    l5->append('a');
    l5->append('b');
    l5->insert('c');
    
    for (List<char>::Iterator it = l5->begin(); it != l5->end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    
    std::cout << std::endl << "Testing all kind of exceptions..." << std::endl;
    
    try {
        people.removeAt(10);
    } catch (const std::exception& e) {
        std::cout << "Tried to remove an element out of range." << std::endl;
    }
    
    try {
        l3[l3.size()];
    } catch (const std::exception& e) {
        std::cout << "Tried to access an element out of range." << std::endl;
    }
    
    
    // Free the memory
    delete l5;
    delete person1;
    delete person2;
    delete person3;
    

    
    
    
    return EXIT_SUCCESS;
}