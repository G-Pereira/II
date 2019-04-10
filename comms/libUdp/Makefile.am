## Process this file with automake to produce Makefile.in

SUBDIRS =  src doc 

cplab3docdir = ${prefix}/doc/cplab3
cplab3doc_DATA = \
	autogen.sh\
	README\
	COPYING\
	AUTHORS\
	ChangeLog\
	INSTALL\
	NEWS\
	TODO

EXTRA_DIST = Cplab3.prj $(cplab3doc_DATA)



# Copy all the spec files. Of cource, only one is actually used.
dist-hook:
	for specfile in *.spec; do \
		if test -f $$specfile; then \
			cp -p $$specfile $(distdir); \
		fi \
	done

