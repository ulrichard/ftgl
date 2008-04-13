
if HAVE_DOXYGEN
htmldocdir = $(datadir)/doc/ftgl/html
htmldoc_DATA = html/doxygen.css
endif

html/doxygen.css: doc-stamp
doc-stamp: ftgl_dox
	$(DOXYGEN) $^
	touch $@

clean: clean-local
clean-local:
	$(RM) -rf html
	$(RM) doc-stamp

if HAVE_DOXYGEN
install-data-local: html/doxygen.css
	$(mkinstalldirs) $(DESTDIR)$(datadir)/doc/$(PACKAGE_NAME)/html
	$(INSTALL) -m 0644 \
	  `find html -name '*.html' -o -name '*.gif' -o -name '*.png'` \
	  $(DESTDIR)$(datadir)/doc/$(PACKAGE_NAME)/html/
endif

EXTRA_DIST = \
    ftgl_dox \
    FTGL.html \
    FTGL_1_3.gif \
    images/ftgldemo.jpg \
    images/metrics.png \
    html.tar.gz \
    $(NULL)
