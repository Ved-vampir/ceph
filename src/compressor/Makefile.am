compressionlibdir = $(pkglibdir)/compressor
compressionlib_LTLIBRARIES =  

include compressor/zlib/Makefile.am
include compressor/snappy/Makefile.am

libcompressor_la_SOURCES = \
	compressor/Compressor.cc \
	compressor/AsyncCompressor.cc \
    compressor/CompressionPlugin.cc
compressor/CompressionPlugin.cc: ./ceph_ver.h
libcompression_la_DEPENDENCIES = $(compressionlib_LTLIBRARIES)
if LINUX
libcompression_la_LIBADD = -ldl
endif # LINUX
noinst_LTLIBRARIES += libcompressor.la

libcompressor_la_LIBADD = $(LIBCOMMON)

noinst_HEADERS += \
	compressor/Compressor.h \
	compressor/AsyncCompressor.h \
    compressor/CompressionPlugin.h

