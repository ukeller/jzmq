/*
    Copyright (c) 2007-2015 Contributors as noted in the AUTHORS file

    This file is part of 0MQ.

    0MQ is free software; you can redistribute it and/or modify it under
    the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation; either version 3 of the License, or
    (at your option) any later version.

    0MQ is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <assert.h>

#include <zmq.h>
#include <zmq_utils.h>

#include "jzmq.hpp"
#include "util.hpp"
#include "org_zeromq_ZMQ_KeyPair.h"

/**
 * Called to construct a Java Context object.
 */
JNIEXPORT jobjectArray JNICALL
Java_org_zeromq_ZMQ_00024KeyPair_construct(JNIEnv *env, jobject obj) {
  char public_key[41];
  char secret_key[41];
  int rc = zmq_curve_keypair(public_key, secret_key);

  if (rc) {
    int err = zmq_errno();
    raise_exception(env, err);
    return NULL;
  }

  jobjectArray ret = (jobjectArray)env->NewObjectArray(
      2, env->FindClass("java/lang/String"), NULL);

  env->SetObjectArrayElement(ret, 0, env->NewStringUTF(public_key));
  env->SetObjectArrayElement(ret, 1, env->NewStringUTF(secret_key));
  return ret;
}
