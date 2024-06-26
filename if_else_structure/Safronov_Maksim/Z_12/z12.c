#include <iostream>
#include <math.h>
#include <time.h> 

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

        Vector(int size){
            _size = size;
            _array = new T[_size];
            for (int i = 0; i<_size; i++){
                _array[i] = 0;
            }
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
            try{
                this->Proverka(obj);}
            catch (const char* error_message){
                std::cout << error_message << std::endl; throw;}
            Vector s = Vector(obj._size, obj._array);
            for (int i = 0; i<_size; i++){
                s._array[i] = _array[i]+obj._array[i];}
            return s;
        }

        void Proverka(const Vector& obj){
            if (_size!=obj._size){
                throw "Размеры не совпадают";}
        }

        Vector operator-(const Vector& obj){
            try{
                this->Proverka(obj);}
            catch (const char* error_message){
                std::cout << error_message << std::endl; throw;}
            Vector s = Vector (obj._size, obj._array);
            for (int i = 0; i<_size; i++){
               s._array[i] = _array[i]-obj._array[i];}
            return s;
        }

        Vector operator*(Vector& obj){
            try{
                this->Proverka(obj);}
            catch (const char* error_message){
                std::cout << error_message << std::endl; throw;}
            Vector s = Vector();
            for (int i = 0; i<obj._size; i++){
                s._array[0]+=_array[i]*obj._array[i];}
            for (int i = 1; i<s._size; i++){
                s._array[i] = -1000;}
            return s;
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

        ~Vector(){}

        friend std::istream& operator>>(std::istream& is, Vector& obj){
            for (int i = 0; i<obj._size; i++){
                std::cout << "[" << i << "] = "; std::cin >> obj._array[i];}
            return is;
        }
};

template<typename T>
class Matrix{
    private:
        size_t _size;
        Vector<T>* _vectors;
        bool _flag;
    public:
        Matrix(){
            _flag = false;
            _size = 3;
            _vectors = new Vector<T>[_size];
        }

        Matrix(int n){
            _flag = false;
            _size = n;
            _vectors = new Vector<T> [_size];
            for (int i = 0; i<_size; i++){
                _vectors[i] = Vector<T>(_size);
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
            Matrix n = Matrix(m._size);
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
            Matrix n = Matrix(m._size);
            for (int i = 0; i < _size; ++i){
                for (int j = 0; j < _size; j++){
                    n[i][j] = _vectors[i][j] - m._vectors[i][j];
                }
            }
            return n;
        }  

        Matrix operator*(Matrix& obj){
            Matrix s = Matrix(obj._size);
            if (obj._flag == true){
                s._flag = obj._flag;
                return s;}
            for (int i = 0; i<_size; i++){
                for (int j = 0; j<_size; j++){
                    for (int k = 0; k<obj._size; k++){
                        s._vectors[i][j]+= _vectors[i][k]*obj._vectors[k][j];
                    }
                }
            }
            return s;
        }

        Matrix(const Matrix& obj){
            _flag = obj._flag;
            _size = obj._size;
            _vectors = new Vector<T>[_size];
            for (int i = 0; i<_size; i++){
                _vectors[i] = Vector<T>(_size);}
            for (int i = 0; i<_size; i++){
                for (int j = 0; j<_size; j++){
                    _vectors[i][j] = obj._vectors[i][j];
                }
            }
        }
        
        T det(){
            long double ved_elem = 0;
            for (int i = 0; i<_size; i++){
                if (_vectors[i][i] == 0){
                    try{
                        this->replace_zero(i);}
                    catch(const char* error_message){
                        std::cout << error_message; return;}
                    }
                ved_elem = _vectors[i][i];
                for (int j = 0; j<_size; j++){
                    long double subtra = _vectors[j][i]/ved_elem;
                    if (j>i){
                        for(int k = 0; k<_size+1; k++){
                            _vectors[j][k] = _vectors[j][k]-(subtra*_vectors[i][k]);}}}}
            ved_elem = 1;
            for(int i = 0; i<_size; i++){ved_elem*=_vectors[i][i];} 
            return ved_elem;
        }

        Matrix operator/(Matrix& obj){
            Matrix inv = obj.inverse_matrix();
            if (inv._flag == true){
                return inv;}
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

        ~Matrix(){
            delete [] _vectors;
        }

        void replace_zero(int col){
            int no_zero = 0;
            for (int j = 0; j<_size; j++){
                if (_vectors[j][col]!=0){
                    no_zero = j; break;}}
            if (no_zero == 0){
                throw "DET = 0! ";}
            for (int i = 0; i<_size; i++){
                for (int j = 0; j<_size; j++){
                    if (i == no_zero){
                        long double a = _vectors[col][j];
                        _vectors[col][j] = _vectors[i][j];
                        _vectors[i][j] = a;}}}
        }

        friend Matrix operator*(int a, Matrix& obj){
            Matrix s = obj;
            for (int i = 0; i<obj._size; i++){
                for (int j = 0; j<obj._size; j++){
                    s[i][j]*=3;
                }
            }
            return s;
        }

        Matrix inverse_matrix(){
            Matrix<float> s = Matrix(_size);
            for (int i = 0; i<_size; i++){
                for (int j = 0; j<_size; j++){
                    if (i == j) s[i][j] = 1;}}
            double ved_elem = 0;
            for (int i = 0; i<_size; i++){
                if (_vectors[i][i] == 0){
                    try{
                        this->replace_zero(i);}
                    catch(const char* error_message){
                        std::cout << error_message; s._flag = true; return s;}
                    }
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
            if (matrix._flag == true){
                return os;}
            for (size_t i =0; i < matrix._size; i++)
                os << matrix._vectors[i];
            os << std::endl;
            return os;
        }

        friend std::istream& operator>>(std::istream& is, Matrix& obj){
                std::cout << "Введите размер матрицы : ";
                is >> obj._size;
                obj._vectors = new Vector<T>[obj._size];
                for (int i = 0; i<obj._size; i++){
                    obj._vectors[i] = Vector<T>(obj._size);
                    std::cin >> obj._vectors[i];
                    std::cout << std::endl;
                }
                std::cout<<std::endl;
                return is;
            }
};


int main(){
    srand(time(0));
    time_t start, end;
    time(&start);
    Matrix<float> a;
    std::cin >> a;
    Matrix<float> b;
    std::cin >> b;
    Matrix<float> c;
    std::cin >> c;
    Matrix <float> prom = (b-3*c);
    Matrix <float> itog = a/prom;
    time(&end);
    double seconds = difftime(end, start);
    std::cout << "The time: " << seconds << " seconds" <<std::endl;
}
