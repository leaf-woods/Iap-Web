#ifndef ICLEARABLE_H
#define ICLEARABLE_H
class iclearable {
    public:
        iclearable() {}
        ~iclearable() {}
        virtual void clear()=0;
};
#endif