
if HAVE_DOXYGEN
htmldocdir = $(datadir)/doc/ftgl/html
htmldoc_DATA = html/doxygen.css
endif

IMAGES = \
    images/ftgldemo.jpg \
    images/metrics.png \
    $(NULL)

html/doxygen.css: doc-stamp
doc-stamp: doxygen.cfg
	$(DOXYGEN) $^
	cp $(IMAGES) html/
	touch $@

clean: clean-local
clean-local:
	$(RM) -rf html
	$(RM) doc-stamp

if HAVE_DOXYGEN
install-data-local: html/doxygen.css
	$(mkinstalldirs) $(DESTDIR)$(datadir)/doc/$(PACKAGE_NAME)/html
	$(INSTALL) -m 0644 \
	  `find html -name '*.html' -o -name '*.gif' -o -name '*.png' -o -name '*.jpg'` \
	  $(DESTDIR)$(datadir)/doc/$(PACKAGE_NAME)/html/
endif

EXTRA_DIST = \
    doxygen.cfg.in \
    ftgl.dox \
    FTGL_1_3.gif \
    $(IMAGES) \
    images/metrics.svg \
    $(NULL)

NULL =
