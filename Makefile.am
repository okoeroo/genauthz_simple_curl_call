
AM_CPPFLAGS = \
	-I$(srcdir) \
	$(ADD_THESE_DEFINES)


libgenauthz_simple_curl_call_la_LDFLAGS = -avoid-version -lgenauthz_core -lcurl

plugindir = $(MODULEDIR)
plugin_LTLIBRARIES = libgenauthz_simple_curl_call.la

libgenauthz_simple_curl_call_la_SOURCES = \
	simple_curl_call.c

