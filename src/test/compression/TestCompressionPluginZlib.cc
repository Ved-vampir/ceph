// -*- mode:C++; tab-width:8; c-basic-offset:2; indent-tabs-mode:t -*-
// vim: ts=8 sw=2 smarttab
/*
 * Ceph distributed storage system
 *
 * Copyright (C) 2013,2014 Cloudwatt <libre.licensing@cloudwatt.com>
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
#include "arch/probe.h"
#include "arch/intel.h"
#include "arch/arm.h"
#include "global/global_init.h"
#include "compression/Compression.h"
#include "common/ceph_argparse.h"
#include "global/global_context.h"
#include "common/config.h"
#include "gtest/gtest.h"

TEST(CompressionPlugin, factory)
{
  CompressionPluginRegistry &instance = CompressionPluginRegistry::instance();
  CompressionProfile profile;
  {
    CompressionInterfaceRef compression;
    EXPECT_FALSE(compression);
    EXPECT_EQ(-ENOENT, instance.factory("zlib",
					g_conf->compression_dir,
					profile,
                                        &compression, &cerr));
    EXPECT_FALSE(compression);
  }
}


TEST(CompressionPlugin, compress_decompress)
{
  
#define LARGE_ENOUGH 2048
  bufferptr in_ptr(buffer::create_page_aligned(LARGE_ENOUGH));
  in_ptr.zero();
  in_ptr.set_length(0);
  const char *payload =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789"
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789"
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789"
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789"
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
  in_ptr.append(payload, strlen(payload));
  bufferlist in;
  in.push_front(in_ptr);

  CompressionPluginRegistry &instance = CompressionPluginRegistry::instance();
  CompressionProfile profile;
  profile["technique"] = "reed_sol_van";
  profile["k"] = "2";
  profile["m"] = "1";
  for (vector<string>::iterator sse_variant = sse_variants.begin();
       sse_variant != sse_variants.end();
       ++sse_variant) {
    //
    // load the plugin variant
    //
    CompressionInterfaceRef compression;
    EXPECT_FALSE(compression);
    EXPECT_EQ(0, instance.factory("jerasure_" + *sse_variant,
				  g_conf->compression_dir,
				  profile,
                                  &compression, &cerr));
    EXPECT_TRUE(compression.get());

    //
    // encode
    //
    int want_to_encode[] = { 0, 1, 2 };
    map<int, bufferlist> encoded;
    EXPECT_EQ(0, compression->encode(set<int>(want_to_encode, want_to_encode+3),
                                      in,
                                      &encoded));
    EXPECT_EQ(3u, encoded.size());
    unsigned length =  encoded[0].length();
    EXPECT_EQ(0, strncmp(encoded[0].c_str(), in.c_str(), length));
    EXPECT_EQ(0, strncmp(encoded[1].c_str(), in.c_str() + length,
                         in.length() - length));

    //
    // decode with reconstruction
    //
    map<int, bufferlist> degraded = encoded;
    degraded.erase(1);
    EXPECT_EQ(2u, degraded.size());
    int want_to_decode[] = { 0, 1 };
    map<int, bufferlist> decoded;
    EXPECT_EQ(0, compression->decode(set<int>(want_to_decode, want_to_decode+2),
                                      degraded,
                                      &decoded));
    EXPECT_EQ(3u, decoded.size());
    EXPECT_EQ(length, decoded[0].length());
    EXPECT_EQ(0, strncmp(decoded[0].c_str(), in.c_str(), length));
    EXPECT_EQ(0, strncmp(decoded[1].c_str(), in.c_str() + length,
                         in.length() - length));

  }
}

int main(int argc, char **argv)
{
  vector<const char*> args;
  argv_to_vec(argc, (const char **)argv, args);

  global_init(NULL, args, CEPH_ENTITY_TYPE_CLIENT, CODE_ENVIRONMENT_UTILITY, 0);
  common_init_finish(g_ceph_context);

  g_conf->set_val("compression_dir", ".libs", false, false);

  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

/*
 * Local Variables:
 * compile-command: "cd ../.. ; make -j4 &&
 *   make unittest_compression_plugin_jerasure &&
 *   valgrind --tool=memcheck ./unittest_compression_plugin_jerasure \
 *      --gtest_filter=*.* --log-to-stderr=true --debug-osd=20"
 * End:
 */
