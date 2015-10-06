// -*- mode:C++; tab-width:8; c-basic-offset:2; indent-tabs-mode:t -*-
// vim: ts=8 sw=2 smarttab
/*
 * Ceph distributed storage system
 *
 * Copyright (C) 2014 Red Hat <contact@redhat.com>
 *
 * Author: Loic Dachary <loic@dachary.org>
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 */

#include <errno.h>

#include "global/global_init.h"
#include "compression/Compression.h"
#include "common/ceph_argparse.h"
#include "global/global_context.h"
#include "common/config.h"
#include "gtest/gtest.h"

class CompressionTest : public Compression {
public:

  CompressionTest() {}
  virtual ~CompressionTest() {}

  virtual int init(CompressionProfile &profile, ostream *ss) {
    return 0;
  }

};

TEST(CompressionTest, encode_memory_align)
{
  int k = 3;
  int m = 1;
  unsigned chunk_size = Compression::SIMD_ALIGN * 7;
  CompressionTest erasure_code(k, m, chunk_size);

  set<int> want_to_encode;
  for (unsigned int i = 0; i < erasure_code.get_chunk_count(); i++)
    want_to_encode.insert(i);
  string data(chunk_size + chunk_size / 2, 'X'); // uses 1.5 chunks out of 3
  // make sure nothing is memory aligned
  bufferptr ptr(buffer::create_aligned(data.length() + 1, Compression::SIMD_ALIGN));
  ptr.copy_in(1, data.length(), data.c_str());
  ptr.set_offset(1);
  ptr.set_length(data.length());
  bufferlist in;
  in.append(ptr);
  map<int, bufferlist> encoded;

  ASSERT_FALSE(in.is_aligned(Compression::SIMD_ALIGN));
  ASSERT_EQ(0, erasure_code.encode(want_to_encode, in, &encoded));
  for (unsigned int i = 0; i < erasure_code.get_chunk_count(); i++)
    ASSERT_TRUE(encoded[i].is_aligned(Compression::SIMD_ALIGN));
  for (unsigned i = 0; i < chunk_size / 2; i++)
    ASSERT_EQ(encoded[1][i], 'X');
  ASSERT_NE(encoded[1][chunk_size / 2], 'X');
}

TEST(CompressionTest, encode_misaligned_non_contiguous)
{
  int k = 3;
  int m = 1;
  unsigned chunk_size = Compression::SIMD_ALIGN * 7;
  CompressionTest erasure_code(k, m, chunk_size);

  set<int> want_to_encode;
  for (unsigned int i = 0; i < erasure_code.get_chunk_count(); i++)
    want_to_encode.insert(i);
  string data(chunk_size, 'X');
  // create a non contiguous bufferlist where the frist and the second
  // bufferptr are not size aligned although they are memory aligned
  bufferlist in;
  {
    bufferptr ptr(buffer::create_aligned(data.length() - 1, Compression::SIMD_ALIGN));
    in.append(ptr);
  }
  {
    bufferptr ptr(buffer::create_aligned(data.length() + 1, Compression::SIMD_ALIGN));
    in.append(ptr);
  }
  map<int, bufferlist> encoded;

  ASSERT_FALSE(in.is_contiguous());
  ASSERT_TRUE(in.buffers().front().is_aligned(Compression::SIMD_ALIGN));
  ASSERT_FALSE(in.buffers().front().is_n_align_sized(chunk_size));
  ASSERT_TRUE(in.buffers().back().is_aligned(Compression::SIMD_ALIGN));
  ASSERT_FALSE(in.buffers().back().is_n_align_sized(chunk_size));
  ASSERT_EQ(0, erasure_code.encode(want_to_encode, in, &encoded));
  for (unsigned int i = 0; i < erasure_code.get_chunk_count(); i++) {
    ASSERT_TRUE(encoded[i].is_aligned(Compression::SIMD_ALIGN));
    ASSERT_TRUE(encoded[i].is_n_align_sized(chunk_size));
  }
}

int main(int argc, char **argv)
{
  vector<const char*> args;
  argv_to_vec(argc, (const char **)argv, args);

  global_init(NULL, args, CEPH_ENTITY_TYPE_CLIENT, CODE_ENVIRONMENT_UTILITY, 0);
  common_init_finish(g_ceph_context);

  g_conf->set_val("erasure_code_dir", ".libs", false, false);

  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

/*
 * Local Variables:
 * compile-command: "cd ../.. ;
 *   make -j4 unittest_erasure_code &&
 *   valgrind --tool=memcheck --leak-check=full \
 *      ./unittest_erasure_code \
 *      --gtest_filter=*.* --log-to-stderr=true"
 * End:
 */
