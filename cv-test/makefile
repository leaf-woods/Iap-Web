iap_ghl_cv_example_base=/home/linye020603/github-local/Iap-Web/examples

iap_ghl_cv_test_base=/home/linye020603/github-local/Iap-Web/cv-test
dir_test_image=$(iap_ghl_cv_test_base)/image
dir_test_util=$(iap_ghl_cv_test_base)/util

all:
	cd $(iap_ghl_cv_example_base)/example8 && $(MAKE)

	cd $(dir_test_image)/color && $(MAKE)
	cd $(dir_test_image)/color/compare && $(MAKE)
	cd $(dir_test_image)/region && $(MAKE)
	cd $(dir_test_image)/toolbox && $(MAKE)
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
	cd $(dir_test_image)/region && $(MAKE) clean
	cd $(dir_test_image)/toolbox && $(MAKE) clean
	cd $(dir_test_util)/convert && $(MAKE) clean
	cd $(dir_test_util)/log && $(MAKE) clean
	cd $(dir_test_util)/tree/bstree && $(MAKE) clean
	cd $(dir_test_util)/tree/dtree && $(MAKE) clean
	cd $(dir_test_util)/tree/htree && $(MAKE) clean
	cd $(dir_test_util)/tree/vtree && $(MAKE) clean
