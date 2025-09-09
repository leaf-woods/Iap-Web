iap_cv_test_base=/home/linye020603/iap-web/cv-test
dir_test_image_color=$(iap_cv_test_base)/image/color
dir_test_util_convert=$(iap_cv_test_base)/util/convert
dir_test_util_tree=$(iap_cv_test_base)/util/tree

all:
	cd $(dir_test_image_color) && $(MAKE)
	cd $(dir_test_util_convert) && $(MAKE)
	cd $(dir_test_util_tree)/bstree && $(MAKE)
	cd $(dir_test_util_tree)/htree && $(MAKE)
	cd $(dir_test_util_tree)/vtree && $(MAKE)

clean:
	cd $(dir_test_image_color) && $(MAKE) clean
	cd $(dir_test_util_convert) && $(MAKE) clean
	cd $(dir_test_util_tree)/bstree && $(MAKE) clean
	cd $(dir_test_util_tree)/htree && $(MAKE) clean
	cd $(dir_test_util_tree)/vtree && $(MAKE) clean
