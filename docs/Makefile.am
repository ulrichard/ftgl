
if HAVE_DOXYGEN
htmldocdir = $(datadir)/doc/ftgl/html
htmldoc_DATA = html/doxygen.css
if HAVE_LATEX
pdfdocdir = $(datadir)/doc/ftgl
pdfdoc_DATA = latex/ftgl.pdf
endif
endif

PNGS = \
    images/logo.png \
    images/metrics.png \
    images/rasterfont.png \
    images/vectorfont.png \
    images/texturefont.png \
    $(NULL)

stamp-eps: $(PNGS)
if HAVE_LATEX
	for i in $^; do convert $$i $$(echo $$i | sed 's/png$$/eps/'); done
endif
	touch $@

html/doxygen.css: stamp-doxygen
stamp-doxygen: doxygen.cfg stamp-eps
	$(DOXYGEN) $^
	touch $@

latex/ftgl.pdf: stamp-latex
stamp-latex: stamp-doxygen
	rm -f latex/ftgl.tex latex/ftgl.pdf
	mv latex/refman.tex latex/ftgl.tex
	sed 's/setlength{/renewcommand{/' latex/ftgl.tex > latex/refman.tex
	cd latex && $(MAKE) $(AM_CFLAGS) refman.pdf #|| (cat refman.log; exit 1)
	mv latex/refman.pdf latex/ftgl.pdf
	touch stamp-latex

clean: clean-local
clean-local:
	$(RM) -rf html latex
	$(RM) -f images/*.eps
	$(RM) -f stamp-doxygen stamp-latex stamp-eps

if HAVE_DOXYGEN
install-data-local: html/doxygen.css
	$(mkinstalldirs) $(DESTDIR)$(htmldocdir)/
	$(INSTALL) -m 0644 \
	  `find html -name '*.html' -o -name '*.gif' -o -name '*.png' -o -name '*.jpg'` \
	  $(DESTDIR)$(htmldocdir)/
endif

EXTRA_DIST = \
    doxygen.cfg.in \
    ftgl.dox \
    FTGL_1_3.gif \
    $(PNGS) \
    images/metrics.svg \
    $(NULL)

NULL =
