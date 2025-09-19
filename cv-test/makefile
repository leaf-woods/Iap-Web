iap_ghl_test_cv_base=/home/linye020603/iap-web/cv-test
dir_test_image=$(iap_ghl_test_cv_base)/image
dir_test_util=$(iap_ghl_test_cv_base)/util

all:
	cd $(dir_test_image)/color && $(MAKE)
	cd $(dir_test_image)/color/compare && $(MAKE)
	cd $(dir_test_image)/region && $(MAKE)
	cd $(dir_test_image)/toolbox && $(MAKE)
	cd $(dir_test_util)/convert && $(MAKE)
	cd $(dir_test_util)/log && $(MAKE)
	cd $(dir_test_util)/tree/bstree && $(MAKE)
	cd $(dir_test_util)/tree/htree && $(MAKE)
	cd $(dir_test_util)/tree/vtree && $(MAKE)

clean:
	cd $(dir_test_image)/color && $(MAKE) clean
	cd $(dir_test_image)/color/compare && $(MAKE) clean
	cd $(dir_test_image)/region && $(MAKE) clean
	cd $(dir_test_image)/toolbox && $(MAKE) clean
	cd $(dir_test_util)/convert && $(MAKE) clean
	cd $(dir_test_util)/log && $(MAKE) clean
	cd $(dir_test_util)/tree/bstree && $(MAKE) clean
	cd $(dir_test_util)/tree/htree && $(MAKE) clean
	cd $(dir_test_util)/tree/vtree && $(MAKE) clean
