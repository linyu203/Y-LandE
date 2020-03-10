#include <iostream>

namespace MySmartPointer{
    
template <class _T>
class shared_ptr{
    _T * d_ptr;
    mutable long * d_referenc_count;
  public:
    shared_ptr(){
        d_ptr = nullptr;
        d_referenc_count = nullptr;
    };
    shared_ptr(const shared_ptr& o){
        if(o.d_ptr != nullptr){
            this->d_ptr = o.d_ptr;
            this->d_referenc_count = o.d_referenc_count;
            (*d_referenc_count)++;
        }
    }
    shared_ptr(_T * p){
        if(p != nullptr){
            d_ptr = p;
            d_referenc_count = new long (1);
        }
    }
    shared_ptr& operator=(const shared_ptr& o){
        if(&o == this){
            return *this;
        }
        if(d_ptr != nullptr){
            if(--(*d_referenc_count)==0){
                delete d_referenc_count;
                delete d_ptr;
            }
        }
        this->d_ptr = o.d_ptr;
        this->d_referenc_count = o.d_referenc_count;
        if(o.d_ptr != nullptr){
            (*d_referenc_count)++;
        }
        return *this;
    }
    _T& operator*(void){
        return (*d_ptr);
    }
    _T* operator->(void){
        return d_ptr;
    }
    ~shared_ptr(){
        if(d_ptr){
            if(*d_referenc_count ==1){
                delete d_referenc_count;
                delete d_ptr;
                d_referenc_count = nullptr;
                d_ptr = nullptr;
                std::cout<<"release \n";
                return;
            }
            (*d_referenc_count)--;
        }
    }
};
template <class _T, class ...Args>
shared_ptr<_T> makeshared (Args&&...args){
    return shared_ptr<_T>(new _T(args...));
}

}
class myclass{
    int x,y;
  public:
    myclass(){std::cout<<"default construct myclass\n";};
    myclass(int a, int b){std::cout<<"construct myclass\n"; x = a; y = b;};
    myclass(const myclass& o){
        std::cout<<"copy construct myclass\n";
        x = o.x;
        y = o.y;
    }
    ~myclass(){
        std::cout<<"destruct myclass\n";
    }
    void set(int a, int b){x=a;y=b;}
    int getx(){return x;}
    int gety(){return y;}
};


int main() {
    /*
    cout<<getmax(12.4,15.1)<<endl;
    myclass *p;
    p = new myclass [100];
    if(p){
        (p+20)->set(2,4);
        (p+15)->set(15,5);
        cout<<p[20].getx()<<p[15].getx()<<endl;
        delete []p;
    }*/
    using namespace MySmartPointer;
    MySmartPointer::shared_ptr<myclass> ptr = MySmartPointer::makeshared<myclass>();
    (*ptr).set(2,4);
    std::cout<<(*ptr).getx()<<std::endl;
    std::cout<<(*ptr).gety()<<std::endl;
    auto bb = MySmartPointer::makeshared<myclass>(7,8);
    auto cc = bb;
    std::cout<<(*bb).getx()<<std::endl;
    std::cout<<(*cc).gety()<<std::endl;
    std::cout<<bb->getx()<<std::endl;
    std::cout<<cc->gety()<<std::endl;
    cc = MySmartPointer::makeshared<myclass>(*ptr);
    std::cout<<cc->gety()<<std::endl;
    return 0;
}
