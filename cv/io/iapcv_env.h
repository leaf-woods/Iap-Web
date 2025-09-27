#ifndef IAPCV_ENV_H
#define IAPCV_ENV_H

#include <string>

// https://stackoverflow.com/questions/1008019/how-do-you-implement-the-singleton-design-pattern
// https://stackoverflow.com/questions/86582/singleton-how-should-it-be-used
class iapcv_env {
    private:
        static iapcv_env* envInstance;
        std::string DEV_TST_IMGBASE;

    public:
        const char* HOME = "/home/linye020603";  // 17
        const char* DEV = "iap-web"; // 7
        const char* GITHUB = "github-local/Iap-Web"; // 20

        const char* DEV_BASE = "cv"; // 2

        const char* TEST_BASE = "cv-test";  // 7
        const char* TEST_IMGDATA_BASE = "cv-test/test-data/image";  //23
   
    private:
        iapcv_env();
        ~iapcv_env();

        iapcv_env(const iapcv_env&);      // Don't Implement
        void operator=(iapcv_env const&); // Don't implement

    //public:
        //iapcv_env(const iapcv_env&)       = delete;
        //void operator=(iapcv_env const&)  = delete;

        //MySingleton(const MySingleton&) = delete;
        //const iapcv_env& operator=(const iapcv_env&) = delete;
        //iapcv_env(iapcv_env&& other) noexcept = delete;
        //iapcv_env& operator=(iapcv_env&& other) noexcept = delete;

    public:
        static iapcv_env* getInstance();

        //iapcv_env(const iapcv_env&) = delete;
        std::string getDevTestImgBase();
        void print();
};
#endif

