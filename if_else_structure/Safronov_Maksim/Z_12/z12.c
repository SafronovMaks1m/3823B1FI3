#include <iostream>
#include <math.h>

template<typename T>

class Vector{
    private:
        T* _array;
        size_t _size;
    public:
        Vector(){
            _size = 5;
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

        Vector<double> vector_normali(Vector& vector){
            double* arr = new double[vector._size];
            for (int i = 0; i<vector._size; i++){
                arr[i] = vector._array[i];}
            
            double s = vector.search_length(vector);
            for (int i = 0; i<vector._size; i++){
                arr[i] = arr[i]/s;
                }
            Vector<double> t = Vector <double>(vector._size, arr);
            return t;
        }

        T& operator[](int index) const{
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
            T arr[obj._size] = {};
            for (int i = 0; i<obj._size; i++){
                std :: cout << "[" << i+1 << "] = ";
                is >> obj._array[i];}
            return is;
        }
};

template<typename T>
class Matrix{
private:
    size_t _size;
    Vector<T>* _vectors;
public:
    Matrix(){
        _size = 3;
        _vectors = new Vector<T>[_size];
        for (int i = 0; i<_size; i++){
            std::cin >> _vectors[i];
        }
    }

    Matrix(int n){
        _size = n;
        _vectors = new Vector<T>[_size];
        for (int i = 0; i<_size; i++){
            for (int j = 0; j<_size; j++){
                _vectors[i][j] = 0;
            }
        }
    }

    Vector<T>& operator[](int index) const{
        return _vectors[index];
    }

    Matrix operator+(const Matrix& m)const{
        if (_size != m._size)
        {
            throw "Invalid matrix size!";
        }
        Matrix n = Matrix();
        // for (size_t i = 0; i < _size; i++)
        // {
        //     n[i] = (*this)[i] + m[i];
        // }
    
        for (int i = 0; i < _size; ++i){
            for (int j = 0; j < _size; j++){
                n[i][j] = _vectors[i][j] + m._vectors[i][j];
            }
        }
        return n;
    }

    Matrix operator-(const Matrix& m)const{ 
        if (_size != m._size)
        {
            throw "Invalid matrix size!";
        }
        Matrix n = Matrix();
        for (int i = 0; i < _size; ++i){
            for (int j = 0; j < _size; j++){
                n[i][j] = _vectors[i][j] + m._vectors[i][j];
            }
        }
        return n;
    }  



    Matrix operator*(Matrix& obj){
        std::cout << obj;
        std::cout << (*this);
        Matrix s = Matrix(0);
        for (int i = 0; i<_size; i++){
            for (int j = 0; j<_size; j++){
                for (int k = 0; k<obj._size; k++){
                    s._vectors[i][j]+= _vectors[i][k]*obj._vectors[k][j];
                }
            }
        }
        return s;
    }

    T det_3(T* matrix){
        return (matrix[0]*matrix[4]*matrix[8]+matrix[1]*matrix[5]*matrix[6]+matrix[3]*matrix[7]*matrix[2]-matrix[2]*matrix[4]*matrix[6]-matrix[1]*matrix[3]*matrix[8]-matrix[0]*matrix[5]*matrix[7]);}
    
    T det(Matrix mas){
        T* matrix = new T [mas._size*mas._size];
        for (int i = 0; i<mas._size; i++){
            for (int j = 0; j<mas._size; j++){
                matrix[i*_size+j] = mas._vectors[i][j];
            }
        } 
        if (mas._size == 2){return (matrix[0]*matrix[3] - matrix[1]*matrix[2]);}
        if (mas._size == 3){return det_3(matrix);}
        int k = mas._size;
        int d = 0, t = 1, total = 0;
        T* s = new T [(k-1)*(k-1)];
        for (int i = 0; i<k*k; i++){
            total = 0;
            if (i%k == 0){
                t = matrix[i]*pow(-1, (i/k+1)+1);
                for (int j = 0; j<k*k; j++){
                    if (j/k!=i/k && j%k!=0){
                        s[total] = matrix[j]; total+=1;}}
            if ((k-1)*(k-1) == 9){
                d+= t*det_3(s);}
            else{
                Matrix lol = Matrix(0);
                lol._size = k-1;
                for (int q = 0; q<lol._size; q++){
                    for (int j = 0; j<lol._size; j++){
                        lol._vectors[q][j] = s[lol._size*q+j];
                    }}
                d+=t*det(lol);}}}
        return d; 
    }

    Matrix operator/(Matrix& obj){
        Matrix inv = obj.inverse_matrix();
        Matrix itog = (*this)*inv;
        return itog;
    }

    Matrix matrix_transponded(){
        Matrix s = Matrix(_size);
        for (int i = 0; i<_size; i++){
            for (int j = 0; j<_size; j++){
                s._vectors[i][j] = _vectors[j][i];
            }
        }
        return s;
    }

    Matrix inverse_matrix(){
        Matrix<double> s = Matrix(_size);
        for (int i = 0; i<_size; i++){
            for (int j = 0; j<_size; j++){
                if (i == j) s[i][j] = 1;}}
        double ved_elem = 0;
        for (int i = 0; i<_size; i++){
            ved_elem = _vectors[i][i];
            for (int j = 0; j<_size; j++){
                _vectors[i][j]/=ved_elem;
                s._vectors[i][j]/=ved_elem;
            }
            ved_elem = _vectors[i][i];
            for (int j = 0; j<_size; j++){
                double subtra = _vectors[j][i]/ved_elem;
                if (j!=i){
                    for(int k = 0; k<_size+1; k++){
                        _vectors[j][k] = _vectors[j][k]-(subtra*_vectors[i][k]);
                        s._vectors[j][k] = s._vectors[j][k]-(subtra*s._vectors[i][k]);}}}}
        return s;
    }

    friend std::ostream& operator<<(std::ostream& os, const Matrix& matrix){
        for (size_t i =0; i < matrix._size; i++)
            os << matrix._vectors[i];
        os << std::endl;
        return os;
    }



};


int main(){
    Matrix<double> m1;
}
