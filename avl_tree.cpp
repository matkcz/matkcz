#include "avl_tree.h"
#include <iostream>
#include <stack>
#include <queue>
#include <iomanip>

using namespace std;

    //private

    bool tree::empty()
    {
        return root == nullptr;
    }

    void tree::makeEmpty(node* t)
    {
        if (t == nullptr)
            return;
        makeEmpty(t->left); //vyprázdní levý podstrom rekursivně
        makeEmpty(t->right); //vyprázdní pravý podstrom rekursivně
        delete t;
    }

    int tree::height(node* t)
    {
        if (t != nullptr)
        {
            return t->height;  //returnuje hodnotu výšky daného vrcholu
        }
        else
        {
            return -1;
        }
    }

    //int tree::getBalance(node* t) //měla nahradit porovnávání výšek u ostatních funkcí, ale nefungovalo mi to všude, tak jsem se obešel bez toho
    //{
    //    if (t == nullptr)
    //        return 0;
    //    else
    //        return height(t->left) - height(t->right);  //returne rozdíl výšky pravého a levého podstromu
    //}

    tree::node* tree::singleRightRotate(node*& t)
    {
        node* u = t->left; //pomocný vrchol u se nastaví na levý od vrcholu t
        t->left = u->right; //levý potomek od t se nastaví na pravý potomek od u
        u->right = t; //pravý potomek od u se nastaví na t
        t->height = max(height(t->left), height(t->right)) + 1; //změna nejvyšší výšky vrcholu t na správnou výšku
        u->height = max(height(u->left), t->height) + 1; //změna nejvyšší výšky vrcholu u na správnou výšku
        return u;
    }

    tree::node* tree::singleLeftRotate(node*& t) //to samé jako u předchozího, jen prohozené strany
    {
        node* u = t->right;
        t->right = u->left;
        u->left = t;
        t->height = max(height(t->left), height(t->right)) + 1;
        u->height = max(height(t->right), t->height) + 1;
        return u;
    }

    tree::node* tree::doubleRightLeftRotate(node*& t)  
    {
        t->right = singleRightRotate(t->right); //rotuje nejprve s pravým potomkem aktuálního vrcholu doprava
        return singleLeftRotate(t); //rotuje s aktuálním vrcholem doleva
    }

    tree::node* tree::doubleLeftRightRotate(node*& t) //to samé jen opačná strana
    {
        t->left = singleLeftRotate(t->left);
        return singleRightRotate(t);
    }

    tree::node* tree::insert(int x, node* t, string y)
    {
        if (t == nullptr) //když to dojde na prázdné místo (na konci větve), kde by to bylo v normálním binárním stromě, tak ho to tam umistí
        {
            t = new node;
            t->data = x;
            t->height = 0;
            t->left = t->right = nullptr;
            t->letter = y;
        }
        else if (x < t->data) //když je zadané číslo menší než číslo aktuálního prvku
        {
            t->left = insert(x, t->left, y); //ho to insertne rekursivně víc do levého podstromu
            if (height(t->left) - height(t->right) == 2) //když se výška podstromů nějakého vrcholu liší o 2
            {
                if (x < t->left->data) //tak se zjistí jestli zadaná data jsou menší než data potomka aktuálního prvku
                {
                    t = singleRightRotate(t); //a tehdy dojde k jedné pravé rotaci
                }
                else  //a pokud ne
                {
                    t = doubleLeftRightRotate(t); //tak dojde k dvojité levé a pravé rotaci
                }
            }
        }
        else if (x > t->data) //to samé jen prohozené strany
        {
            t->right = insert(x, t->right, y);
            if (height(t->right) - height(t->left) == 2)
            {
                if (x > t->right->data)
                {
                    t = singleLeftRotate(t);
                }
                else
                {
                    t = doubleRightLeftRotate(t);
                }
            }
        }
        //cout << t->data<< " ";
        t->height = max(height(t->left), height(t->right)) + 1; //nastavení výšky aktuálních prvků
        return t;
        //postupně se rekursivně vrací až na kořen a dělá kontroly výšky a popř. odpovídající rotace
    }

    tree::node* tree::findMin(node* t) //nalezne nejmenší vrchol v daném podstromu
    {
        if (t == nullptr)
            return nullptr;
        else if (t->left == nullptr)
            return t;
        else
            return findMin(t->left);
    }

    tree::node* tree::findMax(node* t) //nevyužil jsem protože stačí findMin nebo findMax
    {
        if (t == nullptr)
            return nullptr;
        else if (t->right == nullptr)
            return t;
        else
            return findMax(t->right);
    }

    tree::node* tree::findNode(string y)
    {
        //při hledaní vrcholu podle stringu nemůžeme používat menší/větši při výberu odpovídající větve
        std::stack<node*> s; //proto vytvoříme stack(mohla by být fronta) a uložíme všechny vrcholy zde
        node* curr = root;
        int i = 1; //pomocná proměnná i
        while ((curr != nullptr) || (!s.empty()))
        {
            while (curr != nullptr)
            {
                s.push(curr); //umistí vrcholy z levého podstromu do stacku
                curr = curr->left;
                i++;
            }
            curr = s.top(); //vezme z vrchu
            s.pop(); //zruší vrch
            i--;
            if (curr->letter == y) //když to najde, tak skončí while
            {
                break;
            }
            if (i == 0)return nullptr; //pokud se i rovná nule, tak to znamená že jsme prošli už všemi vrcholy a nenašli 
            curr = curr->right; //potom půjde do pravého podstromu vrcholů
        }
        //cout << curr->data;
        return curr; //returne vrchol (nalezený, nebo nullptr)
    }

    tree::node* tree::findNode(int x)
    {
        node* curr = root;

        while (curr != nullptr)
        {
            if (curr->data == x) break;
            if (curr->data < x) curr = curr->right;
            else curr = curr->left;
        }
        //cout << curr->letter;
        return curr; //podle hodnoty čísla najde a vratí vrchol (jako u normálního binárního stromu)
    }

    tree::node* tree::remove(int x, node* t)
    {
        node* curr;

        if (t == nullptr) //pokud to nenalezne co má vymazat
            return nullptr;

        else if (x < t->data) //vyhledá podle čísla co vymazat
            t->left = remove(x, t->left);
        else if (x > t->data)
            t->right = remove(x, t->right);

        else if (t->left && t->right) //když to má dva potomky
        {
            curr = findMin(t->right); //najde nejmenší v pravém podstromě
            t->data = curr->data; //uloží data
            t->letter = curr->letter; //a string do daného prvku
            t->right = remove(t->data, t->right); //odstraní prvek s daty vrcholu t
        }
        else //pokud má jednoho nebo žádného potomka
        {
            curr = t; //pomocný vrchol se nastaví na t
            if (t->left == nullptr) //pokud levý je nullptr
                t = t->right; //nastaví to t na pravý (v případě žádného na nullptr)
            else if (t->right == nullptr) //a nebo pokud pravý je nullptr
                t = t->left; //nastaví to t na levý
            delete curr; //vymaže nakonec curr
        }
        if (t == nullptr) //pokud t je nullptr
            return t; //
        else
        {
            t->height = max(height(t->left), height(t->right)) + 1;

            if (height(t->left) - height(t->right) == -2) //pokud není vybalancovaný po odstranění levého vrcholu
            {
                if (height(t->right->right) - height(t->right->left) == 1) //a pokud rozdíl výšky potomků pravého potomka je 1 tak dojde k
                    return singleLeftRotate(t); //pravé rotaci
                else
                    return doubleRightLeftRotate(t); //levé a pravé rotace
            }
            else if (height(t->left) - height(t->right) == 2) //to samé jen opačné strany
            {
                // left left case
                if (height(t->left->left) - height(t->left->right) == 1)
                    return singleRightRotate(t);
                // left right case
                else
                    return doubleLeftRightRotate(t);
            }
            return t;
        }
    }

    tree::node* tree::remove(string y, node* t) //odstraní vrchol se stringem y
    {
        node* curr = findNode(y); //najde to vrchol se zadaným stringem
        if (curr == nullptr)return nullptr; //pokud to nenajde tak returne nullptr
        root = remove(curr->data, root); //jinak podle dat čísla nalezeného vrcholu vymaže vrchol
        return t;
    }

    void tree::inorder(node* t) //vypíše strom v pořadí do řádku
    {
        if (t == nullptr)
            return;
        inorder(t->left);
        cout << t->data << " ";
        inorder(t->right);
    }

    unsigned int tree::depth() //počíta výšku stromu
    {
        if (empty()) return 0;

        node* curr = root;
        std::queue<node*> q;
        unsigned int h = 0;

        q.push(root);

        while (!q.empty())
        {
            int level_size = q.size();
            for (int i = 0; i < level_size; i++)
            {
                curr = q.front();
                q.pop();
                if (curr->left)
                    q.push(curr->left);
                if (curr->right)
                    q.push(curr->right);
            }
            h++;
        }
        return h;
    }

    //public

    tree::tree()
    {
        root = nullptr;
    }

    tree::~tree()
    {
        if (empty())
        {
            delete root;
            return;
        }
        else
        {
            makeEmpty(root);
            return;
        }
    }

    void tree::insert(int x, string y)
    {
        root = insert(x, root, y);
    }

    void tree::remove(int x)
    {
        root = remove(x, root);
    }

    void tree::remove(string y)
    {
        remove(y, root);
    }

    void tree::display()
    {
        inorder(root);
        cout << endl;
    }

    void tree::wide_print()
    {
        int h = depth(); //vyska stromu; slo by nahradit height(root) + 1
        unsigned int space = (1 << (h - 1));
        std::queue<node*> q;
        q.push(root);
        node* curr;

        for (unsigned int i = 1; i <= h; i++)
        {
            unsigned int level_size = q.size();
            for (unsigned int j = 0; j < level_size; j++)
            {
                curr = q.front();
                q.pop();
                cout << setw(space * 2) << std::right;
                if (curr)
                {
                    q.push(curr->left);
                    q.push(curr->right);
                    cout << curr->data << curr->letter/* << curr->height*/; //zakomentovaný výpis výšky každého vrcholu
                }
                else
                {
                    q.push(nullptr);
                    q.push(nullptr);
                    std::cout << " ";
                }

                std::cout << setw(space * 2) << " ";
            }
            space /= 2;
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }

    //int tree::maxCount() //nakonec jsem nepoužil; returne max počet prvků vzhledem k hloubce
    //{
    //    int x = 2;
    //    for (int i = 1; i < depth(); i++) //taky by šlo nahradit height(root) + 1
    //    {
    //        x *= 2;
    //    }
    //    x--;
    //    //cout << "2^" << depth() << "-1 =" << x;
    //    return x;
    //}

    int tree::find(string y)
    {
        if (empty())return 0;
        node* curr = findNode(y);
        if (curr == nullptr) return 0;
        return curr->data;
    }

    string tree::find(int x)
    {
        if (empty())return "n/a";
        node* curr = findNode(x);
        if (curr == nullptr) return "n/a";
        return curr->letter;
    }
