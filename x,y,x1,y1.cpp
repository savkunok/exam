#include <iostream>
using namespace std;

class A
{
private:
    int x,y;
public:
    A(int x_ ,int y_){
        this->x=x_;
        this->y=y_;
    }
  
    ~A(){};
    
    int getX(){
        return x;
    }
    int getY(){
        return y;
    }
};


class B : public  A
{
private: 
    int x1,y1;
public: 
    B();

    B(int x_,int y_, int x1_, int y1_) : A( x_, y_)
    {
        this->x1=x1_;
        this->y1=y1_;
    }
    
    ~B(){};   
   
    int square(){
        int tmp1 = x1-A::getX();
        int tmp2 = y1-A::getY();
        int tmp3 = tmp1*tmp2;
       return tmp3;
    }

};


int main()
{
    B B(1,1,3,3);
    std::cout<< B::square<< std::endl;
    return 0;
}
