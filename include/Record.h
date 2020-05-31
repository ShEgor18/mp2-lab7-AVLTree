#include <iostream>

using namespace std;

template<class Key, class Data>
class Record {
public:
    Key key;
    Data data;  
    unsigned int height;
    Record* left;
    Record* right;

    Record<Key, Data>(Key _key, Data _data);
    bool operator ==(const Key&);
    bool operator !=(const Key&);
    bool operator<(const Record < Key, Data>& rec);
    bool operator>(const Record < Key, Data>& rec);

    Record<Key, Data>& operator=(const Record<Key, Data>& rec);
    friend ostream& operator<<(std::ostream& os, const Record<Key, Data>& d);
};

template<class Key, class Data>
Record<Key, Data>::Record(Key _key, Data _data)
{
    key = _key;
    data = _data;
    left = nullptr;
    right = nullptr;
    height = 1;
}

template<class Key, class Data>
bool Record<Key, Data>::operator!=(const Key& _key)
{
    return key != _key;
}

template<class Key, class Data>
bool Record<Key, Data>::operator==(const Key& _key)
{
    return key == _key;
}

template<class Key, class Data>
bool Record<Key, Data>::operator<(const Record<Key, Data>& rec)
{
    return key < rec.key;
}

template<class Key, class Data>
bool Record<Key, Data>::operator>(const Record<Key, Data>& rec)
{
    return key > rec.key;
}

template<class Key, class Data>
Record<Key, Data>& Record<Key, Data>::operator=(const Record<Key, Data>& rec)
{
    key = rec.key;
    data = rec.data;
    left = rec.left;
    right = rec.right;
    height = rec.height;
    return *this;
}

template<class Key, class Data>
ostream& operator<<(ostream& os, const Record<Key, Data>& d)
{
    os << "Key: " << d.key << " Data: " << d.data << endl;
    return os;
}
