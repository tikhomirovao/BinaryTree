#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>

using namespace std;
//структура узла бинарного дерева
struct Unit
{
    int x = 0;//поле, для хранения целого числа
    //поле указатель на родителя, указатель на левого потомка, указатель на правого потомка
    Unit* parent = nullptr, * left = nullptr, * right = nullptr;
};

class Tree
{
    Unit* Root;//указатель на корень дерева
    int Count = 0;//количество узлов
public:
    //прототипы методов:
    //конструктор создания дерева по умолчанию
    Tree();
    //Деструктор
    ~Tree();
    //Метод получения текущего кол-ва узлов
    int GetCount()const;
    //добавление узла в дерево 
    void Insert(int X);
    //Метод получения адреса корневого узла
    Unit* GetRoot()const;
    //вывод на экран узлов дерева по возрастанию
    void Show(Unit* root)const;
    //вывод на экран значения корня дерева
    void ShowRoot(Unit* root)const;
    //Метод поиска узла по значению ключевого поля
    bool Search(Unit* root, int Key)const;
    //Метод получения адреса максимального узла
    Unit* Max(Unit* root)const;
    //Метод получения адреса минимального узла
    Unit* Min(Unit* root)const;
    //Метод удаления узла из дерева
    void Delete(Unit* root, int key);

};

int main()
{
    system("chcp 1251");
    system("cls");
    srand((unsigned int)time(nullptr));

    Tree List;
    cout << "Размер дерева List: " << List.GetCount() << endl;
    List.Insert(-2);
    List.Insert(6);
    List.Insert(-4);
    List.Insert(-7);
    List.Insert(-6);
    List.Insert(5);
    List.Insert(9);
    List.Insert(13);
    List.Insert(-15);
    List.Insert(-18);
    List.Insert(16);
    List.Insert(3);
    cout << "Размер дерева List: " << List.GetCount() << endl;
    cout << "Адрес корня: " << List.GetRoot() << endl;
    List.Show(List.GetRoot());
    cout << endl;
    List.ShowRoot(List.GetRoot());
    List.Search(List.GetRoot(), 13);
    cout << "Адрес максимального узла: " << List.Max(List.GetRoot()) << endl;
    cout << "Адрес минимального узла: " << List.Min(List.GetRoot()) << endl;
    List.Delete(List.GetRoot(), -6);
    List.Show(List.GetRoot());
}

//конструктор по умолчанию
Tree::Tree()
{
    //при создание дерево пустое
    Root = nullptr;
}
//Деструктор
Tree::~Tree()
{
    //DelUnit(); //вызов метода DelUnit без параметров, для удаления всех узлов из дерева
}
//Метод получения текущего кол-ва узлов
int Tree::GetCount() const
{
    return Count; //возвращаем текущее кол-во узлов в списке
};
// добавление узла в бинарное дерево поиска
void Tree::Insert(int X)
{
    //создаем новый узел
    Unit* node = new Unit;
    node->x = X;//передаем значение в поле х
    node->left = node->right = nullptr;//указатели на левого и правого потомка нулевые
    //создаем временный указатель для перемещения по дереву для поиска родителя
    Unit* temp = Root; //и устанавливаем его на корень
    Unit* father = nullptr; //хранит адрес потенциального родителя
    //поиск места для вставки узла
    while (temp != nullptr) //пока не найдем подходящее свободное место
    {
        father = temp; //предпологаем, что текущей узел - родительский для вставляемого
        //если значение ключевого поля вставляемого узла меньше значения ключевого поля текущего узла
        if (node->x < temp->x) //сравниваем значения
            temp = temp->left; //идем в левую ветвь(к левому потомку)
        else temp = temp->right; //иначе идем в правую ветвь(к правому потомку)
    }
    //родитель найден, помещаем его адрес в поле parent вставляемого узла Node
    node->parent = father; //привязали родителя к вставляемому узлу
    //определяем каким потомком будет вставляемый узел(левым или правым)
    if (father == nullptr) //if(Node->parent==nullptr) //если вставляемый узел единственный(корень),
        Root = node; //то делаем его корневым
    else //иначе сравниваем его с родительским
        if (node->x < father->x)
            //если значение ключевого поля вставляемого узла меньше значения поля родительского узла,
            father->left = node; //то вставляемый узел становится левым потомком 
        else father->right = node; //иначе вставляемый узел становится правым потомком
    //увеличиваем счетчик количества узлов
    Count++;
}
//Метод получения адреса корневого узла
Unit* Tree::GetRoot() const
{
    return Root; //возвращает адрес корневого узла
}
//вывод на экран узлов дерева по возрастанию
void Tree::Show(Unit* root)const
{
    if (root != nullptr)
    {
        //рекурсивный вызов функции для вывода левой части на экран
        Show(root->left);
        cout << '\t';
        //вывод значения корня
        cout << root->x;
        //рекурсивный вызов функции для вывода правой части на экран
        Show(root->right);
    }
}
//вывод на экран значения корня дерева
void Tree::ShowRoot(Unit* root)const
{
    cout << root->x << endl;
}
//Метод поиска узла по значению ключевого поля
bool Tree::Search(Unit* root, int Key)const
{

    if (root == nullptr)
    {
        cout << "Элемент не найден!" << endl;;
        return false;
    }
    if (root->x == Key)
    {
        cout << "Элемент найден!" << endl;
        return true;
    }
    else
    {
        if (Key < root->x)
            return (Search(root->left, Key));//рекурсивный вызов функции для поиска в левой части дерева
        else
            return (Search(root->right, Key));//рекурсивный вызов функции для поиска в правой части дерева       
    }

}

//Метод получения адреса максимального узла
Unit* Tree::Max(Unit* root) const
{

    while (root->right != nullptr) //пока есть правые потомки
    {
        root = root->right; //идем к правому потомку
    }
    return root; //возвращаем адрес найденого узла, либо адрес самого узла, либо nullptr
}
//Метод получения адреса минимального узла
Unit* Tree::Min(Unit* root) const
{
    while (root->left != nullptr) //пока есть левые потомки 
    {
        root = root->left; //идем к левому потомку
    }
    return root; //возвращаем адрес найденого узла, либо адрес самого узла, либо nullptr
}
//Метод удаления узла из дерева
void Tree::Delete(Unit* root, int Key)
{
    //ключ не найден в дереве
    if (root == nullptr)
    {
        return;//выход
    }
    // если заданный ключ меньше корневого узла, рекурсивно движемся по левому поддереву
    if (Key < root->x)
    {
        Delete(root->left, Key);
    }
    // если данный ключ больше, чем корневой узел, рекурсивно движемся по правому поддереву
    else if (Key > root->x)
    {
        Delete(root->right, Key);
    }
    // ключ найден
    else
    {
        //  удаляемый узел не имеет потомков 
        if (root->left == nullptr && root->right == nullptr)
        {
            // освобождаем память 
            delete root;
            root = nullptr;

        }

        // удаляемый узел имеет двух потомков
        else if (root->left && root->right)
        {
            // найти его неупорядоченный узел-предшественник
            Unit* predecessor = Max(root->left);
            // копируем значение предшественника в текущий узел
            root->x = predecessor->x;
            // удаляем предшественника. Обратите внимание, что            
            Delete(root->left, predecessor->x);
        }
        // удаляемый узел имеет только одного потомка
        else
        {
            // выбираем дочерний узел
            Unit* child = (root->left) ? root->left : root->right;
            Unit* curr = root;
            root = child;
            // освобождаем память
            delete curr;
        }

    }

}