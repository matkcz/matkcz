#include "avl_tree.h"

    //private

    bool tree::empty()
    {
        return root == nullptr;
    }

    void tree::makeEmpty(node* t)
    {
        if (t == nullptr)
            return;
        makeEmpty(t->left); //vypr�zdn� lev� podstrom rekursivn�
        makeEmpty(t->right); //vypr�zdn� prav� podstrom rekursivn�
        delete t;
    }

    int tree::height(node* t)
    {
        if (t != nullptr)
        {
            return t->height;  //returnuje hodnotu v��ky dan�ho vrcholu
        }
        else
        {
            return -1;
        }
    }

    //int tree::getBalance(node* t) //m�la nahradit porovn�v�n� v��ek u ostatn�ch funkc�, ale nefungovalo mi to v�ude, tak jsem se obe�el bez toho
    //{
    //    if (t == nullptr)
    //        return 0;
    //    else
    //        return height(t->left) - height(t->right);  //returne rozd�l v��ky prav�ho a lev�ho podstromu
    //}

    tree::node* tree::singleRightRotate(node*& t)
    {
        node* u = t->left; //pomocn� vrchol u se nastav� na lev� od vrcholu t
        t->left = u->right; //lev� potomek od t se nastav� na prav� potomek od u
        u->right = t; //prav� potomek od u se nastav� na t
        t->height = max(height(t->left), height(t->right)) + 1; //zm�na nejvy��� v��ky vrcholu t na spr�vnou v��ku
        u->height = max(height(u->left), t->height) + 1; //zm�na nejvy��� v��ky vrcholu u na spr�vnou v��ku
        return u;
    }

    tree::node* tree::singleLeftRotate(node*& t) //to sam� jako u p�edchoz�ho, jen prohozen� strany
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
        t->right = singleRightRotate(t->right); //rotuje nejprve s prav�m potomkem aktu�ln�ho vrcholu doprava
        return singleLeftRotate(t); //rotuje s aktu�ln�m vrcholem doleva
    }

    tree::node* tree::doubleLeftRightRotate(node*& t) //to sam� jen opa�n� strana
    {
        t->left = singleLeftRotate(t->left);
        return singleRightRotate(t);
    }

    tree::node* tree::insert(int x, node* t, string y)
    {
        if (t == nullptr) //kdy� to dojde na pr�zdn� m�sto (na konci v�tve), kde by to bylo v norm�ln�m bin�rn�m strom�, tak ho to tam umist�
        {
            t = new node;
            t->data = x;
            t->height = 0;
            t->left = t->right = nullptr;
            t->letter = y;
        }
        else if (x < t->data) //kdy� je zadan� ��slo men�� ne� ��slo aktu�ln�ho prvku
        {
            t->left = insert(x, t->left, y); //ho to insertne rekursivn� v�c do lev�ho podstromu
            if (height(t->left) - height(t->right) == 2) //kdy� se v��ka podstrom� n�jak�ho vrcholu li�� o 2
            {
                if (x < t->left->data) //tak se zjist� jestli zadan� data jsou men�� ne� data potomka aktu�ln�ho prvku
                {
                    t = singleRightRotate(t); //a tehdy dojde k jedn� prav� rotaci
                }
                else  //a pokud ne
                {
                    t = doubleLeftRightRotate(t); //tak dojde k dvojit� lev� a prav� rotaci
                }
            }
        }
        else if (x > t->data) //to sam� jen prohozen� strany
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
        t->height = max(height(t->left), height(t->right)) + 1; //nastaven� v��ky aktu�ln�ch prvk�
        return t;
        //postupn� se rekursivn� vrac� a� na ko�en a d�l� kontroly v��ky a pop�. odpov�daj�c� rotace
    }

    tree::node* tree::findMin(node* t) //nalezne nejmen�� vrchol v dan�m podstromu
    {
        if (t == nullptr)
            return nullptr;
        else if (t->left == nullptr)
            return t;
        else
            return findMin(t->left);
    }

    tree::node* tree::findMax(node* t) //nevyu�il jsem proto�e sta�� findMin nebo findMax
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
        //p�i hledan� vrcholu podle stringu nem��eme pou��vat men��/v�t�i p�i v�beru odpov�daj�c� v�tve
        std::stack<node*> s; //proto vytvo��me stack(mohla by b�t fronta) a ulo��me v�echny vrcholy zde
        node* curr = root;
        int i = 1; //pomocn� prom�nn� i
        while ((curr != nullptr) || (!s.empty()))
        {
            while (curr != nullptr)
            {
                s.push(curr); //umist� vrcholy z lev�ho podstromu do stacku
                curr = curr->left;
                i++;
            }
            curr = s.top(); //vezme z vrchu
            s.pop(); //zru�� vrch
            i--;
            if (curr->letter == y) //kdy� to najde, tak skon�� while
            {
                break;
            }
            if (i == 0)return nullptr; //pokud se i rovn� nule, tak to znamen� �e jsme pro�li u� v�emi vrcholy a nena�li 
            curr = curr->right; //potom p�jde do prav�ho podstromu vrchol�
        }
        //cout << curr->data;
        return curr; //returne vrchol (nalezen�, nebo nullptr)
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
        return curr; //podle hodnoty ��sla najde a vrat� vrchol (jako u norm�ln�ho bin�rn�ho stromu)
    }

    tree::node* tree::remove(int x, node* t)
    {
        node* curr;

        if (t == nullptr) //pokud to nenalezne co m� vymazat
            return nullptr;

        else if (x < t->data) //vyhled� podle ��sla co vymazat
            t->left = remove(x, t->left);
        else if (x > t->data)
            t->right = remove(x, t->right);

        else if (t->left && t->right) //kdy� to m� dva potomky
        {
            curr = findMin(t->right); //najde nejmen�� v prav�m podstrom�
            t->data = curr->data; //ulo�� data
            t->letter = curr->letter; //a string do dan�ho prvku
            t->right = remove(t->data, t->right); //odstran� prvek s daty vrcholu t
        }
        else //pokud m� jednoho nebo ��dn�ho potomka
        {
            curr = t; //pomocn� vrchol se nastav� na t
            if (t->left == nullptr) //pokud lev� je nullptr
                t = t->right; //nastav� to t na prav� (v p��pad� ��dn�ho na nullptr)
            else if (t->right == nullptr) //a nebo pokud prav� je nullptr
                t = t->left; //nastav� to t na lev�
            delete curr; //vyma�e nakonec curr
        }
        if (t == nullptr) //pokud t je nullptr
            return t; //
        else
        {
            t->height = max(height(t->left), height(t->right)) + 1;

            if (height(t->left) - height(t->right) == -2) //pokud nen� vybalancovan� po odstran�n� lev�ho vrcholu
            {
                if (height(t->right->right) - height(t->right->left) == 1) //a pokud rozd�l v��ky potomk� prav�ho potomka je 1 tak dojde k
                    return singleLeftRotate(t); //prav� rotaci
                else
                    return doubleRightLeftRotate(t); //lev� a prav� rotace
            }
            else if (height(t->left) - height(t->right) == 2) //to sam� jen opa�n� strany
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

    tree::node* tree::remove(string y, node* t) //odstran� vrchol se stringem y
    {
        node* curr = findNode(y); //najde to vrchol se zadan�m stringem
        if (curr == nullptr)return nullptr; //pokud to nenajde tak returne nullptr
        remove(curr->data, root); //jinak podle dat ��sla nalezen�ho vrcholu vyma�e vrchol
        return t;
    }

    void tree::inorder(node* t) //vyp�e strom v po�ad� do ��dku
    {
        if (t == nullptr)
            return;
        inorder(t->left);
        cout << t->data << " ";
        inorder(t->right);
    }

    unsigned int tree::depth() //po��ta v��ku stromu
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
        remove(x, root);
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
                    cout << curr->data << curr->letter/* << curr->height*/; //zakomentovan� v�pis v��ky ka�d�ho vrcholu
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

    //int tree::maxCount() //nakonec jsem nepou�il; returne max po�et prvk� vzhledem k hloubce
    //{
    //    int x = 2;
    //    for (int i = 1; i < depth(); i++) //taky by �lo nahradit height(root) + 1
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