# isal plugin
noinst_HEADERS += \
  compressor/isal/CompressionIsal.h \
  compressor/isal/isa-l/include/igzip_lib.h \
  compressor/isal/isa-l/include/types.h

isal_sources = \
  compressor/Compressor.cc \
  compressor/isal/CompressionPluginIsal.cc \
  compressor/isal/CompressionIsal.cc \
  compressor/isal/isa-l/igzip/igzip.c \
  compressor/isal/isa-l/igzip/crc_utils.asm.s \
  compressor/isal/isa-l/igzip/hufftables.asm.s \
  compressor/isal/isa-l/igzip/hufftables_c.c \
  compressor/isal/isa-l/igzip/init_stream.asm.s \
  compressor/isal/isa-l/igzip/utils_asm.asm.s \
  compressor/isal/isa-l/igzip/igzip0_body.asm.s \
  compressor/isal/isa-l/igzip/igzip0_finish.asm.s \
  compressor/isal/isa-l/igzip/igzip0c_body.asm.s \
  compressor/isal/isa-l/igzip/igzip0c_finish.asm.s \
  compressor/isal/isa-l/igzip/igzip1_body.asm.s \
  compressor/isal/isa-l/igzip/igzip1_finish.asm.s \
  compressor/isal/isa-l/igzip/igzip1c_body.asm.s \
  compressor/isal/isa-l/igzip/igzip1c_finish.asm.s \
  compressor/isal/isa-l/igzip/igzip0c_body_stateless.asm.s \
  compressor/isal/isa-l/igzip/igzip0c_finish_stateless.asm.s \
  compressor/isal/isa-l/igzip/crc32_gzip.asm.s \
  compressor/isal/isa-l/igzip/detect_repeated_char.asm.s

compressor/isal/CompressionPluginIsal.cc: ./ceph_ver.h

libceph_isal_la_SOURCES = ${isal_sources}
libceph_isal_la_CFLAGS = ${AM_CFLAGS} -I $(srcdir)/compressor/isal/isa-l/include/
libceph_isal_la_CCASFLAGS = ${AM_CCASFLAGS} -I $(srcdir)/compressor/isal/isa-l/include/
libceph_isal_la_CXXFLAGS= ${AM_CXXFLAGS} 
libceph_isal_la_LIBADD = $(LIBCRUSH) $(PTHREAD_LIBS) $(EXTRALIBS)
libceph_isal_la_LDFLAGS = ${AM_LDFLAGS} -lz -version-info 2:0:0
libceph_isal_la_LIBTOOLFLAGS = --tag=CC
if LINUX
libceph_isal_la_LDFLAGS += -export-symbols-regex '.*__ceph_plugin_.*'
endif

compressorlib_LTLIBRARIES += libceph_isal.la
