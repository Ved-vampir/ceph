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

#ifndef COMPRESSION_PLUGIN_H
#define COMPRESSION_PLUGIN_H

#include "common/Mutex.h"
#include "common/PluginRegistry.h"
#include "Compressor.h"

namespace ceph {

  class CompressionPlugin :  public Plugin {
  public:
    CompressorRef compressor;

    CompressionPlugin(CephContext *cct) : Plugin(cct),
                                          compressor(0) 
    {}
    
    virtual ~CompressionPlugin() {}

    virtual int factory(CompressorRef *cs,
			                  ostream *ss) = 0;

    virtual const char* name() {return "CompressionPlugin";}
  };

}

#endif
