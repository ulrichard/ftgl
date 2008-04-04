
DOXYFILE = ftgl_dox
DOCDIRS = html

all: doc

doc: doc-stamp
doc-stamp: $(DOXYFILE)
	sed 's,^INPUT[ 	].*,INPUT=../../src,' $^ | $(DOXYGEN) -
	touch $@

install-data-local: doc
	$(INSTALL) -d -m 0755 $(DESTDIR)$(datadir)/doc/$(PACKAGE_NAME)/html
	$(INSTALL) -m 0644 html/* $(DESTDIR)$(datadir)/doc/$(PACKAGE_NAME)/html/

distclean-local:
	$(RM) -r $(DOCDIRS)
	$(RM) doc-stamp

.PHONY: all doc
