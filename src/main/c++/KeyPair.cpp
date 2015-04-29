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

static jfieldID publickeyptrFID;
static jfieldID privatekeyptrFID;

static void ensure_keypair(JNIEnv *env, jobject obj);

static void decode_key(JNIEnv *env, jobject obj, jfieldID field, char * key) {
  jobject fieldobj = env->GetObjectField (obj, field);
  jbyteArray * fieldarr = reinterpret_cast<jbyteArray*>(&fieldobj);
  jbyte* key_bytes = env->GetByteArrayElements(*fieldarr, NULL);
  uint8_t* r = zmq_z85_decode(reinterpret_cast<uint8_t*>(key_bytes), key);
  env->ReleaseByteArrayElements(*fieldarr, key_bytes, 0);
  if (!r) {
    int err = zmq_errno();
    raise_exception(env, err);
  }
}

/**
 * Called to construct a Java Context object.
 */
JNIEXPORT void JNICALL Java_org_zeromq_ZMQ_00024KeyPair_construct(JNIEnv *env, jobject obj) {

  ensure_keypair(env,obj);
  char public_key[41];
  char secret_key[41];
  int rc =  zmq_curve_keypair (public_key, secret_key);

  if (rc) {
    int err = zmq_errno();
    raise_exception(env, err);
    return;
  }
  decode_key(env, obj, publickeyptrFID, public_key);
  decode_key(env, obj, privatekeyptrFID, secret_key);
}


/**
 * Make sure we have a valid pointers to Java's KeyPair::publickey and KeyPair::privatekey
 */
static void ensure_keypair(JNIEnv *env, jobject obj) {
  if (publickeyptrFID == NULL || privatekeyptrFID == NULL) {
    jclass cls = env->GetObjectClass(obj);
    assert(cls);
    publickeyptrFID = env->GetFieldID(cls, "publickey", "[B");
    assert(publickeyptrFID);
    privatekeyptrFID = env->GetFieldID(cls, "privatekey", "[B");
    assert(privatekeyptrFID);
    env->DeleteLocalRef(cls);
  }
}
