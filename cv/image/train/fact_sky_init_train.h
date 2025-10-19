#ifndef FACT_SKY_INIT_TRAIN_H
#define FACT_SKY_INIT_TRAIN_H

#include "iapcv_env.h"
#include "sky_init_train.h"

/**
 * A factory which generate a singleton of sky_init_train using file IMG_4585_S_CR_R1_S64_00.JPG
 */
class fact_sky_init_train {
   private:
        static sky_init_train* skyTrainInstance; 

   public:
        fact_sky_init_train();
        ~fact_sky_init_train();

        fact_sky_init_train(const fact_sky_init_train&);
        void operator=(fact_sky_init_train const&);

    public:
        static sky_init_train* getSkyTrainInstance();
};
#endif