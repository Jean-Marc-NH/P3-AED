#include <iostream>

class XVector
{
public:
    XVector(int size_map, int size_vec);
    ~XVector();
    void push_back(int value);
    void push_front(int value);
    int& operator[](int index);
    int** map;
    int size_map, size_vec;
    int size;
    int front_index;
    int back_index;

private:
    void resize();
};

XVector::XVector(int sm, int sv) : size_map(sm), size_vec(sv), size(0), front_index(0), back_index(0)
{
    map = new int* [size_map];
    for (int i = 0; i < size_map; ++i)
        map[i] = new int[size_vec];
}

XVector::~XVector()
{
    for (int i = 0; i < size_map; ++i)
        delete[] map[i];
    delete[] map;
}

void XVector::push_back(int value)
{
    if (back_index == size_map * size_vec)
    {
        resize();
    }
    map[back_index / size_vec][back_index % size_vec] = value;
    ++back_index;
    ++size;
}

void XVector::push_front(int value)
{
    if (size == back_index)
    {
        resize();
    }
    // Mover todos los elementos un espacio adelante
    for (int i = back_index; i > front_index; --i)
    {
        map[i / size_vec][i % size_vec] = map[(i - 1) / size_vec][(i - 1) % size_vec];
    }
    map[front_index / size_vec][front_index % size_vec] = value;
    ++back_index;
    ++size;
}

int& XVector::operator[](int index)
{
    if (index < 0 || index >= size)
        throw std::out_of_range("Index out of range");
    return map[(front_index + index) / size_vec][(front_index + index) % size_vec];
}

void XVector::resize()
{
    int new_size_map = size_map * 2;
    int** new_map = new int* [new_size_map];
    for (int i = 0; i < new_size_map; ++i)
        new_map[i] = new int[size_vec];

    // Copiar los elementos al nuevo mapa
    for (int i = 0; i < size; ++i)
    {
        new_map[i / size_vec][i % size_vec] = map[(front_index + i) / size_vec][(front_index + i) % size_vec];
    }

    for (int i = 0; i < size_map; ++i)
        delete[] map[i];
    delete[] map;

    map = new_map;
    front_index = 0;
    back_index = size;
    size_map = new_size_map;
}

void print(XVector* p)
{
    for (int i = 0; i < p->size; i++)
        std::cout << (*p)[i] << " ";
    std::cout << "\n";
}

int main()
{
    XVector v(4, 3);
    v.push_back(3); v.push_back(8); v.push_back(1);
    v.push_back(4); v.push_back(9); v.push_back(6);
    v.push_back(7);
    print(&v);
    v.push_front(5); v.push_front(2);
    print(&v);
    v.push_front(11); v.push_front(17);
    v.push_back(22);
    print(&v);
    v.push_front(33); v.push_back(77);
    print(&v);
}
