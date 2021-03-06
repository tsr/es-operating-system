if ENABLE_JAVA
JAVADIR = java
else
JAVADIR =
endif

if ENABLE_CPLUSPLUS
CPLUSPLUSDIR = cplusplus
else
CPLUSPLUSDIR =
endif

if ENABLE_NPAPI
NPAPIDIR = npapi
else
NPAPIDIR =
endif

if ENABLE_JSAPI
JSAPIDIR = jsapi
else
JSAPIDIR =
endif

if ENABLE_V8API
V8APIDIR = v8api
else
V8APIDIR =
endif

SUBDIRS = . testsuite $(JAVADIR) $(CPLUSPLUSDIR) $(NPAPIDIR) $(JSAPIDIR) $(V8APIDIR)
DIST_SUBDIRS = testsuite java cplusplus npapi jsapi v8api

if !NACL

BUILT_SOURCES = lexer.cc parser.cc parser.h

bin_PROGRAMS = esidl

esidl_SOURCES = \
	include/cplusplus.h\
	include/cplusplusCall.h \
	include/cplusplusInvoke.h \
	include/cplusplusMeta.h \
	include/cplusplusSrc.h \
	include/cplusplusTemplate.h \
	include/cxx.h \
	include/esidl.h \
	include/expr.h \
	include/formatter.h \
	include/forward.h \
	include/info.h \
	include/java.h \
	include/messenger.h \
	include/messengerDispatch.h \
	include/messengerInvoke.h \
	include/messengerMeta.h \
	include/meta.h \
	include/reflect.h \
	include/sheet.h \
	include/utf.h \
	src/messenger.cpp \
	src/cplusplus.cpp \
	src/cxx.cpp \
	src/driver.cpp \
	src/esidl.cpp \
	src/java.cpp \
	src/lexer.ll \
	src/parser.yy \
	src/print.cpp \
	src/skeleton.cpp \
	src/template.cpp

esidl_CXXFLAGS = -D YYERROR_VERBOSE

clean-local:
	-rm -f $(BUILT_SOURCES) parser.output $(nobase_nodist_include_HEADERS)

dist-hook:
	-rm -f $(distdir)/lexer.cc $(distdir)/parser.cc $(distdir)/parser.h

endif

AM_YFLAGS = -d -v -t

AM_CPPFLAGS = \
	-iquote $(srcdir)/include \
	-iquote $(srcdir)/src

EXTRA_DIST = \
	esidl.spec.in \
	esidl.spec \
	debian/changelog \
	debian/changelog.in \
	debian/compat \
	debian/control \
	debian/copyright \
	debian/docs \
	debian/rules \
	debian/source/format \
	LICENSE \
	dom/COPYRIGHT.html \
	dom/2dcontext.idl \
	dom/arrays.idl \
	dom/console.idl \
	dom/cssom.idl \
	dom/cssomview.idl \
	dom/dom2css.idl \
	dom/dom2events.idl \
	dom/dom2ranges.idl \
	dom/dom2stylesheets.idl \
	dom/dom2traversal.idl \
	dom/dom2views.idl \
	dom/dom3core.idl \
	dom/dom3events.idl \
	dom/dom3ls.idl \
	dom/dom3validation.idl \
	dom/dom3xpath.idl \
	dom/domcore.idl \
	dom/elementtraversal.idl \
	dom/eventsource.idl \
	dom/file.idl \
	dom/geolocation.idl \
	dom/html5.idl \
	dom/idl_scraper.pl \
	dom/indexeddb.idl \
	dom/microdata.idl \
	dom/NOTICE \
	dom/postmsg.idl \
	dom/progress-events.idl \
	dom/selectors.idl \
	dom/smil.idl \
	dom/svg.idl \
	dom/typedarray.idl \
	dom/url.idl \
	dom/webdatabase.idl \
	dom/webgl.idl \
	dom/webnotifications.idl \
	dom/webstorage.idl \
	dom/websocket.idl \
	dom/wget_webidl_dom \
	dom/workers.idl \
	dom/xhr2.idl \
	setup.pepper
