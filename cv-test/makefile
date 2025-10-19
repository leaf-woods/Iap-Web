iap_ghl_cv_example_base=/home/linye020603/github-local/Iap-Web/examples

iap_cv_test_base=/home/linye020603/github-local/Iap-Web/cv-test
dir_test_image=$(iap_cv_test_base)/image
dir_test_stat=$(iap_cv_test_base)/statistics
dir_test_util=$(iap_cv_test_base)/util

all:
	cd $(iap_ghl_cv_example_base)/example8 && $(MAKE)

	cd $(dir_test_image)/color && $(MAKE)
	cd $(dir_test_image)/color/compare && $(MAKE)
	cd $(dir_test_image)/color/datatype && $(MAKE)
	cd $(dir_test_image)/region && $(MAKE)
	cd $(dir_test_image)/region/context && $(MAKE)
	cd $(dir_test_image)/region/datatype && $(MAKE)
	cd $(dir_test_image)/region/explore && $(MAKE)
	cd $(dir_test_image)/train && $(MAKE)
	cd $(dir_test_image)/train/policies && $(MAKE)
	cd $(dir_test_stat)/ && $(MAKE)
	cd $(dir_test_util)/convert && $(MAKE)
	cd $(dir_test_util)/log && $(MAKE)
	cd $(dir_test_util)/tree/bstree && $(MAKE)
	cd $(dir_test_util)/tree/dtree && $(MAKE)
	cd $(dir_test_util)/tree/htree && $(MAKE)
	cd $(dir_test_util)/tree/vtree && $(MAKE)

clean:
	cd $(iap_ghl_cv_example_base)/example8 && $(MAKE) clean

	cd $(dir_test_image)/color && $(MAKE) clean
	cd $(dir_test_image)/color/compare && $(MAKE) clean
	cd $(dir_test_image)/color/datatype && $(MAKE) clean
	cd $(dir_test_image)/region && $(MAKE) clean
	cd $(dir_test_image)/region/context && $(MAKE) clean
	cd $(dir_test_image)/region/datatype && $(MAKE) clean
	cd $(dir_test_image)/region/explore && $(MAKE) clean
	cd $(dir_test_image)/train && $(MAKE) clean
	cd $(dir_test_image)/train/policies && $(MAKE) clean
	cd $(dir_test_stat)/ && $(MAKE) clean
	cd $(dir_test_util)/convert && $(MAKE) clean
	cd $(dir_test_util)/log && $(MAKE) clean
	cd $(dir_test_util)/tree/bstree && $(MAKE) clean
	cd $(dir_test_util)/tree/dtree && $(MAKE) clean
	cd $(dir_test_util)/tree/htree && $(MAKE) clean
	cd $(dir_test_util)/tree/vtree && $(MAKE) clean
