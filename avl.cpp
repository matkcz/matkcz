#include "avl_tree.h"

int main()
{
    tree t;

    /*cout << t.depth() << endl;
    t.display();
    t.wide_print();
    cout << t.find("a") << endl;
    cout << t.find(5) << endl;
    cout << t.maxCount() << endl;

    t.display();
    t.wide_print();
    cout << t.empty() << endl;*/

    t.insert(40, "a");
    t.insert(48, "b");
    t.insert(30, "c");
    t.insert(22, "d");
    t.insert(14, "e");
    t.insert(50, "f");
    t.insert(565, "g");
    t.insert(300, "h");
    t.insert(222, "i");
    t.insert(144, "j");
    t.insert(144, "k");
    t.display();
    t.wide_print();


    t.remove(666);
    t.display();
    t.wide_print();

    t.remove("aaa");
    t.display();
    t.wide_print();

    t.remove(300);
    t.display();
    t.wide_print();

    t.remove("g");
    t.display();
    t.wide_print();

    t.remove(30);
    t.wide_print();

    cout << t.find("j") << endl;
    cout << t.find(222) << endl;
}