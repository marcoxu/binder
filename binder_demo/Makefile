#**********************************************
# Makefile linux 2.6 Module 
# This makefile is written for Ubuntu 10.10
# It may not perfomance without erros on the
# other version or distributions.
#**********************************************
#    BY: Xu, Marco
#    Mail: marco.xu.f@gmail.com
#    2013/08/04
#**********************************************

#编译所有子目录
#SUBDIRS=`ls -d */ | grep -v 'bin' | grep -v 'lib' | grep -v 'include'`
#编译指定子目录
SUBDIRS=binder servicemgr testservice
define make_subdir
 @for subdir in $(SUBDIRS) ; do \
 ( cd $$subdir && make $1) \
 done;
endef

all:
	$(call make_subdir)
 
install :
	$(call make_subdir)
 
debug:
	$(call make_subdir , debug)
clean:
	$(call make_subdir , clean) 