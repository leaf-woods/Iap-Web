iap_ghl_cv_example_base=/home/linye020603/github-local/Iap-Web/examples

iap_cv_test_base=/home/linye020603/github-local/Iap-Web/cv-test
dir_test_image=$(iap_cv_test_base)/image
dir_test_stat=$(iap_cv_test_base)/statistics
dir_test_util=$(iap_cv_test_base)/util

all:
	cd $(iap_ghl_cv_example_base)/example8 && $(MAKE) && echo;

	cd $(dir_test_image)/color && $(MAKE) && echo
	cd $(dir_test_image)/color/compare && $(MAKE) && echo
	cd $(dir_test_image)/color/datatype && $(MAKE) && echo
	cd $(dir_test_image)/region && $(MAKE) && echo
	cd $(dir_test_image)/region/context && $(MAKE) && echo
	cd $(dir_test_image)/region/datatype && $(MAKE) && echo
	cd $(dir_test_image)/region/evaluate && $(MAKE) && echo
	cd $(dir_test_image)/region/explore && $(MAKE) && echo
	cd $(dir_test_image)/train && $(MAKE) && echo
	cd $(dir_test_image)/train/policies && $(MAKE) && echo
	cd $(dir_test_stat)/ && $(MAKE) && echo
	cd $(dir_test_util)/convert && $(MAKE) && echo
	cd $(dir_test_util)/log && $(MAKE) && echo
	cd $(dir_test_util)/tree/bstree && $(MAKE) && echo
	cd $(dir_test_util)/tree/dtree && $(MAKE) && echo
	cd $(dir_test_util)/tree/htree && $(MAKE) && echo
	cd $(dir_test_util)/tree/vtree && $(MAKE) && echo

clean:
	cd $(iap_ghl_cv_example_base)/example8 && $(MAKE) clean && echo

	cd $(dir_test_image)/color && $(MAKE) clean && echo
	cd $(dir_test_image)/color/compare && $(MAKE) clean && echo
	cd $(dir_test_image)/color/datatype && $(MAKE) clean && echo
	cd $(dir_test_image)/region && $(MAKE) clean && echo
	cd $(dir_test_image)/region/context && $(MAKE) clean && echo
	cd $(dir_test_image)/region/datatype && $(MAKE) clean && echo
	cd $(dir_test_image)/region/evaluate && $(MAKE) clean && echo
	cd $(dir_test_image)/region/explore && $(MAKE) clean && echo
	cd $(dir_test_image)/train && $(MAKE) clean && echo
	cd $(dir_test_image)/train/policies && $(MAKE) clean && echo
	cd $(dir_test_stat)/ && $(MAKE) clean && echo
	cd $(dir_test_util)/convert && $(MAKE) clean && echo
	cd $(dir_test_util)/log && $(MAKE) clean && echo
	cd $(dir_test_util)/tree/bstree && $(MAKE) clean && echo
	cd $(dir_test_util)/tree/dtree && $(MAKE) clean && echo
	cd $(dir_test_util)/tree/htree && $(MAKE) clean && echo
	cd $(dir_test_util)/tree/vtree && $(MAKE) clean && echo
