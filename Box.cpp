```
class Box{
 int l{},b{},h{};
 
 public:
    Box(){l = 0;b=0;h=0;};
    Box(int,int,int);
    Box(Box const &oldBox){
       l = oldBox.l;
       b = oldBox.b;
       h = oldBox.h;
    }
    
    int getLength() {return l;}
    int getBreadth() {return b;}
    int getHeight() {return h;}
    long long CalculateVolume(){return (long long)l*b*h;}
    bool operator<(const Box& b)const;
    
    friend ostream& operator<<(ostream& out,const Box& B);
};

Box::Box(int l,int b,int h){
    this->l = l;
    this->b = b;
    this->h = h;
}
bool Box::operator<(const Box &b)const{
    return (this->l < b.l)? true:((this->b<b.b && this->l == b.l)?true:
    ((this->h < b.h && this->b == b.b && this->l == b.l)?true:false)
    );     
}

ostream& operator<<(ostream& out,const Box& B){
    out<<B.l<<' '<<B.b<<' '<<B.h;
    return out;
}
```
