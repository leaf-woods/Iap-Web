#ifndef ICLEARABLE_H
#define ICLEARABLE_H
enum class ClearableState {
    just_cleared,
    just_created,
    just_used
};

class iclearable {
    public:
        iclearable() {}
        ~iclearable() {}

        /*
         * @20250915
         * We enforce an instance of iclearable has three vailable states.
         * Just cleared. Just created. Just used. (e.g., imagecolordesc#setDescData() called.)
         */
        virtual void clear()=0;
};
#endif