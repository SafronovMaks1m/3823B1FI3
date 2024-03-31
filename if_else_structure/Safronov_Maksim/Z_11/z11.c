#include <iostream>
#include <math.h>

template<typename T>

class Vector{
    private:
        T* _array;
        size_t _size;
    public:
        Vector(){
            _size = 10;
            _array = new T[_size];
            for (int i = 0; i<_size; i++){
                _array[i] = 0;
            }
        }

        Vector(size_t size, T* array) : _size(size), _array(new T[size]){
            for (int i = 0; i<_size; i++){
                _array[i] = array[i];}
        }

        Vector(std::initializer_list<T> list){
            _size = list.size();
            int i = 0;
            _array = new T[_size];
            for (auto elem = list.begin(); elem!=list.end(); ++elem){
                _array[i] = *elem;
                i++;
            }
        }

        Vector operator+(const Vector& obj){
            Vector s = Vector (obj._size, obj._array);
            for (int i = 0; i<_size; i++){
                s._array[i] = _array[i]+obj._array[i];}
            return s;
        }

        Vector operator-(const Vector& obj){
            Vector s = Vector (obj._size, obj._array);
            for (int i = 0; i<_size; i++){
               s._array[i] = _array[i]-obj._array[i];}
            return s;
        }

        Vector operator*(Vector& obj){
            Vector s = Vector();
            for (int i = 0; i<obj._size; i++){
                s._array[0]+=_array[i]*obj._array[i];}
            for (int i = 1; i<s._size; i++){
                s._array[i] = -1000;}
            return s;
        }

        Vector(size_t size) : _size(size){
            _array = new T[_size];
            for (int i = 0; i<_size; i++){
                _array[i] = 0;
            }
        }

        double search_length(Vector vector){
            double s = sqrt( double (vector.operator*(vector)._array[0]));
            return s;
        }

        double* vector_normali(Vector& vector){
            double* arr = new double[vector._size];
            double s = vector.search_length(vector);
            for (int i = 0; i<vector._size; i++){
                arr[i] = double(vector._array[i])/s;}
            return arr;
        }

        inline GetSize(){return _size;}

        const T& operator[](int index) const{
            return _array[index];
        }

        friend std::ostream& operator<<(std::ostream& os, const Vector& obj){
            bool flag = false;
            for (int i = 1; i<obj._size; i++){
                if (obj._array[i] != -1000) flag = true;}
            if (flag == false){
                os << obj._array[0]; return os;}
            os << "(";
            for (int i = 0; i<obj._size; i++){
                os << obj._array[i];
                if (i+1!=obj._size)
                    os << ", ";
            }
            os << ")" << std::endl;

            return os;
        }
        friend std::istream& operator>>(std::istream& is, Vector& obj){
            std::cout << "Введите размер вектора: ";
            is >> obj._size;
            T arr[obj._size] = {};
            for (int i = 0; i<obj._size; i++){
                std :: cout << "[" << i+1 << "] = ";
                is >> obj._array[i];}
            return is;
        }

};


int main(){
    Vector vector = Vector <int> ();
    std::cin >> vector;
    Vector vector2 = Vector <int> ();
    std::cin >> vector2;
    Vector vector3 = vector+vector2;
    std::cout << vector3;
    vector3 = vector-vector2; 
    std::cout << vector3;
    Vector s = vector*vector2;
    std::cout << s << std::endl;
    std::cout << vector.search_length(vector) << std::endl;
    double* v = vector.vector_normali(vector);
    Vector vector4 = Vector <double> (vector.GetSize(), v);
    std::cout << vector4; 
    return 0;
}
