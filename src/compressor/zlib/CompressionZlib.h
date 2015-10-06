/*
 * Ceph - scalable distributed file system
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 */


#ifndef CEPH_COMPRESSION_ZLIB_H
#define CEPH_COMPRESSION_ZLIB_H

// -----------------------------------------------------------------------------
#include "common/Mutex.h"
#include "compressor/Compressor.h"
// -----------------------------------------------------------------------------
#include <list>
// -----------------------------------------------------------------------------

class CompressionZlib : public Compressor {
public:

  CompressionZlib()
  {
  }

  virtual
  ~CompressionZlib()
  {
  }

  virtual int compress(bufferlist &in, bufferlist &out);
  virtual int decompress(bufferlist &in, bufferlist &out);

 };


#endif
