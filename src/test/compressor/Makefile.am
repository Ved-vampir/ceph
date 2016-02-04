if ENABLE_SERVER
if WITH_OSD


libceph_example_la_SOURCES = \
	common/buffer.cc \
	compressor/Compressor.cc \
	test/compressor/compressor_plugin_example.cc
noinst_HEADERS += test/compressor/compressor_example.h
test/compressor/compressor_plugin_example.cc: ./ceph_ver.h
libceph_example_la_CFLAGS = ${AM_CFLAGS}
libceph_example_la_CXXFLAGS= ${AM_CXXFLAGS}
libceph_example_la_LIBADD = $(LIBCRUSH) $(PTHREAD_LIBS) $(EXTRALIBS)
libceph_example_la_LDFLAGS = ${AM_LDFLAGS} -export-symbols-regex '.*__compression_.*'
compressorlib_LTLIBRARIES += libceph_example.la

unittest_compression_plugin_SOURCES = \
	compressor/Compressor.cc \
	test/compressor/test_compression_plugin.cc 
unittest_compression_plugin_CXXFLAGS = $(UNITTEST_CXXFLAGS)
unittest_compression_plugin_LDADD = $(LIBOSD) $(LIBCOMMON) $(UNITTEST_LDADD) $(CEPH_GLOBAL)
if LINUX
unittest_compression_plugin_LDADD += -ldl
endif
check_TESTPROGRAMS += unittest_compression_plugin

unittest_compression_snappy_SOURCES = \
	test/compressor/test_compression_snappy.cc \
	${snappy_sources}
unittest_compression_snappy_CXXFLAGS = $(UNITTEST_CXXFLAGS)
unittest_compression_snappy_LDADD = $(LIBOSD) $(LIBCOMMON) $(UNITTEST_LDADD) $(CEPH_GLOBAL)
unittest_compression_snappy_LDFLAGS = -lsnappy
if LINUX
unittest_compression_snappy_LDADD += -ldl
endif
check_TESTPROGRAMS += unittest_compression_snappy

unittest_compression_plugin_snappy_SOURCES = \
	test/compressor/test_compression_plugin_snappy.cc \
	${snappy_sources}
unittest_compression_plugin_snappy_CXXFLAGS = ${AM_CXXFLAGS} ${UNITTEST_CXXFLAGS}
unittest_compression_plugin_snappy_LDADD = $(LIBOSD) $(LIBCOMMON) $(UNITTEST_LDADD) $(CEPH_GLOBAL) $(LIBCOMPRESSOR)
unittest_compression_plugin_snappy_LDFLAGS = -lsnappy
if LINUX
unittest_compression_plugin_snappy_LDADD += -ldl
endif
check_TESTPROGRAMS += unittest_compression_plugin_snappy

unittest_compression_zlib_SOURCES = \
	test/compressor/test_compression_zlib.cc \
	${zlib_sources}
unittest_compression_zlib_CXXFLAGS = $(UNITTEST_CXXFLAGS)
unittest_compression_zlib_LDADD = $(LIBOSD) $(LIBCOMMON) $(UNITTEST_LDADD) $(CEPH_GLOBAL)
unittest_compression_zlib_LDFLAGS = -lz
if LINUX
unittest_compression_zlib_LDADD += -ldl
endif
check_TESTPROGRAMS += unittest_compression_zlib

unittest_compression_plugin_zlib_SOURCES = \
	test/compressor/test_compression_plugin_zlib.cc \
	${zlib_sources}
unittest_compression_plugin_zlib_CXXFLAGS = ${AM_CXXFLAGS} ${UNITTEST_CXXFLAGS}
unittest_compression_plugin_zlib_LDADD = $(LIBOSD) $(LIBCOMMON) $(UNITTEST_LDADD) $(CEPH_GLOBAL) $(LIBCOMPRESSOR)
unittest_compression_plugin_zlib_LDFLAGS = -lz
if LINUX
unittest_compression_plugin_zlib_LDADD += -ldl
endif
check_TESTPROGRAMS += unittest_compression_plugin_zlib

unittest_compression_isal_SOURCES = \
    test/compressor/test_compression_isal.cc \
    ${isal_sources}
unittest_compression_isal_CFLAGS = $(AM_CFLAGS) \
    -Icompressor/isal/isa-l/include/
unittest_compression_isal_CXXFLAGS = $(UNITTEST_CXXFLAGS) \
    -Icompressor/isal/isa-l/include/
unittest_compression_isal_CCASFLAGS = ${AM_CCASFLAGS} \
    -I$(srcdir)/compressor/isal/isa-l/include/
unittest_compression_isal_LDADD = $(LIBOSD) $(LIBCOMMON) $(UNITTEST_LDADD) $(CEPH_GLOBAL)
unittest_compression_isal_LDFLAGS = -lz
if LINUX
unittest_compression_isal_LDADD += -ldl
endif
check_TESTPROGRAMS += unittest_compression_isal

unittest_compression_plugin_isal_SOURCES = \
    test/compressor/test_compression_plugin_isal.cc
unittest_compression_plugin_isal_CXXFLAGS = $(UNITTEST_CXXFLAGS)
unittest_compression_plugin_isal_LDADD = $(LIBOSD) $(LIBCOMMON) $(UNITTEST_LDADD) $(CEPH_GLOBAL) $(LIBCOMPRESSOR)
unittest_compression_plugin_isal_LDFLAGS = -lz
if LINUX
unittest_compression_plugin_isal_LDADD += -ldl
endif
check_TESTPROGRAMS += unittest_compression_plugin_isal

endif # WITH_OSD
endif # ENABLE_SERVER
