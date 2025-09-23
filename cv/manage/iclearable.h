#ifndef ICLEARABLE_H
#define ICLEARABLE_H
enum class ClearableState {
    just_cleared,
    just_created,
    just_used
};

class iclearable {
    public:
        iclearable(){}
        virtual ~iclearable(){}

        /*
         * @20250915
         * We enforce an instance of iclearable has three vailable states.
         * Just cleared. Just created. Just used. (e.g., imagecolordesc#setDescData() called.)
         */
         /*
          * @20250919
          * As long as state is not just_cleared, it is guaranteed color_map, ht and t are not nullptr.
          */
        virtual void clear()=0;
};
#endif