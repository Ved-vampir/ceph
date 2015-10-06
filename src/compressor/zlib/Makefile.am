# zlib plugin
noinst_HEADERS += \
  compressor/zlib/zlib-1.2.8/zutil.h \
  compressor/zlib/zlib-1.2.8/zlib.h \
  compressor/zlib/zlib-1.2.8/zconf.h \
  compressor/zlib/zlib-1.2.8/gzguts.h \
  compressor/zlib/zlib-1.2.8/crc32.h \
  compressor/zlib/zlib-1.2.8/inftrees.h \
  compressor/zlib/zlib-1.2.8/inflate.h \
  compressor/zlib/zlib-1.2.8/inffast.h \
  compressor/zlib/zlib-1.2.8/inffixed.h \
  compressor/zlib/zlib-1.2.8/deflate.h \
  compressor/zlib/CompressionZlib.h

zlib_sources = \
  compressor/Compressor.cc \
  compressor/zlib/zlib-1.2.8/zutil.c \
  compressor/zlib/zlib-1.2.8/adler32.c \
  compressor/zlib/zlib-1.2.8/compress.c \
  compressor/zlib/zlib-1.2.8/crc32.c \
  compressor/zlib/zlib-1.2.8/deflate.c \
  compressor/zlib/zlib-1.2.8/gzclose.c \
  compressor/zlib/zlib-1.2.8/gzlib.c \
  compressor/zlib/zlib-1.2.8/gzread.c \
  compressor/zlib/zlib-1.2.8/gzwrite.c \
  compressor/zlib/zlib-1.2.8/infback.c \
  compressor/zlib/zlib-1.2.8/inffast.c \
  compressor/zlib/zlib-1.2.8/inflate.c \
  compressor/zlib/zlib-1.2.8/inftrees.c \
  compressor/zlib/zlib-1.2.8/trees.c \
  compressor/zlib/zlib-1.2.8/uncompr.c \
  compressor/zlib/CompressionPluginZlib.cc \
  compressor/zlib/CompressionZlib.cc

compressor/zlib/CompressionPluginZlib.cc: ./ceph_ver.h

libcs_zlib_la_SOURCES = ${zlib_sources}
libcs_zlib_la_CFLAGS = ${AM_CFLAGS}  \
  -I$(srcdir)/compressor/zlib/zlib-1.2.8
libcs_zlib_la_CXXFLAGS= ${AM_CXXFLAGS} \
  -I$(srcdir)/compressor/zlib/zlib-1.2.8
libcs_zlib_la_LIBADD = $(LIBCRUSH) $(PTHREAD_LIBS) $(EXTRALIBS)
libcs_zlib_la_LDFLAGS = ${AM_LDFLAGS} -version-info 2:0:0
if LINUX
libcs_zlib_la_LDFLAGS += -export-symbols-regex '.*__compressor_.*'
endif

compressorlib_LTLIBRARIES += libcs_zlib.la
