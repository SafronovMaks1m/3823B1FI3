#include<iostream>
#include<algorithm>
#include<random>
#include<time.h>

class Base_sensors{
    private:
        double _min;
        double _max;
        int _start; int _end; int _gap;
    protected:
        double _value;
        void Gener(){
            srand(time(NULL));
            double a = (_start + rand()%(_end+1))/_gap;
            _value+=a;
            _value = std::max(_min,_value); 
            _value = std::min(_max,_value);
        }
    public:
        Base_sensors(){
            _value = 0+rand()%80;
            _min = 0; _max = 100; 
            _start = 10; _end = 200;
            _gap = 10;
        }
        Base_sensors(int start, int end, int gap, double min, double max){
            _min = min; _max = max; _start = start; _end = end; _gap = gap;}
        double operator()(){
            Gener();        
            return _value;
        }
};

class co2 : public Base_sensors{
    public:
        const double MIN = 0;
        const double MAX = 100;
        co2(int start = -100, int end = 201, double gap = 100.0) : Base_sensors(start, end, gap, MIN, MAX){
            _value = rand()%100;
        };
};

class Pressure_sensor : public Base_sensors{
    public:
        const double MIN = 600;
        const double MAX = 900;
        Pressure_sensor(int start = -300, int end = 601, double gap = 10.0) : Base_sensors(start, end, gap, MIN, MAX){
            _value = MIN + rand() % int(MAX - MIN);
        };

};

class Humidity_sensor : public Base_sensors{
    public:
        const double MIN = 0;
        const double MAX = 100;
        Humidity_sensor(int start = 0, int end = 100, double gap = 100.0) : Base_sensors(start, end, gap, MIN, MAX){
            _value = (rand() % 100)/100.0;
        }
};

class Temp_sensor : public Base_sensors{
    public:
        const double MIN = -93;
        const double MAX = 58;
        Temp_sensor(int start = -5, int end = 11, double gap = 11.0) : Base_sensors(start, end, gap, MIN, MAX){
            _value = -5 + rand() % 11;
        };
};

enum Direction{
    North,
    Northwest,
    Northeast,
    East,
    Southeast,
    Southwest,
    South,
    West
};

class Wide : protected Base_sensors{
    private:
        Direction _direction;
        void gen(){
            this->Gener();
            _direction = static_cast<Direction> (rand()%8);
        }

    public:
        const double MIN = 0;
        const double MAX = 30; 
        Wide(int start = -10, int end = 21, double gap = 10) : Base_sensors(start, end, gap, MIN, MAX){
            _value =  rand()%30;
            _direction =static_cast<Direction> ( rand());
        }
        double GetSpeed(){
            gen();
            return _value;
        }
        Direction GetDirection(){
            gen();
            return _direction;
        }
    
};

class Sensors : protected Base_sensors{
    private:
        Base_sensors** mas_classes;
        int _total;
        int _count;
    public:
        Sensors(){
            _count = 0;
            _total = 10;
            mas_classes = new Base_sensors*[_total];
        }
        void AppendClasses(Base_sensors* tmp){
            mas_classes[_count] = tmp;
            _count++;
        }
        ~Sensors(){
            for (int i = 0; i < _total; i++){
                delete[] mas_classes[i];}
            delete[] mas_classes;
        }

};


int main(){
    Temp_sensor* tmp = new Temp_sensor;
    Sensors sen = Sensors();
    sen.AppendClasses(tmp);
    return 0;
}
