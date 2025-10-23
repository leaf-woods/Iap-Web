iap_ghl_cv_base=/home/linye020603/github-local/Iap-Web/cv
dir_context=$(iap_ghl_cv_base)/context
dir_io=$(iap_ghl_cv_base)/io
dir_image=$(iap_ghl_cv_base)/image
dir_manage=$(iap_ghl_cv_base)/manage
dir_util=$(iap_ghl_cv_base)/util

INCLUDES = -I$(dir_context)/ \
           -I$(dir_image)/color \
           -I$(dir_image)/color/compare \
		   -I$(dir_image)/color/datatype \
		   -I$(dir_image)/color/datatype/status \
		   -I$(dir_manage)/ \
		   -I$(dir_image)/region \
		   -I$(dir_image)/region/datatype \
		   -I$(dir_image)/region/evaluate \
		   -I$(dir_image)/region/explore \
		   -I$(dir_image)/train \
		   -I$(dir_io) \
		   -I$(dir_util)/convert \
		   -I$(dir_util)/log \
           -I$(dir_util)/print \
           -I/usr/include/opencv4

LIBS = -lopencv_core -lopencv_imgcodecs -lopencv_imgproc

OBJS = testEvaluator.o \
       iapcv_env.o \
	   region_evaluator.o \
	   pixel_comparator.o \
	   sky_init_train.o \
	   fact_sky_init_train.o \
	   iapcv_log.o \
	   iap_print.o

all : testEvaluator testEvalParams testEvalPolicy

testEvaluator : $(OBJS) 
	g++ -o testEvaluator $(OBJS) $(LIBS)
testEvaluator.o : testEvaluator.cpp
	g++ -c testEvaluator.cpp $(INCLUDES) 
iapcv_env.o : $(dir_io)/iapcv_env.cpp
	g++ -c $(dir_io)/iapcv_env.cpp

region_evaluator.o : $(dir_image)/region/evaluate/region_evaluator.cpp
	g++ -c $(dir_image)/region/evaluate/region_evaluator.cpp $(INCLUDES)
pixel_comparator.o : $(dir_image)/color/compare/pixel_comparator.cpp
	g++ -c $(dir_image)/color/compare/pixel_comparator.cpp $(INCLUDES)
iapcv_log.o : $(dir_util)/log/iapcv_log.cpp
	g++ -c $(dir_util)/log/iapcv_log.cpp 

iap_print.o : $(dir_util)/print/iap_print.cpp
	g++ -c $(dir_util)/print/iap_print.cpp $(INCLUDES)
sky_init_train.o : $(dir_image)/train/sky_init_train.cpp
	g++ -c $(dir_image)/train/sky_init_train.cpp $(INCLUDES)
fact_sky_init_train.o : $(dir_image)/train/fact_sky_init_train.cpp
	g++ -c $(dir_image)/train/fact_sky_init_train.cpp $(INCLUDES)

EVAL_PARAMS_OBJS = testEvalParams.o iapcv_env.o sky_init_train.o fact_sky_init_train.o iap_print.o 
testEvalParams : $(EVAL_PARAMS_OBJS)
	g++ -o testEvalParams $(EVAL_PARAMS_OBJS) $(LIBS)
testEvalParams.o : testEvalParams.cpp
	g++ -c testEvalParams.cpp $(INCLUDES)

testEvalPolicy : testEvalPolicy.o 
	g++ -o testEvalPolicy testEvalPolicy.o $(LIBS)
testEvalPolicy.o : testEvalPolicy.cpp
	g++ -c testEvalPolicy.cpp $(INCLUDES)

clean : 
ifneq (,$(wildcard *.o))
	rm  *.o
endif
ifneq (,$(wildcard testEvaluator))
	rm  testEvaluator
endif
ifneq (,$(wildcard testEvalParams))
	rm  testEvalParams
endif
ifneq (,$(wildcard testEvalPolicy))
	rm  testEvalPolicy
endif