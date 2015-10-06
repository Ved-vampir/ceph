// -*- mode:C++; tab-width:8; c-basic-offset:2; indent-tabs-mode:t -*-
// vim: ts=8 sw=2 smarttab
/*
 * Ceph - scalable distributed file system
 *
 * Copyright (C) 2014 Haomai Wang <haomaiwang@gmail.com>
 *
 * This is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License version 2.1, as published by the Free Software 
 * Foundation.  See file COPYING.
 *
 */

#include "Compressor.h"
#include "SnappyCompressor.h"


Compressor* Compressor::create(const string &type)
{
  Compressor* cs_impl = NULL;
  stringstream ss;
  ceph::CompressionPluginRegistry::instance().factory(
      type,
      g_conf->compression_dir,
      &cs_impl,
      &ss);
  assert(cs_impl != NULL);
  return cs_impl;
}
